cmake_minimum_required(VERSION 3.10)
project(divideMap)
 
set(CMAKE_CXX_STANDARD 14)
find_package(PCL REQUIRED)

list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4")

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_subdirectory(lib)
add_subdirectory(common)

# set(divideMapLib_DEPS utilLib)
 
add_executable(ply2pcd src/ply2pcd.cpp)  
target_link_libraries(ply2pcd utilLib divideMapLib ${PCL_LIBRARIES})
# add_executable(ply2pcd src/ply2pcd.cpp lib/selectPoint.cpp)  
# target_link_libraries(ply2pcd ${PCL_LIBRARIES})

add_executable(divideMap src/divideMap.cpp)
target_link_libraries(divideMap utilLib divideMapLib ${PCL_LIBRARIES})
# add_executable(divideMap src/divideMap.cpp lib/PLYIO.cpp)
# target_link_libraries(divideMap utilLib ${PCL_LIBRARIES})

# 设置gdb
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")