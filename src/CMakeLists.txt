set(BINARY ${CMAKE_PROJECT_NAME})

add_subdirectory(geometry)

set(SOURCES
    ${SOURCES}
    main.cpp
    utility.cpp
    utility.hpp)

add_executable(${BINARY}_run ${SOURCES} ${HEADERS})

add_library(${BINARY}_lib STATIC ${SOURCES})

if(MSVC)
  target_compile_options(${BINARY}_run PRIVATE /W4 /WX)
else()
  target_compile_options(${BINARY}_run PRIVATE -Wall -Wextra -pedantic -Werror)
endif()