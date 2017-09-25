add_executable (ping_test
    ping_test.cpp)

target_link_libraries(ping_test client_lib)
include_directories("${PROJECT_SOURCE_DIR}/scheduler"})
