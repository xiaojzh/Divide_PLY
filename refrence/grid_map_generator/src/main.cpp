# include "pcd_grid_divider.h"

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // // MainWindow w;
    // // w.show();
    // MainWindow::instance()->show();  // 使用单例模式
    // return a.exec();
    MAP_TOOLS::pcd_grid_divider map_divider;
    map_divider.setInFolder("/home/ouong/WorkSpace/SLAM/wangshu/src/Map/FullMap/ShanghaiTechSchool_210830.pcd");
    map_divider.setOutFolder("/home/ouong/WorkSpace/SLAM/wangshu/src/Map/DivideMap/ShanghaiTechSchool_210830_120");
    map_divider.setGridSize(120.0);
    // map_divider.setVoxelSize(0.0);
    map_divider.run();
    // map_divider.check_point_type("/home/ouong/WorkSpace/SLAM/wangshu/src/Map/FullMap/ShanghaiTechSchool_210830.pcd");
    // std::cout << argv[0] << std::endl;
}
