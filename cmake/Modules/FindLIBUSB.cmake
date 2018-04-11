
# Copyright (c) 2018 Fredik Lingvall (fredrik.lingvall@protonmail.com)
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2 of the License, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc., 51
# Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

# LIBUSB_INCLUDE_DIR = libusb.h
# LIBUSB_LIBRARIES = libusb.so
# LIBUSB_FOUND = true if LIBUSB is found

if (WIN32)
  set(CMAKE_PREFIX_PATH "C:/LIBUSB")
endif(WIN32)

find_path (LIBUSB_INCLUDE_DIR libusb.h NAMES libusb-1.0/libusb.h)
if (NOT LIBUSB_INCLUDE_DIR)
  message (STATUS "Could not find libusb.h")
endif (NOT LIBUSB_INCLUDE_DIR)

find_library (LIBUSB_LIBRARIES NAMES libusb usb PATH_SUFFIXES lib)
if (NOT LIBUSB_LIBRARIES)
  message (STATUS "Could not find LIBUSB library")
endif (NOT LIBUSB_LIBRARIES)

if (LIBUSB_INCLUDE_DIR AND LIBUSB_LIBRARIES)
  set (LIBUSB_FOUND TRUE)
endif (LIBUSB_INCLUDE_DIR AND LIBUSB_LIBRARIES)

if (LIBUSB_FOUND)

  if (NOT LIBUSB_FIND_QUIETLY)
    message (STATUS "Found libusb.h: ${LIBUSB_INCLUDE_DIR}")
  endif (NOT LIBUSB_FIND_QUIETLY)

  if (NOT LIBUSB_FIND_QUIETLY)
    message (STATUS "Found LIBUSB: ${LIBUSB_LIBRARIES}")
  endif (NOT LIBUSB_FIND_QUIETLY)

else (LIBUSB_FOUND)
  if (LIBUSB_FIND_REQUIRED)
    message (FATAL_ERROR "Could not find LIBUSB")
  endif (LIBUSB_FIND_REQUIRED)
endif (LIBUSB_FOUND)

mark_as_advanced (LIBUSB_INCLUDE_DIR LIBUSB_LIBRARIES LIBUSB_FOUND)
