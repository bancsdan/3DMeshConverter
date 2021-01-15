set(BINARY ${CMAKE_PROJECT_NAME}_tests)

add_executable(${BINARY}
    main.cpp
    unittest_utility.cpp
    unittest_triangle.cpp
)

set_property(TARGET ${BINARY} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${BINARY} PROPERTY CMAKE_CXX_STANDARD_REQUIRED True)

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_include_directories(${BINARY} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../src>")
  target_include_directories(${BINARY} PRIVATE
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/lib/Eigen>")

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)