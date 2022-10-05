cmake_minimum_required(VERSION 2.8)
project(myjudge )
LINK_LIBRARIES("pthread")
LINK_LIBRARIES("seccomp")
set(CMAKE_C_FLAGS "-O3 -std=gnu99 -pie -fPIC -pthread")
file(GLOB SOURCE "src/*.cpp")  #glob表达式匹配放到source
add_executable(
    myjudge
    ${SOURCE}
)