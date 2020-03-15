set(TARGET_NAME "dns_cache_test")
set(SRC_FILES  dns_cache_test.cpp)
add_executable(${TARGET_NAME} ${SRC_FILES})
set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-O3"
)

target_link_libraries(${TARGET_NAME} PRIVATE GTest::GTest GTest::Main Threads::Threads ${PROJECT_NAME})
target_include_directories(${TARGET_NAME} PRIVATE ../src)

add_test(${TARGET_NAME} ${TARGET_NAME})
set_tests_properties( ${TARGET_NAME} PROPERTIES WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")


set(TARGET_NAME "dns_cache_time_test")
set(SRC_FILES  dns_cache_time_test.cpp)
add_executable(${TARGET_NAME} ${SRC_FILES})
set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-O3"
)

target_link_libraries(${TARGET_NAME} PRIVATE ${PROJECT_NAME})
target_include_directories(${TARGET_NAME} PRIVATE ../src)

add_test(${TARGET_NAME} ${TARGET_NAME})
set_tests_properties( ${TARGET_NAME} PROPERTIES WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")