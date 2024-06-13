set(psql_test_TEST_SOURCES
    test_main.cpp)

add_executable(psql_test_test ${psql_test_TEST_SOURCES})
target_include_directories(psql_test_test PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_link_directories(psql_test_test PRIVATE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
target_link_libraries(psql_test_test PRIVATE psql_test_shared fmt::fmt ${GTEST_LIBRARIES})
set_target_properties(psql_test_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)

add_custom_target(test COMMAND psql_test_test)
