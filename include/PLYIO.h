// PLYIO.h 
// xiaojzh
// 2021.9.10
// 1. 实现读取，存放PLY点云数据（基础）
// 2. 分割成指定文件数 (分割n个文件)
// 3. 分割成指定文件大小(每个文件字节数固定)
// 4. 分割成指定方块(voxel_size*voxel_size*height)
#ifndef PLYIO_H
#define PLYIO_H

#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <memory.h>
#include <sys/stat.h>
#include "../common/util.h"

#define LENGTH_OF_LINE 1024
using namespace std;

class PLYIO
{
struct Point_XYZ
{
    // 由于struct存在字节数对齐，sizeof（Point_XYZ）大小不等于简单每个sizeof相加
    float x;
    float y;
    float z;
    u_char red;
    u_char green;
    u_char blue;        
}; // Point_XYZ

private:
    size_t sizeOfPoint = sizeof(float)*3 + sizeof(u_char)*3;

    bool is_in_file_set;
    bool is_out_file_set;
    
    string _in_file;
    string _out_file;
    FILE* file_open;
    
    size_t numOfPoint;
    size_t numOfOutFile;
    size_t sizeOfOutFile;
    size_t voxel_size;  // 将每个小地图分为60*60*Height
    




public:
    PLYIO(/* args */);
    ~PLYIO();
    // 分成指定文件数
    void divideNPLY(const string& inFile, const string& outFile, size_t numOfOutFile);
    // 分成指定的大小
    void divideNsize(const string& inFile, const string& outFile, size_t sizeOfOutFile);
    // 分成指定方块
    void divideNvoxel(const string& inFile, const string& outFile, size_t voxel_size);
    // 在文件开头添加抬头
    void writeHeader(string dirpath);
    
private:
    void loadPLY();
    void saveMap(Point_XYZ *point, char *filename, size_t numOfPoint);
};
#endif