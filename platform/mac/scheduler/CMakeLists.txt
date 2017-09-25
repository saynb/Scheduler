add_library( scheduler_lib
    local_server.cpp
    scheduler_thread.cpp)

include_directories("${PROJECT_SOURCE_DIR}/scheduler"})
