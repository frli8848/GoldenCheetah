/*
 * Copyright (c) 2017 Mark Liversedge (liversedge@gmail.com)
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

#ifndef _GC_PythonChart_h
#define _GC_PythonChart_h 1

#include <PythonEmbed.h>

#include <QString>
#include <QDebug>
#include <QColor>
#include <QTextEdit>
#include <QScrollBar>
#include <QCheckBox>
#include <QSplitter>
#include <QByteArray>
#include <string.h>
#include <QWebEngineView>
#include <QUrl>
#include <QtCharts>

#include "GoldenCheetah.h"
#include "Context.h"
#include "Athlete.h"
#include "Colors.h"
#include "RCanvas.h"

// keep aligned to library.py
#define GC_CHART_LINE      1
#define GC_CHART_SCATTER   2
#define GC_CHART_BAR       3
#define GC_CHART_PIE       4

class PythonChart;

class PythonHost {
public:
    virtual PythonChart *chart() = 0;
    virtual bool readOnly() = 0;
};

// a console widget to type commands and display response
class PythonConsole : public QTextEdit {

    Q_OBJECT

signals:
    void getData(const QByteArray &data);

public slots:
    void configChanged(qint32);
    void rMessage(QString);

public:
    explicit PythonConsole(Context *context, PythonHost *pythonHost, QWidget *parent = 0);

    void putData(QString data);
    void putData(QColor color, QString data);
    void setLocalEchoEnabled(bool set);

    // return the current "line" of text
    QString currentLine();
    void setCurrentLine(QString);

    QStringList history;
    int hpos;
    QString chartid;

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void contextMenuEvent(QContextMenuEvent *e);

private:
    Context *context;
    bool localEchoEnabled;
    PythonHost *pythonHost;
    int promptStartIndex = 4;
};

// axis info, might become generic later (i.e. use in other charts)
class AxisInfo {
public:
        enum axisinfoType { CONTINUOUS=0,                 // Continious range
                            DATERANGE=1,                  // Date
                            TIME=2,                       // Duration, Time
                            CATEGORY=3                // labelled with categories
                          };
        typedef enum axisinfoType AxisInfoType;

        AxisInfo(Qt::Orientations orientation, QString name) : name(name), orientation(orientation) {
            miny=maxy=minx=maxx=0;
            fixed=log=false;
            visible=minorgrid=majorgrid=true;
            type=CONTINUOUS;
            axiscolor=labelcolor=GColor(CPLOTMARKER);
        }

        void point(double x, double y) {
            if (fixed) return;
            if (x>maxx) maxx=x;
            if (x<minx) minx=x;
            if (y>maxy) maxy=y;
            if (y<miny) miny=y;
        }

        double min() {
            if (orientation == Qt::Horizontal) return minx;
            else return miny;
        }
        double max() {
            if (orientation == Qt::Horizontal) return maxx;
            else return maxy;
        }

        Qt::AlignmentFlag locate() {
            return align;
        }

        // series we are associated with
        QList<QAbstractSeries*> series;

        // data is all public to avoid tedious get/set
        QString name;
        Qt::Orientations orientation;
        Qt::AlignmentFlag align;
        double miny, maxy, minx, maxx; // updated as we see points, set the range
        bool visible,fixed, log, minorgrid, majorgrid; // settings
        QColor labelcolor, axiscolor; // aesthetics
        QStringList categories;
        AxisInfoType type; // what type of axis is this?
};

// the chart
class PythonChart : public GcChartWindow, public PythonHost {

    Q_OBJECT

    Q_PROPERTY(QString script READ getScript WRITE setScript USER true)
    Q_PROPERTY(QString state READ getState WRITE setState USER true)
    Q_PROPERTY(bool showConsole READ showConsole WRITE setConsole USER true)
    Q_PROPERTY(bool asWeb READ asWeb WRITE setWeb USER true)

    public:
        PythonChart(Context *context, bool ridesummary);

        // reveal
        bool hasReveal() { return true; }
        QCheckBox *showCon, *web;

        // receives all the events
        QTextEdit *script;
        PythonConsole *console;
        QWidget *render;
        QVBoxLayout *renderlayout;

        // rendering via...
        QWebEngineView *canvas; // not yet!!
        QChartView *chartview;
        QChart *qchart;

        void emitUrl(QUrl x) { emit setUrl(x); }

        bool asWeb() const { return (web ? web->isChecked() : true); }
        void setWeb(bool);

        bool showConsole() const { return (showCon ? showCon->isChecked() : true); }
        void setConsole(bool);

        QString getScript() const;
        void setScript(QString);

        QString getState() const;
        void setState(QString);

        PythonChart *chart() { return this; }
        bool readOnly() { return true; }

    signals:
        void setUrl(QUrl);
        void emitChart(QString title, int type, bool animate);
        void emitCurve(QString name, QVector<double> xseries, QVector<double> yseries, QString xname, QString yname,
                      QStringList labels, QStringList colors,
                      int line, int symbol, int size, QString color, int opacity, bool opengl);
        void emitAxis(QString name, bool visible, int align, double min, double max,
                      int type, QString labelcolor, QString color, bool log, QStringList categories);

    public slots:
        void configChanged(qint32);
        void showConChanged(int state);
        void showWebChanged(int state);
        void runScript();
        void webpage(QUrl);
        static void execScript(PythonChart *);

        // post processing clean up / add decorations / helpers etc
        void polishChart();

        // set chart settings
        bool configChart(QString title, int type, bool animate) {

            if (chartview) {

                // if we changed the type, all series must go
                if (charttype != type) {
                    qchart->removeAllSeries();
                    curves.clear();
                    barseries=NULL;
                }

                // clear ALL axes
                foreach(QAbstractAxis *axis, qchart->axes(Qt::Vertical)) {
                    qchart->removeAxis(axis);
                    delete axis;
                }
                foreach(QAbstractAxis *axis, qchart->axes(Qt::Horizontal)) {
                    qchart->removeAxis(axis);
                    delete axis;
                }
                foreach(AxisInfo *axisinfo, axisinfos) delete axisinfo;
                axisinfos.clear();

                left=true;
                bottom=true;
                barsets.clear();

                // remember type
                charttype=type;

                // title is allowed to be blank
                qchart->setTitle(title);

                // would avoid animations as they get very tiresome and are not
                // generally transition animations, so add very little value
                // by default they are disabled anyway
                qchart->setAnimationOptions(animate ? QChart::SeriesAnimations : QChart::NoAnimation);

                return true;
            }
        }
        bool setCurve(QString name, QVector<double> xseries, QVector<double> yseries, QString xname, QString yname,
                      QStringList labels, QStringList colors,
                      int line, int symbol, int size, QString color, int opacity, bool opengl);

        bool configAxis(QString name, bool visible, int align, double min, double max,
                      int type, QString labelcolor, QString color, bool log, QStringList categories);

    protected:
        // enable stopping long running scripts
        bool eventFilter(QObject *, QEvent *e);

        QSplitter *splitter;
        QSplitter *leftsplitter;

    private:
        Context *context;
        QString text; // if Rtool not alive
        bool ridesummary;
        int charttype;

        // curves
        QMap<QString, QAbstractSeries *>curves;

        // axes
        QMap<QString, AxisInfo *>axisinfos;

        // barsets
        QList<QBarSet*> barsets;
        QBarSeries *barseries;

        // axis placement (before user interacts)
        // alternates as axis added
        bool left, bottom;
};


#endif
