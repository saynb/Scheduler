
add_executable( scheduler
    scheduler.cpp
    scheduler_thread.cpp
    logger_thread.cpp
    main.cpp
    task.cpp )

add_library( scheduler_for_test
    scheduler.cpp
    scheduler_thread.cpp
    logger_thread.cpp
    main.cpp
    task.cpp )
target_link_libraries(scheduler scheduler_lib)
target_link_libraries(scheduler_for_test scheduler_lib)

add_subdirectory("test")
