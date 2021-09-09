#include "../include/PLYIO.h"

int main(int argc, char *argv[]){
    PLYIO divideMap;
    divideMap.setFileName("/home/ouong/WorkSpace/BAGs/DividedMap/color.ply");
    divideMap.setNumOfOutFile(20);
    divideMap.run();
    return 0;
}