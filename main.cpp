#include "./include/PLYIO.h"

int main(int argc, char *argv[]){
    PLYIO divideMap;
    divideMap.setFileName("/home/ouong/SLAM/bag/color.ply");
    divideMap.setNumOfOutFile(50);
    divideMap.run();
    return 0;
}