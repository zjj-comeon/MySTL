project(stl_test)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} test.cc)

target_link_libraries(${PROJECT_NAME} stl)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)

gtest_discover_tests(${PROJECT_NAME})
