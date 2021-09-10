#include "../include/selectPoint.h"

int main(int argc, char** argv){
    selectPoint ply2pcd;
    string in_filename;
    string out_filename;
    for (size_t i = 0; i <= 20; i++)
    {
        in_filename = "/home/ouong/WorkSpace/BAGs/DividedMap/ply/ShanghaiTech_" 
                    + to_string(i) + ".ply";
        out_filename = "/home/ouong/WorkSpace/BAGs/DividedMap/pcd/ShanghaiTech_"
                    + to_string(i) + ".pcd";
        ply2pcd.set_in_file(in_filename);
        ply2pcd.set_out_file(out_filename);
        ply2pcd.ply2pcd();

    }
}