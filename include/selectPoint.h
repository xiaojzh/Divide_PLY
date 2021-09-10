#ifndef SELECTPOINT_H
#define SELECTPOINT_H

#include <pcl-1.8/pcl/io/pcd_io.h>
#include <pcl-1.8/pcl/io/ply_io.h>
#include <pcl-1.8/pcl/point_types.h> 
#include <pcl-1.8/pcl/filters/voxel_grid.h>

using namespace std;

class selectPoint{
private:
    string _in_file;
    string _out_file;
    bool is_set_in_file;
    bool is_set_out_file;

public:
    selectPoint();
    ~selectPoint();
    void set_in_file(const string &filename);
    void set_out_file(const string &filename);
    bool ply2pcd();
private:
    
};

#endif