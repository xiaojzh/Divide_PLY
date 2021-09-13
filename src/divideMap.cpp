#include "../include/PLYIO.h"

int main(int argc, char *argv[]){
    PLYIO divideMap;
    // divideMap.divideNPLY("/home/ouong/WorkSpace/BAGs/DividedMap/color.ply","/home/ouong/WorkSpace/BAGs/DividedMap/ply",20);
    // divideMap.divideNsize("/home/ouong/WorkSpace/BAGs/DividedMap/color.ply","/home/ouong/WorkSpace/BAGs/DividedMap/size",15*10000000);
    divideMap.divideNvoxel("/home/ouong/WorkSpace/BAGs/DividedMap/color.ply","/home/ouong/WorkSpace/BAGs/DividedMap/voxel",60);
    return 0;
}