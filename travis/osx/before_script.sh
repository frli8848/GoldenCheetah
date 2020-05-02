#!/bin/bash
set -ev

# D2XX
mkdir D2XX
cp /Volumes/release/D2XX/Object/10.5-10.7/x86_64/libftd2xx.1.2.2.dylib D2XX
sudo cp /Volumes/release/D2XX/Object/10.5-10.7/x86_64/libftd2xx.1.2.2.dylib /usr/local/lib
cp /Volumes/release/D2XX/bin/*.h D2XX
sed -i "" "s|libftd2xx.dylib|@executable_path/../Frameworks/libftd2xx.1.2.2.dylib|" src/FileIO/D2XX.cpp

# Python SIP
python3 --version
python3-config --prefix
curl -O https://www.riverbankcomputing.com/static/Downloads/sip/4.19.8/sip-4.19.8.tar.gz
tar xf sip-4.19.8.tar.gz
cd sip-4.19.8
python3 configure.py
make
sudo make install
cd ..

cp qwt/qwtconfig.pri.in qwt/qwtconfig.pri
cp src/gcconfig.pri.in src/gcconfig.pri
# Define GC version string, only for tagged builds
if [ -n "$TRAVIS_TAG" ]; then echo DEFINES += GC_VERSION=VERSION_STRING >> src/gcconfig.pri; fi
echo DEFINES += NOWEBKIT >> src/gcconfig.pri
sed -i "" "s|#\(CONFIG += release.*\)|\1 static |" src/gcconfig.pri
sed -i "" "s|#\(QMAKE_LRELEASE\).*|\1 += /usr/local/opt/qt5/bin/lrelease|" src/gcconfig.pri
sed -i "" "s|#\(QMAKE_CXXFLAGS\).*|\1_RELEASE += -mmacosx-version-min=10.7 -arch x86_64|" src/gcconfig.pri
sed -i "" "s|^#CloudDB|CloudDB|" src/gcconfig.pri
sed -i "" "s|^#LIBZ|LIBZ|" src/gcconfig.pri
sed -i "" "s|#\(SRMIO_INSTALL =.*\)|\1 /usr/local|" src/gcconfig.pri
sed -i "" "s|#\(D2XX_INCLUDE =.*\)|\1 ../D2XX|" src/gcconfig.pri
sed -i "" "s|#\(D2XX_LIBS    =.*\)|\1 -L../D2XX -lftd2xx.1.2.2|" src/gcconfig.pri
## Disable KML for now
#sed -i "" "s|#\(KML_INSTALL =\).*|\1 /usr/local|" src/gcconfig.pri
#sed -i "" "s|#\(KML_LIBS    =.*\)|\1 -L/usr/local/lib -lkmlxsd -lkmlregionator -lkmldom -lkmlconvenience -lkmlengine -lkmlbase -lexpect|" src/gcconfig.pri
sed -i "" "s|#\(ICAL_INSTALL =.*\)|\1 /usr/local|" src/gcconfig.pri
sed -i "" "s|#\(ICAL_LIBS    =.*\)|\1 -L/usr/local/lib -lical|" src/gcconfig.pri
sed -i "" "s|#\(LIBUSB_INSTALL =\).*|\1 /usr/local|" src/gcconfig.pri
sed -i "" "s|#\(LIBUSB_LIBS    =.*\)|\1 -L/usr/local/lib -lusb-1.0|" src/gcconfig.pri
sed -i "" "s|#\(LIBUSB_USE_V_1 = true.*\)|\1|" src/gcconfig.pri
sed -i "" "s|#\(SAMPLERATE_INSTALL =\).*|\1 /usr/local|" src/gcconfig.pri
sed -i "" "s|#\(SAMPLERATE_LIBS =\).*|\1 -L/usr/local/lib -lsamplerate|" src/gcconfig.pri
sed -i "" "s|#\(LMFIT_INSTALL =\).*|\1 /usr/local|" src/gcconfig.pri
sed -i "" "s|#\(DEFINES += GC_HAVE_LION*\)|\1|" src/gcconfig.pri
sed -i "" "s|#\(HTPATH = ../httpserver.*\)|\1 |" src/gcconfig.pri
sed -i "" "s|#\(DEFINES += GC_WANT_ROBOT.*\)|\1 |" src/gcconfig.pri
##sed -i "" "s|\(DEFINES += GC_VIDEO_NONE.*\)|#\1 |" src/gcconfig.pri ## we want this for now till AVKit fixup or an alternative is proved to work
##sed -i "" "s|#\(DEFINES += GC_VIDEO_QT5.*\)|\1 |" src/gcconfig.pri  ## this amkes Train mode to crash in v3.5
##Issues with c++11 and stdlib on travis and dependencies
sed -i "" "s|#\(DEFINES += GC_WANT_R.*\)|\1 |" src/gcconfig.pri
echo "QMAKE_CFLAGS_RELEASE += -mmacosx-version-min=10.7 -arch x86_64" >> src/gcconfig.pri
# Python (avoiding colision between GC Context.h and Python context.h)
echo DEFINES += GC_WANT_PYTHON >> src/gcconfig.pri
echo PYTHONINCLUDES = -ICore `python3-config --includes` >> src/gcconfig.pri
echo PYTHONLIBS = `python3-config --ldflags` >> src/gcconfig.pri

# Patch Secrets.h
sed -i "" "s/__GC_GOOGLE_CALENDAR_CLIENT_SECRET__/"$GC_GOOGLE_CALENDAR_CLIENT_SECRET"/" src/Core/Secrets.h
sed -i "" "s/__GC_STRAVA_CLIENT_SECRET__/"$GC_STRAVA_CLIENT_SECRET"/" src/Core/Secrets.h
sed -i "" "s/__GC_DROPBOX_CLIENT_SECRET__/"$GC_DROPBOX_CLIENT_SECRET"/" src/Core/Secrets.h
sed -i "" "s/__GC_CYCLINGANALYTICS_CLIENT_SECRET__/"$GC_CYCLINGANALYTICS_CLIENT_SECRET"/" src/Core/Secrets.h
sed -i "" "s/__GC_TWITTER_CONSUMER_SECRET__/"$GC_TWITTER_CONSUMER_SECRET"/" src/Core/Secrets.h
sed -i "" "s/__GC_DROPBOX_CLIENT_ID__/"$GC_DROPBOX_CLIENT_ID"/" src/Core/Secrets.h
sed -i "" "s/__GC_MAPQUESTAPI_KEY__/"$GC_MAPQUESTAPI_KEY"/" src/Core/Secrets.h
sed -i "" "s/__GC_CLOUD_DB_BASIC_AUTH__/"$GC_CLOUD_DB_BASIC_AUTH"/" src/Core/Secrets.h
sed -i "" "s/__GC_CLOUD_DB_APP_NAME__/"$GC_CLOUD_DB_APP_NAME"/" src/Core/Secrets.h
sed -i "" "s/__GC_GOOGLE_DRIVE_CLIENT_ID__/"$GC_GOOGLE_DRIVE_CLIENT_ID"/" src/Core/Secrets.h
sed -i "" "s/__GC_GOOGLE_DRIVE_CLIENT_SECRET__/"$GC_GOOGLE_DRIVE_CLIENT_SECRET"/" src/Core/Secrets.h
sed -i "" "s/__GC_GOOGLE_DRIVE_API_KEY__/"$GC_GOOGLE_DRIVE_API_KEY"/" src/Core/Secrets.h
sed -i "" "s/__GC_TODAYSPLAN_CLIENT_SECRET__/"$GC_TODAYSPLAN_CLIENT_SECRET"/" src/Core/Secrets.h
sed -i "" "s/__GC_WITHINGS_CONSUMER_SECRET__/"$GC_WITHINGS_CONSUMER_SECRET"/" src/Core/Secrets.h
sed -i "" "s/__GC_NOKIA_CLIENT_SECRET__/"$GC_NOKIA_CLIENT_SECRET"/" src/Core/Secrets.h
sed -i "" "s/__GC_SPORTTRACKS_CLIENT_SECRET__/"$GC_SPORTTRACKS_CLIENT_SECRET"/" src/Core/Secrets.h
sed -i "" "s/OPENDATA_DISABLE/OPENDATA_ENABLE/" src/Core/Secrets.h
sed -i "" "s/__GC_CLOUD_OPENDATA_SECRET__/"$GC_CLOUD_OPENDATA_SECRET"/" src/Core/Secrets.h
cat src/gcconfig.pri
# update translations
/usr/local/opt/qt5/bin/lupdate src/src.pro
exit
