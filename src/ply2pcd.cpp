#include "../include/selectPoint.h"

int main(int argc, char** argv){
    selectPoint ply2pcd;
    ply2pcd.set_in_file("/home/ouong/WorkSpace/BAGs/DividedMap/ply/ShanghaiTech_0.ply");
    ply2pcd.set_out_file("/home/ouong/WorkSpace/BAGs/DividedMap/pcd/ShanghaiTech_0.pcd");
    ply2pcd.ply2pcd();
}