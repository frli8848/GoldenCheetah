project (libkml)

cmake_minimum_required(VERSION 3.4)

# Download (git version), configure, build, and install liblibkml.
#
# NB. one have to type passsword (sudo) to install it in /usr/local

include(ExternalProject)

set (LIBKML_SRC_DIR libkml-src)

ExternalProject_Add(libkml-git
  GIT_REPOSITORY https://github.com/google/libkml.git
  # Latest release tag is from 2/19/10 4:52 PM (!?) 
  #GIT_TAG release-1.2
  SOURCE_DIR ${LIBKML_SRC_DIR}
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND ./configure
  BUILD_COMMAND $(MAKE)
  INSTALL_COMMAND sudo $(MAKE) install 
  )

ExternalProject_Add_Step(libkml-git gen-configure-script
  COMMAND cd ${LIBKML_SRC_DIR} && sh autogen.sh
  COMMENT "Generating configure script... "     # Text printed when step executes
  DEPENDEES download    # Steps on which this step depends
  DEPENDERS configure    # Steps that depend on this step
  #[DEPENDS files...]      # Files on which this step depends
  #[ALWAYS 1]              # No stamp file, step always runs
  #WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
  #[LOG 1]                 # Wrap step in script to log output
  )
