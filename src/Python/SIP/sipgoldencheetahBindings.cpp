/*
 * Interface wrapper code.
 *
 * Generated by SIP 4.19.8
 */

#include "sipAPIgoldencheetah.h"

#line 110 "goldencheetah.sip"
//#include "Bindings.h"
#line 12 "./sipgoldencheetahBindings.cpp"

#line 28 "goldencheetah.sip"
#include <qstring.h>
#line 16 "./sipgoldencheetahBindings.cpp"
#line 59 "goldencheetah.sip"
#include "Bindings.h"
#line 19 "./sipgoldencheetahBindings.cpp"


extern "C" {static PyObject *meth_Bindings_threadid(PyObject *, PyObject *);}
static PyObject *meth_Bindings_threadid(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;

    {
        const  ::Bindings *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "B", &sipSelf, sipType_Bindings, &sipCpp))
        {
            long sipRes;

            sipRes = sipCpp->threadid();

            return PyLong_FromLong(sipRes);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_threadid, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_build(PyObject *, PyObject *);}
static PyObject *meth_Bindings_build(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;

    {
        const  ::Bindings *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "B", &sipSelf, sipType_Bindings, &sipCpp))
        {
            int sipRes;

            sipRes = sipCpp->build();

            return SIPLong_FromLong(sipRes);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_build, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_version(PyObject *, PyObject *);}
static PyObject *meth_Bindings_version(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;

    {
        const  ::Bindings *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "B", &sipSelf, sipType_Bindings, &sipCpp))
        {
             ::QString*sipRes;

            sipRes = new  ::QString(sipCpp->version());

            return sipConvertFromNewType(sipRes,sipType_QString,NULL);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_version, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_webpage(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_webpage(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
         ::QString* a0;
        int a0State = 0;
        const  ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_url,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "BJ1", &sipSelf, sipType_Bindings, &sipCpp, sipType_QString,&a0, &a0State))
        {
            int sipRes;

            sipRes = sipCpp->webpage(*a0);
            sipReleaseType(a0,sipType_QString,a0State);

            return SIPLong_FromLong(sipRes);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_webpage, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_result(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_result(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
        double a0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_value,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "Bd", &sipSelf, sipType_Bindings, &sipCpp, &a0))
        {
            sipCpp->result(a0);

            Py_INCREF(Py_None);
            return Py_None;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_result, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_athlete(PyObject *, PyObject *);}
static PyObject *meth_Bindings_athlete(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;

    {
         ::Bindings *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "B", &sipSelf, sipType_Bindings, &sipCpp))
        {
            PyObject * sipRes;

            sipRes = sipCpp->athlete();

            return sipRes;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_athlete, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_athleteZones(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_athleteZones(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
        PyObject * a0 = 0;
         ::QString a1def = "";
         ::QString* a1 = &a1def;
        int a1State = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_date,
            sipName_sport,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|P0J1", &sipSelf, sipType_Bindings, &sipCpp, &a0, sipType_QString,&a1, &a1State))
        {
            PyObject * sipRes;

            sipRes = sipCpp->athleteZones(a0,*a1);
            sipReleaseType(a1,sipType_QString,a1State);

            return sipRes;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_athleteZones, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_activities(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_activities(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
         ::QString a0def = QString();
         ::QString* a0 = &a0def;
        int a0State = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_filter,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|J1", &sipSelf, sipType_Bindings, &sipCpp, sipType_QString,&a0, &a0State))
        {
            PyObject * sipRes;

            sipRes = sipCpp->activities(*a0);
            sipReleaseType(a0,sipType_QString,a0State);

            return sipRes;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_activities, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_season(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_season(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
        bool a0 = 0;
        bool a1 = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_all,
            sipName_compare,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|bb", &sipSelf, sipType_Bindings, &sipCpp, &a0, &a1))
        {
            PyObject * sipRes;

            sipRes = sipCpp->season(a0,a1);

            return sipRes;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_season, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_seriesPresent(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_seriesPresent(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
        int a0 = 10;
        PyObject * a1 = 0;
        const  ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_type,
            sipName_activity,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|iP0", &sipSelf, sipType_Bindings, &sipCpp, &a0, &a1))
        {
            bool sipRes;

            sipRes = sipCpp->seriesPresent(a0,a1);

            return PyBool_FromLong(sipRes);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_seriesPresent, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_seriesName(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_seriesName(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
        int a0 = 10;
        const  ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_type,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|i", &sipSelf, sipType_Bindings, &sipCpp, &a0))
        {
             ::QString*sipRes;

            sipRes = new  ::QString(sipCpp->seriesName(a0));

            return sipConvertFromNewType(sipRes,sipType_QString,NULL);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_seriesName, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_seriesLast(PyObject *, PyObject *);}
static PyObject *meth_Bindings_seriesLast(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;

    {
        const  ::Bindings *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "B", &sipSelf, sipType_Bindings, &sipCpp))
        {
            int sipRes;

            sipRes = sipCpp->seriesLast();

            return SIPLong_FromLong(sipRes);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_seriesLast, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_series(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_series(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
        int a0 = 10;
        PyObject * a1 = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_type,
            sipName_activity,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|iP0", &sipSelf, sipType_Bindings, &sipCpp, &a0, &a1))
        {
             ::PythonDataSeries*sipRes;

            sipRes = new  ::PythonDataSeries(sipCpp->series(a0,a1));

            return sipConvertFromNewType(sipRes,sipType_PythonDataSeries,Py_None);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_series, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_activityWbal(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_activityWbal(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
        PyObject * a0 = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_activity,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|P0", &sipSelf, sipType_Bindings, &sipCpp, &a0))
        {
             ::PythonDataSeries*sipRes;

            sipRes = new  ::PythonDataSeries(sipCpp->activityWbal(a0));

            return sipConvertFromNewType(sipRes,sipType_PythonDataSeries,Py_None);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_activityWbal, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_activityXdata(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_activityXdata(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
         ::QString* a0;
        int a0State = 0;
         ::QString* a1;
        int a1State = 0;
         ::QString a2def = "repeat";
         ::QString* a2 = &a2def;
        int a2State = 0;
        PyObject * a3 = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_name,
            sipName_series,
            sipName_join,
            sipName_activity,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "BJ1J1|J1P0", &sipSelf, sipType_Bindings, &sipCpp, sipType_QString,&a0, &a0State, sipType_QString,&a1, &a1State, sipType_QString,&a2, &a2State, &a3))
        {
             ::PythonDataSeries*sipRes;

            sipRes = new  ::PythonDataSeries(sipCpp->activityXdata(*a0,*a1,*a2,a3));
            sipReleaseType(a0,sipType_QString,a0State);
            sipReleaseType(a1,sipType_QString,a1State);
            sipReleaseType(a2,sipType_QString,a2State);

            return sipConvertFromNewType(sipRes,sipType_PythonDataSeries,Py_None);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_activityXdata, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_activityXdataSeries(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_activityXdataSeries(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
         ::QString* a0;
        int a0State = 0;
         ::QString* a1;
        int a1State = 0;
        PyObject * a2 = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_name,
            sipName_series,
            sipName_activity,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "BJ1J1|P0", &sipSelf, sipType_Bindings, &sipCpp, sipType_QString,&a0, &a0State, sipType_QString,&a1, &a1State, &a2))
        {
             ::PythonDataSeries*sipRes;

            sipRes = new  ::PythonDataSeries(sipCpp->activityXdataSeries(*a0,*a1,a2));
            sipReleaseType(a0,sipType_QString,a0State);
            sipReleaseType(a1,sipType_QString,a1State);

            return sipConvertFromNewType(sipRes,sipType_PythonDataSeries,Py_None);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_activityXdataSeries, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_activityXdataNames(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_activityXdataNames(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
         ::QString a0def = QString();
         ::QString* a0 = &a0def;
        int a0State = 0;
        PyObject * a1 = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_name,
            sipName_activity,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|J1P0", &sipSelf, sipType_Bindings, &sipCpp, sipType_QString,&a0, &a0State, &a1))
        {
            PyObject * sipRes;

            sipRes = sipCpp->activityXdataNames(*a0,a1);
            sipReleaseType(a0,sipType_QString,a0State);

            return sipRes;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_activityXdataNames, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_activityMetrics(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_activityMetrics(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
        bool a0 = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_compare,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|b", &sipSelf, sipType_Bindings, &sipCpp, &a0))
        {
            PyObject * sipRes;

            sipRes = sipCpp->activityMetrics(a0);

            return sipRes;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_activityMetrics, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_seasonMetrics(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_seasonMetrics(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
        bool a0 = 0;
         ::QString a1def = QString();
         ::QString* a1 = &a1def;
        int a1State = 0;
        bool a2 = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_all,
            sipName_filter,
            sipName_compare,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|bJ1b", &sipSelf, sipType_Bindings, &sipCpp, &a0, sipType_QString,&a1, &a1State, &a2))
        {
            PyObject * sipRes;

            sipRes = sipCpp->seasonMetrics(a0,*a1,a2);
            sipReleaseType(a1,sipType_QString,a1State);

            return sipRes;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_seasonMetrics, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_metrics(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_metrics(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
         ::QString* a0;
        int a0State = 0;
        bool a1 = 0;
         ::QString a2def = QString();
         ::QString* a2 = &a2def;
        int a2State = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_metric,
            sipName_all,
            sipName_filter,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "BJ1|bJ1", &sipSelf, sipType_Bindings, &sipCpp, sipType_QString,&a0, &a0State, &a1, sipType_QString,&a2, &a2State))
        {
             ::PythonDataSeries*sipRes;

            sipRes = sipCpp->metrics(*a0,a1,*a2);
            sipReleaseType(a0,sipType_QString,a0State);
            sipReleaseType(a2,sipType_QString,a2State);

            return sipConvertFromType(sipRes,sipType_PythonDataSeries,Py_None);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_metrics, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_seasonPmc(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_seasonPmc(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
        bool a0 = 0;
         ::QString a1def = QString("BikeStress");
         ::QString* a1 = &a1def;
        int a1State = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_all,
            sipName_metric,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|bJ1", &sipSelf, sipType_Bindings, &sipCpp, &a0, sipType_QString,&a1, &a1State))
        {
            PyObject * sipRes;

            sipRes = sipCpp->seasonPmc(a0,*a1);
            sipReleaseType(a1,sipType_QString,a1State);

            return sipRes;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_seasonPmc, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_seasonMeasures(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_seasonMeasures(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
        bool a0 = 0;
         ::QString a1def = QString("Body");
         ::QString* a1 = &a1def;
        int a1State = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_all,
            sipName_group,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|bJ1", &sipSelf, sipType_Bindings, &sipCpp, &a0, sipType_QString,&a1, &a1State))
        {
            PyObject * sipRes;

            sipRes = sipCpp->seasonMeasures(a0,*a1);
            sipReleaseType(a1,sipType_QString,a1State);

            return sipRes;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_seasonMeasures, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_activityMeanmax(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_activityMeanmax(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
        bool a0 = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_compare,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|b", &sipSelf, sipType_Bindings, &sipCpp, &a0))
        {
            PyObject * sipRes;

            sipRes = sipCpp->activityMeanmax(a0);

            return sipRes;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_activityMeanmax, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_seasonMeanmax(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_seasonMeanmax(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
        bool a0 = 0;
         ::QString a1def = QString();
         ::QString* a1 = &a1def;
        int a1State = 0;
        bool a2 = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_all,
            sipName_filter,
            sipName_compare,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|bJ1b", &sipSelf, sipType_Bindings, &sipCpp, &a0, sipType_QString,&a1, &a1State, &a2))
        {
            PyObject * sipRes;

            sipRes = sipCpp->seasonMeanmax(a0,*a1,a2);
            sipReleaseType(a1,sipType_QString,a1State);

            return sipRes;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_seasonMeanmax, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_seasonPeaks(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_seasonPeaks(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
         ::QString* a0;
        int a0State = 0;
        int a1;
        bool a2 = 0;
         ::QString a3def = QString();
         ::QString* a3 = &a3def;
        int a3State = 0;
        bool a4 = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_series,
            sipName_duration,
            sipName_all,
            sipName_filter,
            sipName_compare,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "BJ1i|bJ1b", &sipSelf, sipType_Bindings, &sipCpp, sipType_QString,&a0, &a0State, &a1, &a2, sipType_QString,&a3, &a3State, &a4))
        {
            PyObject * sipRes;

            sipRes = sipCpp->seasonPeaks(*a0,a1,a2,*a3,a4);
            sipReleaseType(a0,sipType_QString,a0State);
            sipReleaseType(a3,sipType_QString,a3State);

            return sipRes;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_seasonPeaks, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_seasonIntervals(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_seasonIntervals(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
         ::QString a0def = QString();
         ::QString* a0 = &a0def;
        int a0State = 0;
        bool a1 = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_type,
            sipName_compare,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|J1b", &sipSelf, sipType_Bindings, &sipCpp, sipType_QString,&a0, &a0State, &a1))
        {
            PyObject * sipRes;

            sipRes = sipCpp->seasonIntervals(*a0,a1);
            sipReleaseType(a0,sipType_QString,a0State);

            return sipRes;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_seasonIntervals, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_Bindings_activityIntervals(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_Bindings_activityIntervals(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
         ::QString a0def = QString();
         ::QString* a0 = &a0def;
        int a0State = 0;
        PyObject * a1 = 0;
         ::Bindings *sipCpp;

        static const char *sipKwdList[] = {
            sipName_type,
            sipName_activity,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|J1P0", &sipSelf, sipType_Bindings, &sipCpp, sipType_QString,&a0, &a0State, &a1))
        {
            PyObject * sipRes;

            sipRes = sipCpp->activityIntervals(*a0,a1);
            sipReleaseType(a0,sipType_QString,a0State);

            return sipRes;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_Bindings, sipName_activityIntervals, NULL);

    return NULL;
}


/* Call the instance's destructor. */
extern "C" {static void release_Bindings(void *, int);}
static void release_Bindings(void *sipCppV, int)
{
    delete reinterpret_cast< ::Bindings *>(sipCppV);
}


extern "C" {static void assign_Bindings(void *, SIP_SSIZE_T, void *);}
static void assign_Bindings(void *sipDst, SIP_SSIZE_T sipDstIdx, void *sipSrc)
{
    reinterpret_cast< ::Bindings *>(sipDst)[sipDstIdx] = *reinterpret_cast< ::Bindings *>(sipSrc);
}


extern "C" {static void *array_Bindings(SIP_SSIZE_T);}
static void *array_Bindings(SIP_SSIZE_T sipNrElem)
{
    return new  ::Bindings[sipNrElem];
}


extern "C" {static void *copy_Bindings(const void *, SIP_SSIZE_T);}
static void *copy_Bindings(const void *sipSrc, SIP_SSIZE_T sipSrcIdx)
{
    return new  ::Bindings(reinterpret_cast<const  ::Bindings *>(sipSrc)[sipSrcIdx]);
}


extern "C" {static void dealloc_Bindings(sipSimpleWrapper *);}
static void dealloc_Bindings(sipSimpleWrapper *sipSelf)
{
    if (sipIsOwnedByPython(sipSelf))
    {
        release_Bindings(sipGetAddress(sipSelf), 0);
    }
}


extern "C" {static void *init_type_Bindings(sipSimpleWrapper *, PyObject *, PyObject *, PyObject **, PyObject **, PyObject **);}
static void *init_type_Bindings(sipSimpleWrapper *, PyObject *sipArgs, PyObject *sipKwds, PyObject **sipUnused, PyObject **, PyObject **sipParseErr)
{
     ::Bindings *sipCpp = 0;

    {
        if (sipParseKwdArgs(sipParseErr, sipArgs, sipKwds, NULL, sipUnused, ""))
        {
            sipCpp = new  ::Bindings();

            return sipCpp;
        }
    }

    {
        const  ::Bindings* a0;

        if (sipParseKwdArgs(sipParseErr, sipArgs, sipKwds, NULL, sipUnused, "J9", sipType_Bindings, &a0))
        {
            sipCpp = new  ::Bindings(*a0);

            return sipCpp;
        }
    }

    return NULL;
}


static PyMethodDef methods_Bindings[] = {
    {SIP_MLNAME_CAST(sipName_activities), (PyCFunction)meth_Bindings_activities, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_activityIntervals), (PyCFunction)meth_Bindings_activityIntervals, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_activityMeanmax), (PyCFunction)meth_Bindings_activityMeanmax, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_activityMetrics), (PyCFunction)meth_Bindings_activityMetrics, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_activityWbal), (PyCFunction)meth_Bindings_activityWbal, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_activityXdata), (PyCFunction)meth_Bindings_activityXdata, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_activityXdataNames), (PyCFunction)meth_Bindings_activityXdataNames, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_activityXdataSeries), (PyCFunction)meth_Bindings_activityXdataSeries, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_athlete), meth_Bindings_athlete, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_athleteZones), (PyCFunction)meth_Bindings_athleteZones, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_build), meth_Bindings_build, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_metrics), (PyCFunction)meth_Bindings_metrics, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_result), (PyCFunction)meth_Bindings_result, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_season), (PyCFunction)meth_Bindings_season, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_seasonIntervals), (PyCFunction)meth_Bindings_seasonIntervals, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_seasonMeanmax), (PyCFunction)meth_Bindings_seasonMeanmax, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_seasonMeasures), (PyCFunction)meth_Bindings_seasonMeasures, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_seasonMetrics), (PyCFunction)meth_Bindings_seasonMetrics, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_seasonPeaks), (PyCFunction)meth_Bindings_seasonPeaks, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_seasonPmc), (PyCFunction)meth_Bindings_seasonPmc, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_series), (PyCFunction)meth_Bindings_series, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_seriesLast), meth_Bindings_seriesLast, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_seriesName), (PyCFunction)meth_Bindings_seriesName, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_seriesPresent), (PyCFunction)meth_Bindings_seriesPresent, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_threadid), meth_Bindings_threadid, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_version), meth_Bindings_version, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_webpage), (PyCFunction)meth_Bindings_webpage, METH_VARARGS|METH_KEYWORDS, NULL}
};


sipClassTypeDef sipTypeDef_goldencheetah_Bindings = {
    {
        -1,
        0,
        0,
        SIP_TYPE_CLASS,
        sipNameNr_Bindings,
        {0},
        0
    },
    {
        sipNameNr_Bindings,
        {0, 0, 1},
        27, methods_Bindings,
        0, 0,
        0, 0,
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    },
    0,
    -1,
    -1,
    0,
    0,
    init_type_Bindings,
    0,
    0,
#if PY_MAJOR_VERSION >= 3
    0,
    0,
#else
    0,
    0,
    0,
    0,
#endif
    dealloc_Bindings,
    assign_Bindings,
    array_Bindings,
    copy_Bindings,
    release_Bindings,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};
