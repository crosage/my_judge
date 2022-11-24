cmake_minimum_required(VERSION 2.8)
project(myjudge )
LINK_LIBRARIES("pthread")
LINK_LIBRARIES("seccomp")
set(CMAKE_CXX_FLAGS "-O3 -std=c++11 -pie -fPIC -pthread")
file(GLOB SOURCE "src/*.cpp")  #glob表达式匹配放到source
include_directories(../include)
add_executable(
    myjudge
    ${SOURCE}
)