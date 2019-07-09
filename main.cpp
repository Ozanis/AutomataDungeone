#include "graphicalEngine.h"


int main(){
    generateMap();

//    const char path = system("pwd");
    genBmp(generateMap(), "/home/max/Dunge.bmp");
    createWindow();
    return 0;
}