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

flex_target(scanner ${PROJECT_ROOT}/src/scanner.l ${PROJECT_ROOT}/src/scanner.l.cpp
        COMPILE_FLAGS "-+ --header-file=${PROJECT_ROOT}/src/scanner.l.hpp")
bison_target(parser ${PROJECT_ROOT}/src/parser.y ${PROJECT_ROOT}/src/parser.y.cpp)
add_flex_bison_dependency(scanner parser)

include_directories({PROJECT_ROOT}/src)

set(SOURCE_FILES
        src/main.cpp
        src/scanner.l.cpp
        src/parser.y.cpp
        src/visitor.h
        src/grammar.h
        )
add_executable(minijavac ${SOURCE_FILES})
