// 将 ShanghaiTech 的地图分成多份，方便读取
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

#define LENGTH_OF_LINE 1024
using namespace std;

class PLYIO
{
struct Point_XYZ
{
    float x;
    float y;
    float z;
    unsigned char red;
    unsigned char green;
    unsigned char blue;         // 使用时不标记颜色
    // u_char end;
};

private:
    bool is_file_set;
    // bool is_out_num_file_set;
    size_t voxel_size = 60;  // 将每个小地图分为60*60*Height
    size_t NumOfOutFile;

    string _in_file;
    string _out_file;
    FILE* file_open;

    size_t numOfPoint;
public:
    PLYIO(/* args */);
    ~PLYIO();
    void setFileName (char const* filename);
    void setNumOfOutFile(size_t NumOfOutFile);
    bool run();
private:
    void loadPLY();
    void dividePLY();
    void saveMap(Point_XYZ *point, char *filename, size_t numOfPoint);
    void divideNvoxel(string& inFile,string& outFile, size_t voxel_size);
    size_t sizeOfPoint = sizeof(float)*3 + sizeof(unsigned char)*3;
};
#endif