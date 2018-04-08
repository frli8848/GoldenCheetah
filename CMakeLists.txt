project (GoldenCheetah)

# See http://doc.qt.io/qt-5/cmake-manual.html
cmake_minimum_required(VERSION 3.1)

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

# Prefer Qt 5
option(USE_QT5 "Use Qt5 instead of Qt4." ON)

if (USE_QT5)
  find_package (Qt5Widgets REQUIRED)
  find_package (Qt5Core REQUIRED)
  find_package (Qt5MultimediaWidgets REQUIRED)
  find_package (Qt5PrintSupport REQUIRED)
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

set (QC_INCLUDE_DIRS "src/ANT")
set (QC_INCLUDE_DIRS  ${QC_INCLUDE_DIRS} "src/Train")
set (QC_INCLUDE_DIRS  ${QC_INCLUDE_DIRS} "src/FileIO")
set (QC_INCLUDE_DIRS  ${QC_INCLUDE_DIRS} "src/Cloud")
set (QC_INCLUDE_DIRS  ${QC_INCLUDE_DIRS} "src/Charts")
set (QC_INCLUDE_DIRS  ${QC_INCLUDE_DIRS} "src/Metrics")  
set (QC_INCLUDE_DIRS  ${QC_INCLUDE_DIRS} "src/Gui")
set (QC_INCLUDE_DIRS  ${QC_INCLUDE_DIRS} "src/Core")
set (QC_INCLUDE_DIRS  ${QC_INCLUDE_DIRS} "src/Planing")

###=======================================================================
### DISTRIBUTED SOURCE [Snaffled in sources to avoid further dependencies]
###=======================================================================

set (QC_INCLUDE_DIRS  ${QC_INCLUDE_DIRS} "qwt/src")
set (QC_INCLUDE_DIRS  ${QC_INCLUDE_DIRS} "qxt/src")
set (QC_INCLUDE_DIRS  ${QC_INCLUDE_DIRS} "qtsolutions/json")
set (QC_INCLUDE_DIRS  ${QC_INCLUDE_DIRS} "qtsolutions/qwtcurve")

# GC has its own Qwt
#find_package (QWT REQUIRED)

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

#find_package (ZLIB)

include_directories (
  
  if (USE_QT5)
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5PrintSupport_INCLUDE_DIRS}
  endif (USE_QT5)

  ${QC_INCLUDE_DIRS}
  ${QWT_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/include
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
  set (GC_QT_LIBS ${GCR_QT_LIBS} "Qt5::Concurrent")
  set (GC_QT_LIBS ${GCR_QT_LIBS} "Qt5::Serialport")
  set (GC_QT_LIBS ${GCR_QT_LIBS} "Qt5::Multimedia")
  set (GC_QT_LIBS ${GCR_QT_LIBS} "Qt5::MultimediaWidgets")
    #set (GC_QT_LIBS ${GCR_QT_LIBS} "Qt5::PrintSupport")
else (USE_QT5)
  set (GC_QT_LIBS "${QT_LIBRARIES}")
endif (USE_QT5)

add_executable(GoldenCheetah
  ${GC_SOURCE_FILES} 
  ${GC_HEADER_FILES_MOC}
  )

# Deps.
target_link_libraries (GoldenCheetah
  ${GC_QT_LIBS}
  ${QWT_LIBRARIES}
  )

# Install of the app.
install (TARGETS GoldenCheetah
  RUNTIME DESTINATION bin
  )


