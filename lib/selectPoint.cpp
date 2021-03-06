# include "../include/selectPoint.h"

selectPoint::selectPoint(){
    this->is_set_in_file = false;
    this->is_set_out_file = false;
}

selectPoint::~selectPoint(){}

void selectPoint::set_in_file(const string &filename){
    this->_in_file = filename;
    this->is_set_in_file = true;
}
void selectPoint::set_out_file(const string &filename){
    this->_out_file = filename;
    this->is_set_out_file = true;
}

bool selectPoint::ply2pcd(){
    if (!this->is_set_out_file || !this->is_set_in_file) {
        std::cout << "confirm in_folder/out_folder/grid_size first!" << std::endl;
        return false;
    }
    // pcl::PLYReader reader;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);
    // reader.read<pcl::PointXYZ>(this->_in_file,*cloud);
    if (pcl::io::loadPLYFile<pcl::PointXYZ>(this->_in_file,*cloud) == -1)
	{
		PCL_ERROR("Couldn't read file sample \n");
		return (-1);
	}
    cout << "the first point: " <<  cloud->points[0].x << " "
                                <<  cloud->points[0].y << " "
                                <<  cloud->points[0].z << endl;
    pcl::VoxelGrid<pcl::PointXYZ> sor;
    sor.setInputCloud (cloud);
    sor.setLeafSize (1.0f, 1.0f, 1.0f);
    sor.filter (*cloud_filtered);
    pcl::io::savePCDFile(this->_out_file, *cloud_filtered);
    return true;
}