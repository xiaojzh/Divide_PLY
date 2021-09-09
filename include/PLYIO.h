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

using namespace std;

class PLYIO
{
struct Point_XYZ
{
    float x;
    float y;
    float z;
    u_char red;
    u_char green;
    u_char blue;         // 使用时不标记颜色
    // u_char end;
};

private:
    bool is_file_set;
    // bool is_out_num_file_set;
    size_t voxel_size = 60;  // 将每个小地图分为60*60*Height
    size_t NumOfOutFile;

    char const *_in_file;
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
    size_t sizeOfPoint = sizeof(float)*3 + sizeof(u_char)*3;
};
#endif