#include "graphicalEngine.h"

static float defaultProbability = 0.45;
static int DethLim = 3;
static int BirthLim = 6;
static unsigned width = 128;
static unsigned height = 128;


int main(){
    CellAutomat Map(defaultProbability, DethLim, BirthLim, width, height);
    Map.update(3);
    display(Map.grid, height, width);
//    genPng(map);


    Graphics Engine("/home/max/dungeone.png", 0, 0, 640, 480);
    SDL_Event event;
    while(event.type!= SDL_QUIT){
        SDL_PollEvent(&event);
        Engine.draw();
    }
    return 0;
}