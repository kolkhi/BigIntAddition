# CMakeList.txt : CMake project for BigIntAddition, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable (BigIntAddition "BigIntAddition.cpp" "BigIntAddition.h" "main.cpp" "TestCasesLoader.h" "TestCasesLoader.cpp")

find_package(Boost)

include_directories(${Boost_INCLUDE_DIRS})

set (TESTS_SOURCES "tests/BigIntAdditionTest.cpp" "./BigIntAddition.cpp" "./TestCasesLoader.cpp")

set (TEST BigIntAdditionTest)

add_executable (${TEST} ${TESTS_SOURCES})

target_link_libraries (${TEST} ${PROJECT})

enable_testing ()

add_test (${TEST} ${TEST})