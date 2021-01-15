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

add_executable(${BINARY}_cli ${SOURCES} ${HEADERS})
add_library(${BINARY}_lib STATIC ${SOURCES} ${HEADERS})

target_include_directories(${BINARY}_cli PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")

target_include_directories(${BINARY}_lib PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")

target_compile_features(${BINARY}_cli PRIVATE cxx_std_17)
target_compile_features(${BINARY}_lib PRIVATE cxx_std_17)

if(MSVC)
  target_compile_options(${BINARY}_cli PRIVATE /W4 /WX)
  target_compile_options(${BINARY}_lib PRIVATE /W4 /WX)
else()
  target_compile_options(${BINARY}_cli PRIVATE -Werror -Wall -Wextra -pedantic -O3)
  target_compile_options(${BINARY}_lib PRIVATE -Werror -Wall -Wextra -pedantic -O3)
endif()