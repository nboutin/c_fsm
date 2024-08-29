
add_executable(${PROJECT_NAME}
    fsm_definition/fsm_on_off.c
    suites/test_fsm_action.cpp
    suites/test_fsm_null.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE fsm_definition)

target_link_libraries(${PROJECT_NAME} PRIVATE fsm gtest gtest_main gmock)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}
    XML_OUTPUT_DIR ${CMAKE_BINARY_DIR}/test_report/xml
)
