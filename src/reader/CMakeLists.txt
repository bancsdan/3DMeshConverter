set(SOURCES
   ${SOURCES}
   ${CMAKE_CURRENT_SOURCE_DIR}/obj_reader.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/reader_factory.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/supported_input_formats.cpp
   PARENT_SCOPE
)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/ireader.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/obj_reader.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/reader_factory.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/supported_input_formats.hpp
   PARENT_SCOPE
)