cmake_minimum_required(VERSION 3.8)

# project configuration
project("minijavac" CXX C)
set(PROJECT_ROOT ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/bin)

# flex-bison configuration
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

flex_target(scanner ${PROJECT_ROOT}/src/ast/scanner.l ${PROJECT_ROOT}/src/ast/scanner.l.cpp
        COMPILE_FLAGS "-+ --header-file=${PROJECT_ROOT}/src/ast/scanner.l.hpp")
bison_target(parser ${PROJECT_ROOT}/src/ast/parser.y ${PROJECT_ROOT}/src/ast/parser.y.cpp
        COMPILE_FLAGS "-v")
add_flex_bison_dependency(scanner parser)

#file(GLOB_RECURSE SOURCE_FILES ${PROJECT_ROOT}/src "*.h" "*.c" "*.hpp" ".cpp")

set(SOURCE_FILES
        src/main.cpp
        src/ast/visitor.h
        src/ast/grammar.h
        src/ast/declaration.h
        src/ast/expression.h
        src/ast/statement.h
        src/ast/type.h
        src/ast/grammardecl.h
        src/ast/treeserializer.h
        src/ast/treeserializer.cpp
        src/ast/scanner.l.cpp
        src/ast/parser.y.cpp
        src/symboltable/symbol.h
        src/symboltable/symbol.cpp
        src/symboltable/table.h
        src/symboltable/table.cpp
        src/symboltable/classinfo.h
        src/symboltable/classinfo.cpp
        src/symboltable/methodinfo.cpp
        src/symboltable/methodinfo.h
        src/symboltable/variableinfo.cpp
        src/symboltable/variableinfo.h
        src/symboltable/tableinitializer.cpp
        src/symboltable/tableinitializer.h
        test/symboltable_test.cpp
        src/ast/treedeallocator.cpp
        src/ast/treedeallocator.h
        src/symboltable/typechecker.cpp
        src/symboltable/typechecker.h
        src/utils/utils.h
        src/utils/utils.cpp)

add_executable(minijavac ${SOURCE_FILES})

target_include_directories(minijavac PUBLIC
        ${PROJECT_ROOT}/src
        ${PROJECT_ROOT}/src/ast
        ${PROJECT_ROOT}/src/symboltable
        ${PROJECT_ROOT}/src/utils)

# gtest configuration
set(GTEST_ROOT ${PROJECT_ROOT}/lib/gtest/googletest)
add_subdirectory(${GTEST_ROOT})
target_link_libraries(minijavac gtest gtest_main)

enable_testing()

# fmtlib configuration
add_subdirectory(${PROJECT_ROOT}/lib/fmtlib)
target_link_libraries(minijavac fmt)
target_include_directories(minijavac PUBLIC ${PROJECT_ROOT}/lib/fmtlib/)
