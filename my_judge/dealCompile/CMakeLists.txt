cmake_minimum_required(VERSION 2.8)
project(dealCompile)
LINK_LIBRARIES("pthread")
set(CMAKE_C_FLAGS "-O3 -std=c++11 -pie -fPIC -pthread")
file(GLOB SOURCE "*.cpp")  #glob表达式匹配放到source
include_directories(../include)
add_executable(
    dealCompile
    ${SOURCE}
)