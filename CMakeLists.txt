cmake_minimum_required(VERSION 3.15)
project(voyage CXX)

add_subdirectory(vendor)
add_subdirectory(tests)

include_directories("include")
file(GLOB SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCES})
