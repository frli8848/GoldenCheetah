project (GoldenCheetah)

# See http://doc.qt.io/qt-5/cmake-manual.html
cmake_minimum_required(VERSION 3.4)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Grab the version number from the git repo.
#
# http://brianmilco.blogspot.no/2012/11/cmake-automatically-use-git-tags-as.html 
include(GetGitRevisionDescription)
#git_describe(VERSION --tags --dirty=-dirty)
git_describe(VERSION tag)

# Parse the version information into pieces (version tags must have the format v0.3.4)
string(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1" VERSION_SHA1 "${VERSION}")
set(DL_VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

#get_git_head_revision(GIT_REFSPEC GIT_SHA1)

message(STATUS "GoldenCheetah version: ${DL_VERSION_SHORT} [${VERSION_SHA1}]")

###############################################################################
#                                                                             #
#              ***  SECTION ONE - CORE CONFIGURATION  ***                     #
#                                                                             #
#                                                                             #
###############################################################################

# Enable when WebKit is not available (e.g. QT >= 5.6) TODO let cmake probe for Qt version instead?
option (NOWEBKIT "Enable when WebKit is not available (e.g. QT >= 5.6)" OFF)
if (NOWEBKIT)
  add_definitions( -DNOWEBKIT )
endif (NOWEBKIT)

# Enable if you want an R chart
# You will need R installed along with the Rcpp and RInside
# packages. There is an R script in the `util' directory that
# can be run to install these packages; see it for more info.
option (GC_WANT_R "Enable if you want an R chart" OFF)
if (GC_WANT_R)
  #find_package (R)
  add_definitions( -DGC_WANT_R )
endif (GC_WANT_R)

# Enable if you want Python charting / ML etc
# You will need Python Development tools installed
# PYTHONHEADER goes directly into the header file so
# make sure you escape the braces etc
#
# Libs needed can typically be found by calling e.g
# python3.6-config --libs
#
# below 3 lines work well on Linux style OS
#DEFINES += GC_WANT_PYTHON
#PYTHONINCLUDES = -I/usr/include/python3.6
#PYTHONLIBS = -L/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu -lpython3.6m
#
# below 3 lines work well on Windows
#DEFINES += GC_WANT_PYTHON
#PYTHONINCLUDES = -I\"C:\Program Files\Python36\include\"
#PYTHONLIBS = -L\"C:\Program Files\Python36\libs\" -lpython36
#
#Below work ok on MacOS High Sierra
#DEFINES += GC_WANT_PYTHON
#PYTHONINCLUDES = -I/Library/Frameworks/Python.framework/Versions/3.6/include/python3.6m
#PYTHONLIBS = -L/Library/Frameworks/Python.framework/Versions/3.6/lib -lpython3.6m

option (GC_WANT_PYTHON "Enable if you want Python charting / ML etc" OFF)
if (GC_WANT_PYTHON)
  find_package (PythonLibs 3.6 REQUIRED)
  if (PYTHONLIBS_FOUND)
    message (STATUS "Python lib dir:${PYTHON_LIBRARIES}")
    message (STATUS "Python include dir: ${YTHON_INCLUDE_DIRS}")
    message (STATUS "Python lib version: ${PYTHONLIBS_VERSION_STRING}")
    add_definitions( -DGC_WANT_PYTHON )
  endif (PYTHONLIBS_FOUND)
endif (GC_WANT_PYTHON)

# Global conf file name: If you'd like to use a different global config file
# name than the default (e.g. for testing purposes), set it here.
#DEFINES += GC_SETTINGS_APP=\\\"GoldenCheetahTest\\\"

# If you want a console window to appear on Windows machines
# then uncomment the following two lines.
#ONFIG += console
#QMAKE_LFLAGS = -mwindows

# To compile translation you need QT tool - lrelease
# If it is not found using he defaults in src/src.pro
# then set the full path and filename here.
#QMAKE_LRELEASE = /usr/bin/lrelease

# MSVC needs the WINDOWS KIT libraries for the memory model you are building
#WINKIT_INSTALL= "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64"

# Let us know where flex and bison are installed.
# You may need to specify the full path if things don't work.
#QMAKE_LEX  = flex
#QMAKE_YACC = bison
# If you're compiling with nmake and VC then you
# will likely also use win_flex and win_bison
# so uncomment below
#QMAKE_LEX = win_flex
#QMAKE_YACC = win_bison
#win32 {
#  QMAKE_YACC = bison --file-prefix=y -t
#  QMAKE_MOVE = cmd /c move
#  QMAKE_DEL_FILE = rm -f
#}

# If you want SRM download support you must install SRMIO
#     http://www.zuto.de/project/srmio/
# Set path to the root of the SRMIO installation
# If you installed in /usr/local/srmio then set
# SRMIO_INSTALL = /usr/local/srmio
# This will automatically set:
# SRMIO_INCLUDE = $${SRMIO_INSTALL}/include 
# SRMIO_LIBS    = $${SRMIO_INSTALL}/lib/libsrmio.a
# You may override the INCLUDE and LIB files if you like.
# You *must* define SRMIO_INSTALL to use this feature.
#SRMIO_INSTALL = 
#SRMIO_INCLUDE = 
#SRMIO_LIBS    = 

# If you want Twitter support you must install a QT OAUTH library kQoAUTH
#     http://github.com/kypeli/kQOAuth (Version >= 0.98 - tested with 0.98))
# Set path to the root of the OAUTH installation
# If you installed in /usr/local/kqoauth then set
# KQOAUTH_INSTALL = /usr/local/kqoauth
# This will automatically set:
# KQOAUTH_INCLUDE = $${KQOAUTH_INSTALL}/src
# KQOAUTH_LIBS    = $${KQOAUTH_INSTALL}/lib/libkqoauthd0.a   // if in DEBUG mode
# KQOAUTH_LIBS    = $${KQOAUTH_INSTALL}/lib/libkqoauth0.a    // if in RELEASE mode
# You may override the INCLUDE and LIB files if you like.
# You *must* define KQOAUTH_INSTALL to use this feature.

#KQOAUTH_INSTALL = 
#KQOAUTH_INCLUDE =
#KQOAUTH_LIBS =

# For TrainingPeaks.com upload/download you need to install the Qt Soap add-on
#     http://qt.nokia.com/products/appdev/add-on-products/catalog/4/Utilities/qtsoap
# If qtsoap.pri is install in /usr/local/qtsolutions/soap/ then set
# QTSOAP_INSTALL = /usr/local/qtsolutions/soap
# By default we use a copy of Qt Soap in the GIT repository.
# You *must* define QTSOAP_INSTALL to use a different version than this.
#QTSOAP_INSTALL = 

# If you want support for Google Earth .kml files then you need
# to install the Google libkml library
#
# http://code.google.com/p/libkml/
# or on Linux sudo apt-get install libkml-dev
#
# then set the following variable appropriately
# to the root of the libs/include path
#KML_INSTALL = /usr/local
#KML_INCLUDE = 
#KML_LIBS    = 
# Since KML also requires BOOST you will need to install
# that too and then set BOOST_INCLUDE to that location
# If the files are in /usr/include/boost then set
#BOOST_INCLUDE = /usr/include
#Additionally, on MAC the latest libs also need the following
#QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
#QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64
#LIBS += -lexpat -luriparser -lminizip

# If you want support for downloading from iCal calendars you will need libical
#     http://sourceforge.net/projects/freeassociation/
# Set path to the root of the libical installation
# If you installed in /usr/local/libical then set
# ICAL_INSTALL = /usr/local/libical
# This will automatically set:
# ICAL_INCLUDE = $${ICAL_INSTALL}/include 
# ICAL_LIBS    = $${ICAL_INSTALL}/lib/libical.a
# You may override the INCLUDE and LIB files if you like.
# You *must* define ICAL_INSTALL to use this feature.
#ICAL_INSTALL = 
#ICAL_INCLUDE = 
#ICAL_LIBS    =
#
# libical has moved to GitHub: http://libical.github.io/libical/ 

option (GC_WANT_ICAL "Enable if you want support for downloading from iCal calendars" OFF)
if (GC_WANT_LIBICAL)
  #find_package (LIBICAL)
  add_definitions( -DICAL_INSTALL )
endif (GC_WANT_LIBICAL)


# If you want support for using USB1 sticks in Train View on Windows
# then install the SiLabs USBXpress Software Development Kit (SDK)
#     http://www.silabs.com/products/mcu/Pages/USBXpress.aspx
# and set the following to the 'Host' directory within the SDK
# USBXPRESS_INSTALL = /c/SiLabs/MCU/USBXpress/USBXpress_API/Host/
# You may override the INCLUDE and LIB files if you like.
# You *must* define USBXPRESS_INSTALL to use this feature.
#USBXPRESS_INSTALL = 
#USBXPRESS_INCLUDE = 
#USBXPRESS_LIBS    = 

# If you want support for using USB2 sticks in Train View on Linux or Windows
# then you need to install libusb (Linux) version 0.1.12 
# or libusb-win32 (Windows) version 1.2.6.0
# For Linux builds download: (There is a copy in the contrib directory)
#     http://prdownloads.sourceforge.net/libusb/libusb-0.1.12.tar.gz
# For Windows builds download:
#     ttps://sourceforge.net/projects/libusb-win32/files/libusb-win32-releases/1.2.6.0/
# You may override the INCLUDE and LIB files if you like.
# You *must* define LIBUSB_INSTALL to use this feature.
#LIBUSB_INSTALL = /usr/local
#LIBUSB_INCLUDE = 
#LIBUSB_LIBS    = 

# if you want video playback on training mode then
# download and install vlc (videolan) from
# ftp.videolan.org/pub/vlc/1.1.8 or http://download.videolan.org/vlc/ for 
# your platform there are sdks for Mac and Windows. On Linux you
# will need to use the latest distro (e.g. Meerkat
# on Ubuntu) to be sure apt-get installs the latest
# builds (we need 1.1.8 or higher).
# Set path to the root of the VLC installation
# If the are installed in /usr/local/vlc then set
# VLC_INSTALL = /usr/local/vlc
# This will automatically set (Windows and Unix):
# VLC_INCLUDE = $${VLC_INSTALL}/include 
# For Windows
# VLC_LIBS    = $${VLC_INSTALL}/lib/libvlc.dll.a
# For Unix
# VLC_LIBS    = -lvlc
# You may override the INCLUDE and LIB files if you like.
# You *must* define VLC_INSTALL to use this feature.
#VLC_INSTALL = 
#VLC_INCLUDE = 
#VLC_LIBS    = 

# *** Mac users NOTE ***
# On MAC you don't need libvlc since we use the
# native QTKit (OSX framework) for video playback
# using Quicktime and on 10.6 or higher Quicktime X
#

# if you want to resample with high fidelity we can use the
# libsamplerate libraries, this is used in RideFile::resample()
# if you don't resample (e.g. export or merge with new recording
# intervals) then don't bother.
#
# Mainly tested on Linux, compilation on Windows requires
# some modifications in the build process to build with MSVC2015 
# Code is available at: http://www.mega-nerd.com/SRC/
#
#SAMPLERATE_INSTALL = /usr/local
#SAMPLERATE_INCLUDE = /usr/local/include
#SAMPLERATE_LIBS = /usr/local/lib/libsamplerate.a

# If your system has PKG_CONFIG, QT can use this to get dependent libraries.
# Add the names of libraries with PKG_CONFIG information.
# eg. PKGCONFIG = oauth libical
# Uncomment the following two lines to enable.
#CONFIG   += link_pkgconfig
#PKGCONFIG = 

# We use LMFit for model fitting Banister models
# download from http://apps.jcns.fz-juelich.de/src/lmfit/
#LMFIT_INSTALL = /usr/local

# If your QT build includes its own local compress libs
# then you should comment the line below, otherwise you
# will need to have the compress libraries installed
# separately. 
#LIBZ_INCLUDE =
#LIBZ_LIBS    = -lz

#macx {
#    # Uncomment this line to build with OS X Tiger support on a Leopard system:
#    #QMAKE_MAC_SDK=/Developer/SDKs/MacOSX10.4u.sdk
#
#    # Uncomment this line to build a OS X universal binary:
#    #CONFIG+=x86 ppc
#
#    # Uncomment this line if you have SDK 10.7 or higher
#    #DEFINES += GC_HAVE_LION
#
#    #uncomment below if you are running on the 10.9 developer preview
#    #INCLUDEPATH += /Library/Developer/CommandLineTools/SDKs/MacOSX10.9.sdk/usr/include/ 
#}

# uncomment below for R integration via webservices
#HTPATH = ../httpserver

# Enable if you want a 'robot' to test realtime code without having
# to get on your trainer and ride
option (GC_WANT_ROBOT "Enable if you want 'robot' to test realtime code" OFF)
if (GC_WANT_ROBOT)
  add_definitions( -DGC_WANT_ROBOT )
endif (GC_WANT_ROBOT)

#if you have a version of mingw that properly provides
#the Dwmapi.h header then uncomment this line
#DEFINES += GC_HAVE_DWM

# USING THE DROPBOX API
# register your app at https://www.dropbox.com/developers/apps and
# make sure the redirect_uri for the app includes  the url: 
# https://goldencheetah.github.io/blank.html and full permissions 
# are granted. Then set the client # and secret in the two defines
# below replacing the xxxxxxxxxxxxxx with the actual values.
#DEFINES += GC_DROPBOX_CLIENT_ID=\\\"xxxxxxxxxxxxxxx\\\"
#DEFINES += GC_DROPBOX_CLIENT_SECRET=\\\"xxxxxxxxxxxxxxx\\\"

# if you have your own MAPQUEST KEY
#DEFINES += GC_MAPQUESTAPI_KEY=\\\"xxxxxxxxxxxxxxxxxxxxxx\\\"

# USING THE WITHINGS API (http://oauth.withings.com/api)
#DEFINES += GC_WITHINGS_CONSUMER_KEY=\\\"xxxxxxxxxxxxxxx\\\"
#DEFINES += GC_WITHINGS_CONSUMER_SECRET=\\\"xxxxxxxxxxxxxxx\\\"

# What video playback do you want?
#DEFINES += GC_VIDEO_NONE             # dont add any video playback support
add_definitions( -DGC_VIDEO_NONE )
#DEFINES += GC_VIDEO_QUICKTIME        # mac only and the default
#DEFINES += GC_VIDEO_QT5              # use QT5 qvideowidget if QT > 5.2.1
#DEFINES += GC_VIDEO_VLC              # use VideoLan library needs VLC_INSTALL defined above
#DEFINES += GC_VIDEO_AV               # use AV Foundation on Mac now QTKit is deprecated

# Using the GoldenCheetah/CloudDB feature (with a private CloudDB instance)
# requires that you have a running instance of CloudDB on Google App Engine
# (for details on CloudDB please check the documentation here: https://github.com/GoldenCheetah/CloudDB
#DEFINES +=GC_CLOUD_DB_BASIC_AUTH=
#DEFINES +=GC_CLOUD_DB_APP_NAME=
#CloudDB = active

###======================================================
### QT MODULES [we officially support QT4.8.6+ or QT5.8+]
###======================================================

# Prefer Qt 5
option(USE_QT5 "Use Qt5 instead of Qt4." ON)

if (USE_QT5)
  find_package (Qt5Widgets REQUIRED)
  find_package (Qt5Core REQUIRED)
  find_package (Qt5Concurrent REQUIRED)
  #find_package (Qt5SerialPort REQUIRED)
  find_package(Qt5Core COMPONENTS Qt5SerialPort REQUIRED)
  find_package (Qt5MultimediaWidgets REQUIRED)
  #find_package (Qt5PrintSupport REQUIRED)
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTOUIC ON)
  message (STATUS "Qt version: ${Qt5Widgets_VERSION}")
  add_definitions( -DUSE_QT5 ) 
else (USE_QT5)
  find_package (Qt4 REQUIRED)
endif (USE_QT5)

###=======================================================================
### Directory Structure - Split into subdirs to be more manageable
###=======================================================================

set (GC_INCLUDE_DIRS "src/ANT")
set (GC_INCLUDE_DIRS  ${GC_INCLUDE_DIRS} "src/Train")
set (GC_INCLUDE_DIRS  ${GC_INCLUDE_DIRS} "src/FileIO")
set (GC_INCLUDE_DIRS  ${GC_INCLUDE_DIRS} "src/Cloud")
set (GC_INCLUDE_DIRS  ${GC_INCLUDE_DIRS} "src/Charts")
set (GC_INCLUDE_DIRS  ${GC_INCLUDE_DIRS} "src/Metrics")  
set (GC_INCLUDE_DIRS  ${GC_INCLUDE_DIRS} "src/Gui")
set (GC_INCLUDE_DIRS  ${GC_INCLUDE_DIRS} "src/Core")
set (GC_INCLUDE_DIRS  ${GC_INCLUDE_DIRS} "src/Planing")

###=======================================================================
### DISTRIBUTED SOURCE [Snaffled in sources to avoid further dependencies]
###=======================================================================

set (GC_INCLUDE_DIRS  ${GC_INCLUDE_DIRS} "qwt/src")
set (GC_INCLUDE_DIRS  ${GC_INCLUDE_DIRS} "qxt/src")
set (GC_INCLUDE_DIRS  ${GC_INCLUDE_DIRS} "qtsolutions/json")
set (GC_INCLUDE_DIRS  ${GC_INCLUDE_DIRS} "qtsolutions/qwtcurve")

#
# Qwt
#

# GC has its own Qwt
#find_package (QWT REQUIRED)

# We could 1) write a CMakeFile.txt for building Qwt or 2) just add the sources to GC
#
# 1)
#add_subdirectory("qwt/src")
#_
# 2) Add Qwt sources
file (GLOB_RECURSE QWT_HEADER_FILES RELATIVE ${CMAKE_SOURCE_DIR} qwt/src/*.h)
file (GLOB_RECURSE QWT_SOURCE_FILES RELATIVE ${CMAKE_SOURCE_DIR} qwt/src/*.cpp)

if (WIN32) 
  # QWT is configured to build 2 libs (release/debug) on win32 (see qwtbuild.pri)
  #CONFIG(release, debug|release){
  #LIBS += -L$${PWD}/../qwt/lib -lqwt
  #}
  #CONFIG(debug, debug|release) {
  #LIBS += -L$${PWD}/../qwt/lib -lqwtd
  #}
  
else (WIN32)
  # QWT is configured to build 1 lib for all other OS (see qwtbuild.pri)
 # LIBS += -L$${PWD}/../qwt/lib -lqwt
endif (WIN32)

#
# Qxt
#

file (GLOB_RECURSE QXT_HEADER_FILES RELATIVE ${CMAKE_SOURCE_DIR} qxt/src/*.h)
file (GLOB_RECURSE QXT_SOURCE_FILES RELATIVE ${CMAKE_SOURCE_DIR} qxt/src/*.cpp)

#find_package (ZLIB)

# Qt 5
if (USE_QT5)
  #qt5_wrap_ui (GC_FORMS_HEADER_FILES ${GC_FORMS})
  #qt5_wrap_cpp (GC_HEADER_FILES_MOC ${GC_HEADER_FILES})
  set (GC_FORMS_HEADER_FILES ${GC_FORMS}) # We use AUTOMUIC ON
  set (GC_HEADER_FILES_MOC ${GC_HEADER_FILES}) # We use AUTOMOC ON
  set (QWT_HEADER_FILES_MOC ${QWT_HEADER_FILES}) # We use AUTOMOC ON
  set (QXT_HEADER_FILES_MOC ${QXT_HEADER_FILES}) # We use AUTOMOC ON
else (USE_QT5) # Qt 4
  #qt4_wrap_ui(GC_FORMS_HEADER_FILES ${GC_FORMS})
  qt4_wrap_cpp (GC_HEADER_FILES_MOC ${GC_HEADER_FILES})
  qt4_wrap_cpp (QWT_HEADER_FILES_MOC ${QWT_HEADER_FILES})
  qt4_wrap_cpp (QXT_HEADER_FILES_MOC ${QXT_HEADER_FILES})
endif (USE_QT5)

include_directories (
  
  if (USE_QT5)
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5PrintSupport_INCLUDE_DIRS}
  endif (USE_QT5)

  ${GC_INCLUDE_DIRS}
  ${QWT_INCLUDE_DIR}
  ${QXT_INCLUDE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR} # May be needed to ui_*.h files (see https://anteru.net/2009/09/07/582/).
  )

set (GC_HEADER_FILES
  src/Gui/QTFullScreen.h
  src/Train/VideoWindow.h
  qtsolutions/segmentcontrol/qtsegmentcontrol.h
  )

set (GC_SOURCE_FILES
  src/Gui/QTFullScreen.cpp
  src/Train/VideoWindow.cpp
  qtsolutions/segmentcontrol/qtsegmentcontrol.cpp
  )

if (USE_QT5)
  set (GC_QT_LIBS "Qt5::Widgets")
  set (GC_QT_LIBS ${GC_QT_LIBS} "Qt5::Concurrent")
  #set (GC_QT_LIBS ${GC_QT_LIBS} "Qt5::SerialPort")
  set (GC_QT_LIBS ${GC_QT_LIBS} "Qt5::Multimedia")
  set (GC_QT_LIBS ${GC_QT_LIBS} "Qt5::MultimediaWidgets")
  #set (GC_QT_LIBS ${GC_QT_LIBS} "Qt5::PrintSupport")
else (USE_QT5)
  set (GC_QT_LIBS "${QT_LIBRARIES}")
endif (USE_QT5)

add_executable(GoldenCheetah
  ${GC_SOURCE_FILES} 
  ${GC_HEADER_FILES_MOC}
  ${QWT_SOURCE_FILES_MOC}
  ${QXT_SOURCE_FILES_MOC}
  )

# Deps.
target_link_libraries (GoldenCheetah
  ${GC_QT_LIBS}
  #${QWT_LIBRARIES}
  )

#qt5_use_modules(GoldenCheetah Core SerialPort)

# Install of the app.
install (TARGETS GoldenCheetah
  RUNTIME DESTINATION bin
  )


