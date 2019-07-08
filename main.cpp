#include "CellAutomat.h"
#include "graphicalEngine.h"

size_t width = 128;
size_t height = 128;

void generateMap(){
   Map * Automat = init(height, width);
   GenBitmap(Automat);
   display(Automat);
   Map * newAutomat = initialiseMap(Automat);
   display(newAutomat);
   for(unsigned i = 0; i < 3; i++){
       Map * map = RunSimulation(newAutomat);
       display(map);
   }
}

int main(){
    generateMap();
    return 0;
}