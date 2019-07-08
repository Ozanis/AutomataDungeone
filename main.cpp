#include "CellAutomat/CellAutomat.h"


int main(){
   bool Automat[128][128] = {false, false};
   GenBitmap(Automat);
   bool newAutomat = RunSimulation(Automat);
}