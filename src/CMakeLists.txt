set(psql_test_SOURCES
    # sources
    stub.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${psql_test_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt ${PQXX_LIBRARIES})

if (UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE dl pthread m)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

if (BUILD_TESTS)
    add_library(${PROJECT_NAME}_shared SHARED ${psql_test_SOURCES})
    target_include_directories(${PROJECT_NAME}_shared PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_link_directories(${PROJECT_NAME}_shared PRIVATE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    target_link_libraries(${PROJECT_NAME}_shared PRIVATE fmt::fmt ${PQXX_LIBRARIES})
    install(TARGETS ${PROJECT_NAME}_shared LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif()

# Prepend the full path to each source file
# Create custom target for running clang tidy
list(TRANSFORM psql_test_SOURCES PREPEND ${CMAKE_SOURCE_DIR}/src/)

set(CLANG_TIDY_OPTIONS ${CLANG_TIDY_OPTIONS}
    -extra-arg=-Wno-unknown-warning-option
    -extra-arg=-Wno-ignored-optimization-argument
    -extra-arg=-Wno-unused-command-line-argument
    -warning-as-errors=*)

if("${CLANG_TIDY_OPTIONS_DRIVER_MODE}" STREQUAL "cl")
    set(CLANG_TIDY_OPTIONS ${CLANG_TIDY_OPTIONS} -extra-arg=/std:c++${CMAKE_CXX_STANDARD})
else()
    set(CLANG_TIDY_OPTIONS ${CLANG_TIDY_OPTIONS} -extra-arg=-std=c++${CMAKE_CXX_STANDARD})
endif()

add_custom_target(tidy
    COMMAND clang-tidy -p ${CMAKE_BINARY_DIR} --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy --use-color ${psql_test_SOURCES}
    COMMENT "Running tidy checks"
    VERBATIM)

add_custom_target(format
    COMMAND clang-format --Werror --sort-includes --verbose ${psql_test_SOURCES}
    COMMENT "Running formatting checks"
    VERBATIM)

add_custom_target(formatw
    COMMAND clang-format --Werror --sort-includes --verbose -i ${psql_test_SOURCES}
    COMMENT "Running formatting checks"
    VERBATIM)
