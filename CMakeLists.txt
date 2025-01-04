cmake_minimum_required(VERSION 3.16)
project("cppchess")

set(CMAKE_CXX_STANDARD 11)

set(SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES
    "${SRC_PATH}/*.cpp"
    "${INC_PATH}/*.cpp"
)

file(GLOB_RECURSE INC_FILES
    "${SRC_PATH}/*.hpp"
    "${INC_PATH}/*.hpp"
)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${INC_FILES})