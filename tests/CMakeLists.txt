cmake_minimum_required(VERSION 3.0)
project(ColorBoyTests)

# Prepare "Catch" library for other executables.
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Remove project's main.cpp.
list(REMOVE_ITEM PROJECT_SRC_LST ${PROJECT_SRC_DIR}/src/main.cpp)

# Configure file
set(ROMFOLDERPATH "${CMAKE_CURRENT_LIST_DIR}")
configure_file(consts.h.in consts.h @ONLY)

# Make test executable.
file(GLOB_RECURSE TEST_SOURCES ${PROJECT_SRC_LST} ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(colorboy_tests ${TEST_SOURCES})
target_include_directories(colorboy_tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(colorboy_tests Catch)

add_test(test_all colorboy_tests)
