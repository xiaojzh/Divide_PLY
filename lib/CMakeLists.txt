cmake_minimum_required(VERSION 3.10)
project(divideMapLib)
 
set(CMAKE_CXX_STANDARD 11)
 
add_library(divideMapLib SHARED PLYIO.cpp selectPoint.cpp) # 诉生成一个库文件。