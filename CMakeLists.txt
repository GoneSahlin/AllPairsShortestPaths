
project(CPSC_450_FINAL)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O0")
set(CMAKE_BUILD_TYPE Debug)

# locate gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# create unit test executable
add_executable(final_test final_test.cpp)
target_link_libraries(final_test ${GTEST_LIBRARIES} pthread)

add_executable(final_perf final_perf.cpp util.cpp)


 
