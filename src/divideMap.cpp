#include "../include/PLYIO.h"

int main(int argc, char *argv[]){
    PLYIO divideMap;
    // divideMap.divideNPLY("/home/ouong/WorkSpace/BAGs/DividedMap/color.ply","/home/ouong/WorkSpace/BAGs/DividedMap/ply",20);
    // divideMap.divideNsize("/home/ouong/WorkSpace/BAGs/DividedMap/color.ply","/home/ouong/WorkSpace/BAGs/DividedMap/size",15*10000000);
    divideMap.divideNvoxel("/home/xiaojz/ws/SmartCar/DivideMap/color.ply","/home/xiaojz/ws/SmartCar/DivideMap/voxel",60);
    // divideMap.writeHeader("/home/xiaojz/ws/SmartCar/DivideMap/voxel");
    return 0;
}