cmake_minimum_required(VERSION 3.10)
project(utilLib)
 
set(CMAKE_CXX_STANDARD 14)
 
add_library(utilLib SHARED util.cpp) # 诉生成一个库文件。