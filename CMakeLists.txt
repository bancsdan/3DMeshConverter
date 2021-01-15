cmake_minimum_required(VERSION 3.11)

project(converter)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include_directories(lib/Eigen)
add_subdirectory(lib/googletest)
add_subdirectory(src)
add_subdirectory(tests)
