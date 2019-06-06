cmake_minimum_required(VERSION 3.4)

project(first_homework_niit)

set(CMAKE_CXX_STANDARD 17)

file(GLOB HPPS "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB CPPS "${PROJECT_SOURCE_DIR}/src/*.cpp")

set(INCLUDE "${PROJECT_SOURCE_DIR}/include")
include_directories(${INCLUDE})

add_executable(${PROJECT_NAME} ${CPPS} ${HPPS})


