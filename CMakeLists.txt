PROJECT(oblivion-core)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

IF(APPLE)
    SET(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -std=c++11 -stdlib=libc++ -fPIC")
ELSEIF(UNIX)
    SET(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -std=c++11 -fPIC")
ENDIF()

INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(test)

SET(CORE_SOURCES
    "src/oblivion/core/exception.cpp"
    "src/oblivion/core/file.cpp"
    "src/oblivion/core/random.cpp"
    "src/oblivion/core/string_util.cpp")

IF(WIN32)
    SET(CORE_SOURCES ${CORE_SOURCES}
        "src/oblivion/core/dynamic_lib_windows.cpp"
        "src/oblivion/core/file_windows.cpp")
ENDIF()

IF(UNIX)
    SET(CORE_SOURCES ${CORE_SOURCES}
        "src/oblivion/core/dynamic_lib_posix.cpp"
        "src/oblivion/core/file_posix.cpp")
ENDIF()

SET(CORE_HEADERS
    "include/oblivion/core/algorithm.h"
    "include/oblivion/core/algorithm_inl.h"
    "include/oblivion/core/base.h"
    "include/oblivion/core/dynamic_lib.h"
    "include/oblivion/core/exception.h"
    "include/oblivion/core/file.h"
    "include/oblivion/core/random.h"
    "include/oblivion/core/string_util.h"
    "include/oblivion/core/string_util_inl.h"
    "include/oblivion/core/types.h"
    "include/oblivion/core/windows.h")

ADD_LIBRARY(oblivion-core SHARED ${CORE_SOURCES} ${CORE_HEADERS})
SET_TARGET_PROPERTIES(oblivion-core PROPERTIES
    COMPILE_FLAGS "-D_CRT_SECURE_NO_WARNINGS -DOBLIVION_CORE_EXPORTS")

IF (UNIX)
    TARGET_LINK_LIBRARIES(oblivion-core dl)
ENDIF()

SET(TEST_SOURCES
    "test/gtest/gtest-all.cc"
    "test/main.cpp"
    "test/oblivion/core/algorithm_test.cpp"
    "test/oblivion/core/file_test.cpp"
    "test/oblivion/core/string_util_test.cpp"
    "test/oblivion/core/types_test.cpp")

ADD_EXECUTABLE(oblivion-core-test ${TEST_SOURCES})
SET_TARGET_PROPERTIES(oblivion-core-test PROPERTIES
    COMPILE_FLAGS "-DGTEST_HAS_TR1_TUPLE=0")

IF(UNIX)
    TARGET_LINK_LIBRARIES(oblivion-core-test pthread)
ENDIF()

TARGET_LINK_LIBRARIES(oblivion-core-test oblivion-core)

ENABLE_TESTING()
ADD_TEST(unit_tests oblivion-core-test)