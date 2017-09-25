
add_executable( scheduler_test
    scheduler_test.cpp)

add_dependencies(scheduler_test scheduler_lib scheduler_for_testgtest_main)
target_link_libraries(scheduler_test scheduler_lib scheduler_for_test gtest_main)
add_test(NAME scheduler_test COMMAND scheduler_execute)

