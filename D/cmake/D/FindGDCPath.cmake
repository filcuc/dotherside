#
# CMakeD - CMake module for D Language
#
# Copyright (c) 2013, Selman Ulug <selman.ulug@gmail.com>
#                     Tim Burrell <tim.burrell@gmail.com>
#                     Dragos Carp <dragos.carp@gmail.com>
#
# All rights reserved.
#
# See LICENSE for details.
#
# - Find GDC Include Path
#
#  GDC_INCLUDE_PATH = path to where object.d is found
#

set(GDC_POSSIBLE_INCLUDE_PATHS
  /usr/include/d/4.8.2
  /usr/include/d/4.8.1
  /usr/include/d/4.8.0
  /usr/include/d/4.7.3
  /usr/include/d/4.7.2
  /usr/include/d/4.7.1
  /usr/include/d/4.7.0
  /usr/include/d/4.2.1
  /usr/include/d/4.2.0
  /usr/include/d/4.1.2
  /usr/include/d/4.1.1
  /usr/include/d/4.1.0
  /usr/include/d/4.0.4
  /usr/include/d/4.0.3
  /usr/include/d/4.0.2
  /usr/include/d/4.0.1
  /usr/include/d/4.0.0
  /usr/include/d/4.0.6
  /usr/include/d/4.0.5
  /usr/include/d/3.4.4
  /usr/include/d/3.4.3
  /usr/include/d/3.4.2
  /usr/include/d/3.4.1
  /usr/include/d/3.4.0
  )

find_path(GDC_INCLUDE_PATH object.d
  ${GDC_POSSIBLE_INCLUDE_PATHS})

mark_as_advanced(
  GDC_INCLUDE_PATH
  )
