# Locate the Google C++ Testing Framework.
#
# Defines the following variables:
#
#   GMOCK_FOUND - Found the Google Testing framework
#   GMOCK_INCLUDE_DIRS - Include directories
#
# Also defines the library variables below as normal
# variables.  These contain debug/optimized keywords when
# a debugging library is found.
#
#   GMOCK_BOTH_LIBRARIES - Both libgmock & libgmock-main
#   GMOCK_LIBRARIES - libgmock
#   GMOCK_MAIN_LIBRARIES - libgmock-main
#
# Accepts the following variables as input:
#
#   GMOCK_ROOT - (as a CMake or environment variable)
#                The root directory of the gmock install prefix
#
#   GMOCK_MSVC_SEARCH - If compiling with MSVC, this variable can be set to
#                       "MD" or "MT" to enable searching a GMock build tree
#                       (defaults: "MD")
#
#-----------------------
# Example Usage:
#
#    enable_testing()
#    find_package(GMock REQUIRED)
#    include_directories(${GMOCK_INCLUDE_DIRS})
#
#    add_executable(foo foo.cc)
#    target_link_libraries(foo ${GMOCK_BOTH_LIBRARIES})
#
#    add_test(AllTestsInFoo foo)
#
#-----------------------
#
# If you would like each Google test to show up in CTest as
# a test you may use the following macro.
# NOTE: It will slow down your tests by running an executable
# for each test and test fixture.  You will also have to rerun
# CMake after adding or removing tests or test fixtures.
#
# GMOCK_ADD_TESTS(executable extra_args ARGN)
#    executable = The path to the test executable
#    extra_args = Pass a list of extra arguments to be passed to
#                 executable enclosed in quotes (or "" for none)
#    ARGN =       A list of source files to search for tests & test
#                 fixtures.
#
#  Example:
#     set(FooTestArgs --foo 1 --bar 2)
#     add_executable(FooTest FooUnitTest.cc)
#     GMOCK_ADD_TESTS(FooTest "${FooTestArgs}" FooUnitTest.cc)

#=============================================================================
# Copyright 2009 Kitware, Inc.
# Copyright 2009 Philip Lowman <philip@yhbt.com>
# Copyright 2009 Daniel Blezek <blezek@gmail.com>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)
#
# Thanks to Daniel Blezek <blezek@gmail.com> for the GMOCK_ADD_TESTS code

function(GMOCK_ADD_TESTS executable extra_args)
    if(NOT ARGN)
        message(FATAL_ERROR "Missing ARGN: Read the documentation for GMOCK_ADD_TESTS")
    endif()
    foreach(source ${ARGN})
        file(READ "${source}" contents)
        string(REGEX MATCHALL "TEST_?F?\\(([A-Za-z_0-9 ,]+)\\)" found_tests ${contents})
        foreach(hit ${found_tests})
            string(REGEX REPLACE ".*\\( *([A-Za-z_0-9]+), *([A-Za-z_0-9]+) *\\).*" "\\1.\\2" test_name ${hit})
            add_test(${test_name} ${executable} --gtest_filter=${test_name} ${extra_args})
        endforeach()
    endforeach()
endfunction()

function(_gmock_append_debugs _endvar _library)
    if(${_library} AND ${_library}_DEBUG)
        set(_output optimized ${${_library}} debug ${${_library}_DEBUG})
    else()
        set(_output ${${_library}})
    endif()
    set(${_endvar} ${_output} PARENT_SCOPE)
endfunction()

function(_gmock_find_library _name)
    find_library(${_name}
        NAMES ${ARGN}
        HINTS
            ENV GMOCK_ROOT
            ${GMOCK_ROOT}
        PATH_SUFFIXES ${_gmock_libpath_suffixes}
    )
    mark_as_advanced(${_name})
endfunction()

#

if(NOT DEFINED GMOCK_MSVC_SEARCH)
    set(GMOCK_MSVC_SEARCH MD)
endif()

set(_gmock_libpath_suffixes lib)
if(MSVC)
    list(APPEND _gmock_libpath_suffixes
        msvc/2010/Debug
        msvc/2010/Release)
elseif(ANDROID)
    list(APPEND _gmock_libpath_suffixes
        libs/${ANDROID_NDK_ABI_NAME})
endif()


find_path(GMOCK_INCLUDE_DIR gmock/gmock.h
    HINTS
        $ENV{GMOCK_ROOT}/include
        ${GMOCK_ROOT}/include)
mark_as_advanced(GMOCK_INCLUDE_DIR)


find_path(GTEST_INCLUDE_DIR gtest/gtest.h
    HINTS
        $ENV{GMOCK_ROOT}/gtest/include
        ${GMOCK_ROOT}/gtest/include)
mark_as_advanced(GTEST_INCLUDE_DIR)


include(FindPackageHandleStandardArgs)

if(MSVC)
    _gmock_find_library(GMOCK_LIBRARY      gmock)
    _gmock_find_library(GMOCK_MAIN_LIBRARY gmock_main)
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(GMock DEFAULT_MSG GMOCK_LIBRARY GMOCK_INCLUDE_DIR GTEST_INCLUDE_DIR GMOCK_MAIN_LIBRARY)
elseif (ANDROID)
    _gmock_find_library(GMOCK_LIBRARY      gmock)
    _gmock_find_library(GMOCK_MAIN_LIBRARY gmock_main)
    _gmock_find_library(GTEST_LIBRARY      gtest)
    _gmock_find_library(GTEST_MAIN_LIBRARY gtest_main)
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(GMock DEFAULT_MSG GTEST_LIBRARY GMOCK_LIBRARY GMOCK_INCLUDE_DIR GTEST_INCLUDE_DIR GMOCK_MAIN_LIBRARY GTEST_MAIN_LIBRARY)
endif()

if(GMOCK_FOUND)
    set(GMOCK_INCLUDE_DIRS ${GMOCK_INCLUDE_DIR} ${GTEST_INCLUDE_DIR})
    _gmock_append_debugs(GMOCK_LIBRARIES      GMOCK_LIBRARY)
    _gmock_append_debugs(GMOCK_MAIN_LIBRARIES GMOCK_MAIN_LIBRARY)
    set(GMOCK_BOTH_LIBRARIES ${GMOCK_LIBRARIES} ${GMOCK_MAIN_LIBRARIES})

    _gmock_append_debugs(GTEST_LIBRARIES      GTEST_LIBRARY)
    _gmock_append_debugs(GTEST_MAIN_LIBRARIES GTEST_MAIN_LIBRARY)
    set(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
endif()

