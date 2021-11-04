cmake_minimum_required(VERSION 3.0.0)
project(SIXTH_LAB VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(SIXTH_LAB
    lab6.cpp
    sqlite3.c
    sqlite3.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
