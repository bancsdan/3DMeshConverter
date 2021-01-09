set(BINARY ${CMAKE_PROJECT_NAME})

add_subdirectory(geometry)

set(SOURCES
    ${SOURCES}
    main.cpp
    utility.cpp
    utility.hpp)

add_executable(${BINARY}_run ${SOURCES} ${HEADERS})

add_library(${BINARY}_lib STATIC ${SOURCES})