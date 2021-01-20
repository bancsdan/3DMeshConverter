cmake_minimum_required(VERSION 3.7)

project(converter)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(lib/googletest)
add_subdirectory(src)
add_subdirectory(tests)
