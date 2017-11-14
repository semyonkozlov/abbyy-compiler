project(test)

add_executable(symboltable_test symboltable_test.cpp)
target_link_libraries(symboltable_test gtest gtest_main)