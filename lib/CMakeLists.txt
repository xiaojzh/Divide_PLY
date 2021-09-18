cmake_minimum_required(VERSION 3.10)
project(divideMapLib)
 
set(CMAKE_CXX_STANDARD 14)
 
add_library(divideMapLib SHARED PLYIO.cpp selectPoint.cpp) # 诉生成一个库文件。

target_link_libraries(divideMapLib utilLib)