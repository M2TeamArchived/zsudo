# ZSUDO cmake

cmake_minimum_required(VERSION 3.12)

if(NOT DEFINED ZSUDO_VERSION_MAJOR)
  set(ZSUDO_VERSION_MAJOR 1)
endif()
if(NOT DEFINED ZSUDO_VERSION_MINOR)
  set(ZSUDO_VERSION_MINOR 0)
endif()
if(NOT DEFINED ZSUDO_VERSION_PATCH)
  set(ZSUDO_VERSION_PATCH 0)
endif()
if(NOT DEFINED ZSUDO_VERSION_SUFFIX)
  set(ZSUDO_VERSION_SUFFIX git)
endif()

if (NOT PACKAGE_VERSION)
  set(PACKAGE_VERSION
    "${ZSUDO_VERSION_MAJOR}.${ZSUDO_VERSION_MINOR}.${ZSUDO_VERSION_PATCH}${ZSUDO_VERSION_SUFFIX}")
endif()

if ((CMAKE_GENERATOR MATCHES "Visual Studio") AND (CMAKE_GENERATOR_TOOLSET STREQUAL ""))
    message(WARNING "Visual Studio generators use the x86 host compiler by "
                  "default, even for 64-bit targets. This can result in linker "
                  "instability and out of memory errors. To use the 64-bit "
                  "host compiler, pass -Thost=x64 on the CMake command line.")
endif()

if( CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR AND NOT MSVC_IDE )
    message(FATAL_ERROR "In-source builds are not allowed."
                   "Please create a directory and run cmake from there, passing the path"
                   "to this source directory as the last argument."
                   "This process created the file `CMakeCache.txt' and the directory `CMakeFiles'."
                   "Please delete them.")
endif()


project(ZSUDO
  VERSION ${ZSUDO_VERSION_MAJOR}.${ZSUDO_VERSION_MINOR}.${ZSUDO_VERSION_PATCH}
  LANGUAGES C CXX)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to Debug")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (default Debug)" FORCE)
endif()

#
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
# Your should add git under your path,
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)

# Generate version code
configure_file(
  ${CMAKE_SOURCE_DIR}/include/zsudoversion.h.cmake
  ${CMAKE_BINARY_DIR}/include/zsudoversion.h
)

# LTO support
include(CheckIPOSupported)
check_ipo_supported(RESULT lto_supported OUTPUT error)
if(lto_supported)
  message(STATUS "IPO/LTO enabled")
else()
  message(STATUS "IPO/LTO not supported: <${error}>")
endif()

# Force use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Force use unicode
add_definitions(
  -D_UNICODE=1
  -DUNICODE=1
)

include_directories(
  ./include
  ${CMAKE_BINARY_DIR}/include
)
