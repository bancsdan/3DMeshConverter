set(BINARY ${CMAKE_PROJECT_NAME})

add_subdirectory(geometry)
add_subdirectory(reader)
add_subdirectory(writer)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utility.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/exception.cpp)

set(HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/utility.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/exception.hpp)

add_executable(${BINARY}_run ${SOURCES} ${HEADERS})
add_library(${BINARY}_lib STATIC ${SOURCES} ${HEADERS})

target_include_directories(${BINARY}_run PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")

target_include_directories(${BINARY}_lib PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")

set_property(TARGET ${BINARY}_run PROPERTY CXX_STANDARD 17)
set_property(TARGET ${BINARY}_lib PROPERTY CXX_STANDARD 17)
set_property(TARGET ${BINARY}_run PROPERTY CMAKE_CXX_STANDARD_REQUIRED True)
set_property(TARGET ${BINARY}_lib PROPERTY CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
  target_compile_options(${BINARY}_run PRIVATE /W4 /WX)
else()
  target_compile_options(${BINARY}_run PRIVATE -Wall -Wextra -pedantic -Werror)
endif()