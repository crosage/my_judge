cmake_minimum_required(VERSION 2.8)
project(judger)
LINK_LIBRARIES("pthread")
LINK_LIBRARIES("seccomp")
set(CMAKE_C_FLAGS "-O3 -std=c++11 -pie -fPIC -pthread")
file(GLOB SOURCE "dealCompile/*.cpp")  #glob表达式匹配放到source
file(GLOB SOURCES "judger/src/*.cpp")
include_directories(include)
# add_executable(
#     compiler
#     ${SOURCE}
# )
add_executable(
    ajudger
    ${SOURCES}
)