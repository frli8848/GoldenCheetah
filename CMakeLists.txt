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

option (USE_R "Enable if you want an R chart" OFF)

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

option (USE_PYTHON "Enable if you want Python charting / ML etc" OFF)

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
find_program (LRELEASE NAMES lrelease REQUIRED)
if (LRELEASE)
  message (STATUS "Using lrelease: ${LRELEASE}")
endif (LRELEASE)

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

option (USE_SRMIO "Enable if you want SRM download support" OFF)

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

option (USE_KQOAUTH "Enable if you want Twitter support" OFF)

# For TrainingPeaks.com upload/download you need to install the Qt Soap add-on
#     http://qt.nokia.com/products/appdev/add-on-products/catalog/4/Utilities/qtsoap
# If qtsoap.pri is install in /usr/local/qtsolutions/soap/ then set
# QTSOAP_INSTALL = /usr/local/qtsolutions/soap
# By default we use a copy of Qt Soap in the GIT repository.
# You *must* define QTSOAP_INSTALL to use a different version than this.
#QTSOAP_INSTALL = 

option (USE_QTSOAP "Enable if you want TrainingPeaks.com upload/download" OFF)

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

option (USE_KML "Enable if you want support for Google Earth .kml files" OFF)

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

option (USE_ICAL "Enable if you want support for downloading from iCal calendars" OFF)

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

option (USE_USBXPRESS "Enable if you want support for using USB1 sticks in Train View on Windows" OFF)

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

option (USE_LIBUSB "Enable if you want support for using USB2 sticks in Train View on Linux or Windows" OFF)

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

option (USE_VLC "Enable if you want video playback on training mode" OFF)

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

option (USE_SAMPLERATE "Enable if you want to resample with high fidelity" OFF)

# If your system has PKG_CONFIG, QT can use this to get dependent libraries.
# Add the names of libraries with PKG_CONFIG information.
# eg. PKGCONFIG = oauth libical
# Uncomment the following two lines to enable.
#CONFIG   += link_pkgconfig
#PKGCONFIG = 

# We use LMFit for model fitting Banister models
# download from http://apps.jcns.fz-juelich.de/src/lmfit/
#LMFIT_INSTALL = /usr/local

option (USE_LMFIT "Enable if you want support for LMFit (for model fitting Banister models)" OFF)

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

option (USE_HTPATH "Enable if you want R integration via webservices" OFF)

# Enable if you want a 'robot' to test realtime code without having
# to get on your trainer and ride

option (USE_ROBOT "Enable if you want 'robot' to test realtime code" OFF)

if (USE_ROBOT)
  add_definitions( -DGC_WANT_ROBOT )
endif (USE_ROBOT)

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
#DEFINES += GC_VIDEO_QUICKTIME        # mac only and the default
#DEFINES += GC_VIDEO_QT5              # use QT5 qvideowidget if QT > 5.2.1
#DEFINES += GC_VIDEO_VLC              # use VideoLan library needs VLC_INSTALL defined above
#DEFINES += GC_VIDEO_AV               # use AV Foundation on Mac now QTKit is deprecated

option (USE_VLC "Enable if you want support for video playback" OFF)

# Using the GoldenCheetah/CloudDB feature (with a private CloudDB instance)
# requires that you have a running instance of CloudDB on Google App Engine
# (for details on CloudDB please check the documentation here: https://github.com/GoldenCheetah/CloudDB
#DEFINES +=GC_CLOUD_DB_BASIC_AUTH=
#DEFINES +=GC_CLOUD_DB_APP_NAME=
#CloudDB = active

option (USE_CloudDB "Enable if you want support for the GoldenCheetah/CloudDB feature (with a private CloudDB instance)" OFF)

###======================================================
### QT MODULES [we officially support QT4.8.6+ or QT5.8+]
###======================================================

# Prefer Qt 5
option(USE_QT5 "Use Qt5 (instead of Qt4)." ON)

if (USE_QT5)
  find_package (Qt5Widgets 5.8 REQUIRED)
  find_package (Qt5Core REQUIRED)
  find_package (Qt5Xml REQUIRED)
  find_package (Qt5Sql REQUIRED)
  find_package (Qt5Network REQUIRED)
  find_package (Qt5Svg REQUIRED)
  find_package (Qt5Concurrent REQUIRED)
  #find_package (Qt5SerialPort REQUIRED)
  find_package(Qt5Core COMPONENTS Qt5SerialPort REQUIRED)
  find_package (Qt5MultimediaWidgets REQUIRED)
  #find_package (Qt5PrintSupport REQUIRED)

  ## Always add debug information for Windows, MSVC
  #win32-msvc* { CONFIG += force_debug_info }
  
  ## If building with QT5 there is experimental suport for building
  ## with WebEngine now that WebKit is deprecated in QT 5.6
  ## It brings in a LOT of dependencies !
  if (NOWEBKIT AND NOT ${Qt5Widgets_VERSION} LESS 5.6) # We require Qt >= 5.8 so we could skip the 2nd test here.
    #CONFIG += c++11
    find_package (Qt5WebEngine REQUIRED)
    find_package (Qt5WebEngineCore REQUIRED)
    find_package (Qt5WebEngineWidgets REQUIRED)
    find_package (Qt5WebChannel REQUIRED)
    find_package (Qt5Positioning REQUIRED)
  else (NOWEBKIT AND NOT ${Qt5Widgets_VERSION} LESS 5.6)
    # On 5.5 or earlier we can still use WebKit
    find_package (Qt5WebKitWidgets)
  endif (NOWEBKIT AND NOT ${Qt5Widgets_VERSION} LESS 5.6)
  
  if (APPLE)
    ## need mac extras and clang++ needs to know which stdlib to link with
    #QT += macextras webengine webenginecore webenginewidgets positioning
  else (APPLE)
    
  endif (APPLE)
  
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTOUIC ON)
  message (STATUS "Qt version: ${Qt5Widgets_VERSION}")

  #add_definitions( -DUSE_QT5 ) 

else (USE_QT5) # Qt 4
  find_package (Qt4 REQUIRED)
endif (USE_QT5)

###=======================================================================
### Directory Structure - Split into subdirs to be more manageable
###=======================================================================

set (GC_INCLUDE_DIRS
  src/ANT
  src/Train
  src/FileIO
  src/Cloud
  src/Charts
  src/Metric
  src/Gui
  src/Core
  src/Planing
  )

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
add_definitions( -DQXT_STATIC )

# Compress and math libs must be defined in gcconfig.pri
# if they're not part of the QT include
#INCLUDEPATH += $${LIBZ_INCLUDE}
#LIBS += $${LIBZ_LIBS}
#find_package (ZLIB)

###===============================
### PLATFORM SPECIFIC DEPENDENCIES
###===============================

# Microsoft Visual Studion toolchain dependencies
if (MSVC)
  # We need windows kit 8.2 or higher with MSVC, offer default location
  #isEmpty(WINKIT_INSTALL) WINKIT_INSTALL= "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64"
  #LIBS += -L$${WINKIT_INSTALL} -lGdi32 -lUser32
  
else (MSVC)
  # gnu toolchain wants math libs
  #LIBS += -lm
  
  if (UNIX AND NOT APPLE)
    # Linux gcc 5 grumbles about unused static globals and leads
    # to a gazillion warnings that are harmless so lets remove them
    #QMAKE_CXXFLAGS += -Wno-unused-variable
    
    # Linux Flex compiler grumbles about unsigned comparisons
    #QMAKE_CXXFLAGS += -Wno-sign-compare
  endif (UNIX AND NOT APPLE)
  
endif(MSVC)

# Windows icon and use QT zlib, not sure why different but keep for now
if (WIN32)
  #RC_FILE = Resources/win32/windowsico.rc
  #INCLUDEPATH += Resources/win32 $${QT_INSTALL_PREFIX}/src/3rdparty/zlib
  #LIBS += -lws2_32
else (WIN32)
  #RC_FILE = Resources/images/gc.icns
endif (WIN32)

if (APPLE)
  
  # We have our own plist
  set (QMAKE_INFO_PLIST ./Resources/mac/Info.plist.app)
  
  # on mac we use native buttons and video, but have native fullscreen support
  #LIBS  += -lobjc -framework IOKit -framework AppKit
  
  # On mac we use QTKit or AV Foundation
  if (GC_VIDEO_AV)
    
    # explicitly wants AV Foundation
    #LIBS += -framework AVFoundation
    #HEADERS +=  Gui/QtMacVideoWindow.h
    #OBJECTIVE_SOURCES += Gui/QtMacVideoWindow.mm
    
  else (GC_VIDEO_AV)
    
    if (GC_VIDEO_NONE)
      
      # We have a blank videowindow, it will do nothing
      #HEADERS += Train/VideoWindow.h
      #SOURCES += Train/VideoWindow.cpp
      
    else (GC_VIDEO_NONE)
      
      # Default is to use QuickTime for now
      #LIBS += -framework QTKit
      #HEADERS +=  Gui/QtMacVideoWindow.h
      #OBJECTIVE_SOURCES += Gui/QtMacVideoWindow.mm
      
    endif (GC_VIDEO_NONE)
    
  endif (GC_VIDEO_AV)
  
else (APPLE)
  
  # not on mac we need our own full screen support and segment control button
  #HEADERS += Gui/QTFullScreen.h
  #SOURCES += Gui/QTFullScreen.cpp
  
  #HEADERS += Train/VideoWindow.h
  #SOURCES += Train/VideoWindow.cpp

endif (APPLE)

###=================
### LANGUAGE SUPPORT
###=================

set (TRANSLATIONS
  Resources/translations/gc_fr.ts
  Resources/translations/gc_ja.ts
  Resources/translations/gc_it.ts
  Resources/translations/gc_pt-br.ts
  Resources/translations/gc_de.ts
  Resources/translations/gc_cs.ts
  Resources/translations/gc_es.ts
  Resources/translations/gc_pt.ts
  Resources/translations/gc_ru.ts
  Resources/translations/gc_zh-cn.ts
  Resources/translations/gc_zh-tw.ts
  Resources/translations/gc_nl.ts
  Resources/translations/gc_sv.ts
  )

# Need lrelease to generate qm files
if (NOT LRELEASE)
  
  if (WIN32)
    set (LRELEASE = ${QT_INSTALL_BINS}\\lrelease.exe)
  endif (WIN32)
  
  if (UNIX AND NOT APPLE)
    set (LRELEASE  ${QT_INSTALL_BINS}/lrelease-qt4)
  else (UNIX AND NOT APPLE)
    set (LRELEASE  ${QT_INSTALL_BINS}/lrelease)
  endif (UNIX AND NOT APPLE)
  
endif (NOT LRELEASE)

# How to run lrelease
if  (NOT TS_DIR)
  set (TS_DIR "${PWD}/Resources/translations")
  set (TSQM.name "lrelease ${QMAKE_FILE_IN}")
  set (TSQM.input ${TRANSLATIONS})
  set (TSQM.output ${TS_DIR}/${QMAKE_FILE_BASE}.qm)
  set (TSQM.commands  "${QMAKE_LRELEASE} ${QMAKE_FILE_IN} -qm ${TS_DIR}/${QMAKE_FILE_BASE}.qm")
  set (TSQM.CONFIG  no_link target_predeps)
  set (QMAKE_EXTRA_COMPILERS ${QMAKE_EXTRA_COMPILERS} TSQM)
endif  (NOT TS_DIR)

###==========
### RESOURCES
###==========

set (RESOURCES src/Resources/application.qrc src/Resources/RideWindow.qrc)

###############################################################################
#                                                                             #
#         ***  SECTION TWO - OPTIONAL LIBRARIES AND FEATURES  ***             #
#                                                                             #
#                                                                             #
###############################################################################

###========================================
### OPTIONAL => LMFIT Model fitting library
###========================================

if (NOT LMFIT_INSTALL)

  #find_package (LMFIT)
  
  # we will work out the rest if you tell us where it is installed
  #isEmpty(LMFIT_INCLUDE) { LMFIT_INCLUDE = $${LMFIT_INSTALL}/src }
  #isEmpty(LMFIT_LIBS)    { LMFIT_LIBS    = -L$${LMFIT_INSTALL}/lib -llmfit }
  
  #INCLUDEPATH += $${LMFIT_INCLUDE}
  #LIBS        += $${LMFIT_LIBS}
  #DEFINES     += GC_HAVE_LMFIT

endif (NOT LMFIT_INSTALL)

###=========================
### OPTIONAL => Embed Python
###=========================

if (USE_PYTHON)
  
  find_package (PythonLibs 3.6 REQUIRED)
  
  if (PYTHONLIBS_FOUND)
    
    message (STATUS "Python lib dir:${PYTHON_LIBRARIES}")
    message (STATUS "Python include dir: ${PYTHON_INCLUDE_DIRS}")
    message (STATUS "Python lib version: ${PYTHONLIBS_VERSION_STRING}")
        
    if (Qt5Widgets_VERSION GREATER_EQUAL 5.8)
      
      #if (QT_MAJOR_VERSION EQUAL 4)
      
      #if (QT_MINOR_VERSION GREATER 7) 
      
      # add Python subdirectory to include path
      #INCLUDEPATH += ./Python
      
      #DEFINES += SIP_STATIC_MODULE
      #!isEmpty(PYTHONINCLUDES) QMAKE_CXXFLAGS += $${PYTHONINCLUDES}
      #LIBS += $${PYTHONLIBS}
      
      ## Python integration
      #HEADERS += Python/PythonEmbed.h Charts/PythonChart.h Python/PythonSyntax.h
      #SOURCES += Python/PythonEmbed.cpp Charts/PythonChart.cpp Python/PythonSyntax.cpp
      
      ## Python SIP generated module
      #SOURCES += Python/SIP/sipgoldencheetahBindings.cpp Python/SIP/sipgoldencheetahcmodule.cpp
      #SOURCES += Python/SIP/Bindings.cpp
      
      ## SIP type conversion
      #SOURCES += Python/SIP/sipgoldencheetahQString.cpp
      #SOURCES += Python/SIP/sipgoldencheetahPythonDataSeries.cpp
      #DEFINES += GC_HAVE_PYTHON
	
      #else (QT_MINOR_VERSION GREATER 7) 
      # QT5 but not 5.5 or higher
      #message(STATUS "")
      #endif (QT_MINOR_VERSION GREATER 7) 
      
      #else (QT_MAJOR_VERSION EQUAL 4)
      
      # QT5 but not 5.5 or higher
      #message(STATUS "")
      #endif (QT_MAJOR_VERSION EQUAL 4)
      
      add_definitions( -DGC_WANT_PYTHON )
      
    else (Qt5Widgets_VERSION GREATER_EQUAL 5.8)
      
      message (STATUS "INFO: Embedded Python requires version QT >= 5.8, no support for ${Qt5Widgets_VERSION}")
      
    endif(Qt5Widgets_VERSION GREATER_EQUAL 5.8)
    
  endif (PYTHONLIBS_FOUND)
  
endif (USE_PYTHON)

###====================
### OPTIONAL => Embed R
###====================

if (USE_R)
  
  #find_package (R)
  
  # Only supports Linux and OSX until RInside and Rcpp support MSVC
  # This is not likely to be very soon, they are heavily dependant on GCC
  # see: http://dirk.eddelbuettel.com/blog/2011/03/25/#rinside_and_qt
  if (NOT R_HOME)
    execute_process(COMMAND R RHOME RESULT_VARIABLE R_HOME)
  endif (NOT R_HOME)
  
  if (R_HOME)
    
    add_definitions( -DGC_WANT_R )
    
    # add R subdirectory to include path
    #INCLUDEPATH += ./R
    set (GC_INCLUDE_DIRS "${GC_INCLUDE_DIRS}" "src/R")
    
    ## include headers and libraries for R
    if (WIN32)
      #QMAKE_CXXFLAGS += -I$$R_HOME/include
      #DEFINES += Win32
    else (WIN32)
      #QMAKE_CXXFLAGS += $$system($$R_HOME/bin/R CMD config --cppflags)
    endif (WIN32)
    
    ## R has lots of compatibility headers for S and legacy R code we don't want
    #DEFINES += STRICT_R_HEADERS
    add_definitions( -DSTRICT_R_HEADERS )
    
    ## R integration
    #HEADERS += R/REmbed.h R/RTool.h R/RGraphicsDevice.h R/RSyntax.h R/RLibrary.h
    #SOURCES += R/REmbed.cpp R/RTool.cpp R/RGraphicsDevice.cpp R/RSyntax.cpp R/RLibrary.cpp
    
    ## R based charts
    #HEADERS += Charts/RChart.h Charts/RCanvas.h
    #SOURCES += Charts/RChart.cpp Charts/RCanvas.cpp
    
    ## For hardware accelerated scene rendering
    #QT += opengl

  endif (R_HOME)
  
endif (USE_R)

###====================
### OPTIONAL => KQOAUTH
###====================

if (USE_KQOAUTH)
  
  if (UNIX AND NOT APPLE)
    
    # build from version in repo for Linux builds since
    # kqoauth is not packaged for the Debian and this makes
    # life much easier for the package maintainer
    #INCLUDEPATH += $${PWD}/../kqoauth
    #LIBS        += $${PWD}/../kqoauth/libkqoauth.a
    #DEFINES     += GC_HAVE_KQOAUTH
    
  else (UNIX AND NOT APPLE)
    
    if (KQOAUTH_INSTALL)
      
      # we will work out the rest if you tell us where it is installed
      if (NOT KQOAUTH_INCLUDE)
	set (KQOAUTH_INCLUDE "${KQOAUTH_INSTALL}/src")
      endif (NOT KQOAUTH_INCLUDE)
      
      if (NOT KQOAUTH_LIBS)
	set (KQOAUTH_LIBS "-L$${KQOAUTH_INSTALL}/lib -lkqoauth")
      endif (NOT KQOAUTH_LIBS)
      
      #INCLUDEPATH += $${KQOAUTH_INCLUDE}
      #LIBS        += $${KQOAUTH_LIBS}
      #DEFINES     += GC_HAVE_KQOAUTH
      
    endif (KQOAUTH_INSTALL)
  endif (UNIX AND NOT APPLE)

endif (USE_KQOAUTH)

###=======================================================
### OPTIONAL => D2XX FOR FTDI DRIVERS ON WINDOWS PLATFORMS
###=======================================================

if (USE_D2XX)

  #find_package (D2XX)
  
  #DEFINES     += GC_HAVE_D2XX
  #INCLUDEPATH += $${D2XX_INCLUDE}

  #!isEmpty(D2XX_LIBS) { LIBS += $${D2XX_LIBS} }
  #unix                { LIBS += -ldl }
  
  #HEADERS     += FileIO/D2XX.h
  #SOURCES     += FileIO/D2XX.cpp

endif (USE_D2XX)


###==================
### OPTIONAL => SRMIO
###==================

if (USE_SRMIO)
  
  #find_package (SRMIO)

  # we will work out the rest if you tell use where it is installed
  #isEmpty(SRMIO_INCLUDE) { SRMIO_INCLUDE = $${SRMIO_INSTALL}/include }
  #isEmpty(SRMIO_LIBS)    { SRMIO_LIBS    = -L$${SRMIO_INSTALL}/lib -lsrmio }
  
  #DEFINES     += GC_HAVE_SRMIO
  #INCLUDEPATH += $${SRMIO_INCLUDE}
  #LIBS        += $${SRMIO_LIBS}
  
  # add support for srm downloads
  #HEADERS     += FileIO/SrmDevice.h
  #SOURCES     += FileIO/SrmDevice.cpp
  
endif (USE_SRMIO)


###=====================================
### OPTIONAL => GOOGLE KML IMPORT EXPORT
###=====================================

if (USE_KML)
  
  # we will work out the rest if you tell use where it is installed
  #isEmpty(KML_INCLUDE) { KML_INCLUDE = $${KML_INSTALL}/include }
  #isEmpty(KML_LIBS)    { KML_LIBS    = -L$${KML_INSTALL}/lib/ \
  #                                     -lkmldom -lkmlconvenience -lkmlengine -lkmlbase
  #}
  
  # on MS VS the linker wants /LTCG for libkmldom due to
  # "MSIL .netmodule or module compiled with /GL found"
  #win32-msvc* { QMAKE_LFLAGS +=  /LTCG }
  
  #DEFINES     += GC_HAVE_KML
  #INCLUDEPATH += $${KML_INCLUDE}  $${BOOST_INCLUDE}
  #LIBS        += $${KML_LIBS}
  
  # add kml file i/o
  #SOURCES     += FileIO/KmlRideFile.cpp
  #HEADERS     += FileIO/KmlRideFile.h
  
endif (USE_KML)

###=================
### OPTIONAL => ICAL
###=================

if (USE_ICAL)

  #find_package (ICAL)
  #find_package (LIBICAL)
  
  # we will work out the rest if you tell use where it is installed
  #isEmpty(ICAL_INCLUDE) { ICAL_INCLUDE = $${ICAL_INSTALL}/include }
  #isEmpty(ICAL_LIBS)    { ICAL_LIBS    = -L$${ICAL_INSTALL}/lib -lical }
  
  #DEFINES     += GC_HAVE_ICAL
  #INCLUDEPATH += $${ICAL_INCLUDE}
  #LIBS        += $${ICAL_LIBS}
  
  # add caldav and diary functions
  #HEADERS     += Core/ICalendar.h Charts/DiaryWindow.h Cloud/CalDAV.h
  #SOURCES     += Core/ICalendar.cpp Charts/DiaryWindow.cpp Cloud/CalDAV.cpp
  
endif (USE_ICAL)

###===================
### OPTIONAL => LIBUSB
###===================

if (USE_LIBUSB)

  #find_package (LIBUSB)

  # we will work out the rest if you tell use where it is installed
  #isEmpty(LIBUSB_INCLUDE) { LIBUSB_INCLUDE = $${LIBUSB_INSTALL}/include }
  #isEmpty(LIBUSB_LIBS)    {
  # needs fixing for msvc toolchain
  #unix  { LIBUSB_LIBS = -L$${LIBUSB_INSTALL}/lib -lusb }
  #      win32 { LIBUSB_LIBS = -L$${LIBUSB_INSTALL}/lib/gcc -lusb }
  #  }

  #DEFINES     += GC_HAVE_LIBUSB
  #INCLUDEPATH += $${LIBUSB_INCLUDE}
  #LIBS        += $${LIBUSB_LIBS}

  # lots of dependents
  # SOURCES     += Train/LibUsb.cpp Train/EzUsb.c Train/Fortius.cpp Train/FortiusController.cpp \
  #                 Train/Imagic.cpp Train/ImagicController.cpp
  #  HEADERS     += Train/LibUsb.h Train/EzUsb.h Train/Fortius.cpp Train/FortiusController.h \
  #                 Train/Imagic.h Train/ImagicController.h

endif (USE_LIBUSB)


###===================================================
### OPTIONAL => USBXPRESS [Windows only for ANT+ USB1]
###===================================================

if (WIN32) 
  
  # are we supporting USB1 devices on Windows?
  if (USE_USBXPRESS)
    
    # we will work out the rest if you tell use where it is installed
    #isEmpty(USBXPRESS_INCLUDE) { USBXPRESS_INCLUDE = $${USBXPRESS_INSTALL} }

    # this is windows only !
    #isEmpty(USBXPRESS_LIBS)    { USBXPRESS_LIBS    = $${USBXPRESS_INSTALL}/x86/SiUSBXp.lib }

    #DEFINES     += GC_HAVE_USBXPRESS
    #INCLUDEPATH += $${USBXPRESS_INCLUDE}
    #LIBS        += $${USBXPRESS_LIBS}

    #SOURCES += Train/USBXpress.cpp
    #HEADERS += Train/USBXpress.h

  endif (USE_USBXPRESS)

endif (WIN32)


###=============================================================
### OPTIONAL => VLC [Windows and Unix. OSX uses QuickTime Video]
###=============================================================


if (USE_VLC)

  # not on a mac as they use quicktime video
  if (NOT APPLE)

    # we will work out the rest if you tell use where it is installed
    #isEmpty(VLC_INCLUDE) { VLC_INCLUDE = $${VLC_INSTALL}/include }
    #isEmpty(VLC_LIBS)    { VLC_LIBS    = -L$${VLC_INSTALL}/lib -lvlc }
    
    #DEFINES     += GC_HAVE_VLC
    #INCLUDEPATH += $${VLC_INCLUDE}
    #LIBS        += $${VLC_LIBS}
    
  endif (NOT APPLE)

endif (USE_VLC)


###=======================
### OPTIONAL => SAMPLERATE
###=======================

if (USE_SAMPLERATE)

  # we will work out the rest if you tell use where it is installed
  #isEmpty(SAMPLERATE_INCLUDE) { SAMPLERATE_INCLUDE = $${SAMPLERATE_INSTALL}/include }
  #isEmpty(SAMPLERATE_LIBS)    { SAMPLERATE_LIBS    = -L$${SAMPLERATE_INSTALL}/lib -lsamplerate }
  
  #DEFINES     += GC_HAVE_SAMPLERATE
  #INCLUDEPATH += $${SAMPLERATE_INCLUDE}
  #LIBS        += $${SAMPLERATE_LIBS}
  
endif (USE_SAMPLERATE)

###==================================
### OPTIONAL => HTTP API WEB SERVICES
###==================================

if (USE_HTPATH)

  #INCLUDEPATH += $$HTPATH
  #DEPENDPATH += $$HTPATH
  
  #DEFINES += GC_WANT_HTTP
  
  #HEADERS +=  Core/APIWebService.h
  #SOURCES +=  Core/APIWebService.cpp
  
  #HEADERS +=  $$HTPATH/httpglobal.h \
  #            $$HTPATH/httplistener.h \
  #            $$HTPATH/httpconnectionhandler.h \
  #            $$HTPATH/httpconnectionhandlerpool.h \
  #            $$HTPATH/httprequest.h \
  #            $$HTPATH/httpresponse.h \
  #            $$HTPATH/httpcookie.h \
  #            $$HTPATH/httprequesthandler.h \
  #            $$HTPATH/httpsession.h \
  #            $$HTPATH/httpsessionstore.h \
  #            $$HTPATH/staticfilecontroller.h
  #SOURCES +=  $$HTPATH/httpglobal.cpp \
  #            $$HTPATH/httplistener.cpp \
  #            $$HTPATH/httpconnectionhandler.cpp \
  #            $$HTPATH/httpconnectionhandlerpool.cpp \
  #            $$HTPATH/httprequest.cpp \
  #            $$HTPATH/httpresponse.cpp \
  #            $$HTPATH/httpcookie.cpp \
  #            $$HTPATH/httprequesthandler.cpp \
  #            $$HTPATH/httpsession.cpp \
  #            $$HTPATH/httpsessionstore.cpp \
  #            $$HTPATH/staticfilecontroller.cpp
  
endif (USE_HTPATH)

###=====================================================
### OPTIONAL => CLOUD DB [Google App Engine Integration]
###=====================================================

##----------------------------------------------##
## CloudDB is only supported on QT5.5 or higher ##
##----------------------------------------------##

if (USE_CloudDB)
  
  if (Qt5Widgets_VERSION GREATER_EQUAL 5.5)
    
    #HEADERS += Cloud/CloudDBChart.h Cloud/CloudDBCommon.h \
    #           Cloud/CloudDBCurator.h Cloud/CloudDBStatus.h \
    #           Cloud/CloudDBVersion.h Cloud/CloudDBTelemetry.h
    #SOURCES += Cloud/CloudDBChart.cpp Cloud/CloudDBCommon.cpp \
    #           Cloud/CloudDBCurator.cpp Cloud/CloudDBStatus.cpp \
    #           Cloud/CloudDBVersion.cpp Cloud/CloudDBTelemetry.cpp
    
    #DEFINES += GC_HAS_CLOUD_DB
    
  else (Qt5Widgets_VERSION GREATER_EQUAL 5.5)
    
    # QT5 but not 5.5 or higher
    message(STATUS "INFO: CloudDB requires version QT >= 5.5, no support for ${QT_VERSION}")

  endif (Qt5Widgets_VERSION GREATER_EQUAL 5.5)
  
endif (USE_CloudDB)

###############################################################################
#                                                                             #
#         ***  SECTION THREE - GOLDENCHEETAH SOURCE FILES  ***                #
#                                                                             #
#                                                                             #
###############################################################################


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


