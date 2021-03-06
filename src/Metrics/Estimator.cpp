/*
 * Copyright (c) 2018 Mark Liversedge (liversedge@gmail.com)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "Estimator.h"

#include "Context.h"
#include "Athlete.h"
#include "RideFileCache.h"
#include "RideCacheModel.h"
#include "Specification.h"

#ifndef ESTIMATOR_DEBUG
#define ESTIMATOR_DEBUG false
#endif
#ifdef Q_CC_MSVC
#define printd(fmt, ...) do {                                                \
    if (ESTIMATOR_DEBUG) {                                 \
        printf("[%s:%d %s] " fmt , __FILE__, __LINE__,        \
               __FUNCTION__, __VA_ARGS__);                    \
        fflush(stdout);                                       \
    }                                                         \
} while(0)
#else
#define printd(fmt, args...)                                            \
    do {                                                                \
        if (ESTIMATOR_DEBUG) {                                       \
            printf("[%s:%d %s] " fmt , __FILE__, __LINE__,              \
                   __FUNCTION__, ##args);                               \
            fflush(stdout);                                             \
        }                                                               \
    } while(0)
#endif

class RollingBests {
    private:

        // buffer of best values; Watts or Watts/KG
        // is a double to handle both use cases
        QVector<QVector<float> > buffer;

        // current location in circular buffer
        int index;

    public:

        // iniitalise with circular buffer size
        RollingBests(int size) {
            index=1;
            buffer.resize(size);
        }

        // add a new weeks worth of data, losing
        // whatever is at the back of the buffer
        void addBests(QVector<float> array) {
            buffer[index++] = array;
            if (index >= buffer.count()) index=0;
        }

        // get an aggregate of all the bests
        // currently in the circular buffer
        QVector<float> aggregate() {

            QVector<float> returning;

            // set return buffer size
            int size=0;
            for(int i=0; i<buffer.count(); i++)
                if (buffer[i].size() > size)
                    size = buffer[i].size();

            // initialise return values
            returning.fill(0.0f, size);

            // get largest values
            for(int i=0; i<buffer.count(); i++)
                for (int j=0; j<buffer[i].count(); j++)
                    if(buffer[i].at(j) > returning[j])
                        returning[j] = buffer[i].at(j);

            // return the aggregate
            return returning;
        }
};

Estimator::Estimator(Context *context) : context(context)
{
    // used to flag when we need to stop
    abort = false;

    // lazy start signal
    connect(&singleshot, SIGNAL(timeout()), this, SLOT(calculate()));

    // when thread finishes we can let everyone know estimates are updated
    connect(this, SIGNAL(finished()), context, SLOT(notifyEstimatesRefreshed()));
}

void
Estimator::stop()
{
    if (isRunning()) {

        // we could use requestInterruption but would mean we need QT > 5.2
        // and there isn't much value in that.
        abort = true;

        // now wait for the thread to stop
        while(isRunning() && abort == true)  msleep(50);
    }
}

// terminate thread before closing
Estimator::~Estimator()
{
    stop();
}

// refresh
void
Estimator::refresh()
{
    printd("Lazy start triggered.\n");

    stop(); // stop any running threads
    singleshot.stop(); // stop any pending threads

    // 15 secs delay before calculate() is triggered
    singleshot.setSingleShot(true);
    singleshot.setInterval(15000);
    singleshot.start();
}

// setup and run, if not already running
void
Estimator::calculate()
{
    // already doing that, so return straight away
    if (isRunning()) return;

    // get a copy of the rides XXX what about deleting rides?
    rides = context->athlete->rideCache->rides();

    // kick off thread
    start();
}

// threaded code here
void
Estimator::run()
{
    printd("Estimator starts.\n");

    // this needs to be done once all the other metrics
    // Calculate a *monthly* estimate of CP, W' etc using
    // bests data from the previous 12 weeks
    RollingBests bests(12);
    RollingBests bestsWPK(12);

    // clear any previous calculations
    QList<PDEstimate> est;

    // we do this by aggregating power data into bests
    // for each month, and having a rolling set of 3 aggregates
    // then aggregating those up into a rolling 3 month 'bests'
    // which we feed to the models to get the estimates for that
    // point in time based upon the available data
    QDate from, to;

    // what dates have any power data ?
    foreach(RideItem *item, rides) {

        // has power, but not running
        if (item->present.contains("P") && !item->isRun) {

            // no date set
            if (from == QDate()) from = item->dateTime.date();
            if (to == QDate()) to = item->dateTime.date();

            // later...
            if (item->dateTime.date() < from) from = item->dateTime.date();

            // earlier...
            if (item->dateTime.date() > to) to = item->dateTime.date();
        }
    }

    // if we don't have 2 rides or more then skip this but add a blank estimate
    if (from == to || to == QDate()) {
        printd("Estimator ends, less than 2 rides with power data.\n");
        est << PDEstimate();
        return;
    }

    // set up the models we support
    CP2Model p2model(context);
    CP3Model p3model(context);
    WSModel wsmodel(context);
    MultiModel multimodel(context);
    ExtendedModel extmodel(context);

    QList <PDModel *> models;
    models << &p2model;
    models << &p3model;
    models << &multimodel;
    models << &extmodel;
    models << &wsmodel;


    // from has first ride with Power data / looking at the next 7 days of data with Power
    // calculate Estimates for all data per week including the week of the last Power recording
    QDate date = from;
    while (date < to) {

        // check if we've been asked to stop
        if (abort == true) {
            printd("Model estimator aborted.\n");
            abort = false;
            return;
        }

        QDate begin = date;
        QDate end = date.addDays(6);

        printd("Model progress %d/%d\n", date.year(), date.month());

        // months is a rolling 3 months sets of bests
        QVector<float> wpk; // for getting the wpk values

        // don't include RUNS ..................................................vvvvv
        bests.addBests(RideFileCache::meanMaxPowerFor(context, wpk, begin, end, false));
        bestsWPK.addBests(wpk);

        // we now have the data
        foreach(PDModel *model, models) {

            PDEstimate add;

            // set the data
            model->setData(bests.aggregate());
            model->saveParameters(add.parameters); // save the computed parms

            add.wpk = false;
            add.from = begin;
            add.to = end;
            add.model = model->code();
            add.WPrime = model->hasWPrime() ? model->WPrime() : 0;
            add.CP = model->hasCP() ? model->CP() : 0;
            add.PMax = model->hasPMax() ? model->PMax() : 0;
            add.FTP = model->hasFTP() ? model->FTP() : 0;

            if (add.CP && add.WPrime) add.EI = add.WPrime / add.CP ;

            // so long as the important model derived values are sensible ...
            if (add.WPrime > 1000 && add.CP > 100) {
                printd("Estimates for %s - %s\n", add.from.toString().toStdString().c_str(), add.to.toString().toStdString().c_str());
                est << add;
            }

            //qDebug()<<add.to<<add.from<<model->code()<< "W'="<< model->WPrime() <<"CP="<< model->CP() <<"pMax="<<model->PMax();

            // set the wpk data
            model->setData(bestsWPK.aggregate());
            model->saveParameters(add.parameters); // save the computed parms

            add.wpk = true;
            add.from = begin;
            add.to = end;
            add.model = model->code();
            add.WPrime = model->hasWPrime() ? model->WPrime() : 0;
            add.CP = model->hasCP() ? model->CP() : 0;
            add.PMax = model->hasPMax() ? model->PMax() : 0;
            add.FTP = model->hasFTP() ? model->FTP() : 0;
            if (add.CP && add.WPrime) add.EI = add.WPrime / add.CP ;

            // so long as the model derived values are sensible ...
            if ((!model->hasWPrime() || add.WPrime > 10.0f) &&
                (!model->hasCP() || add.CP > 1.0f) &&
                (!model->hasPMax() || add.PMax > 1.0f) &&
                (!model->hasFTP() || add.FTP > 1.0f)) {
                printd("WPK Estimates for %s - %s\n", add.from.toString().toStdString().c_str(), add.to.toString().toStdString().c_str());
                est << add;
            }

            //qDebug()<<add.from<<model->code()<< "KG W'="<< model->WPrime() <<"CP="<< model->CP() <<"pMax="<<model->PMax();
        }

        // go forward a week
        date = date.addDays(7);
    }

    // add a dummy entry if we have no estimates to stop constantly trying to refresh
    if (est.count() == 0)  est << PDEstimate();

    // now update them
    lock.lock();
    estimates = est;
    lock.unlock();

    printd("Estimates end\n");
}
