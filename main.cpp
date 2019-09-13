#include "graphicalEngine.h"
#include "unistd.h"

static float defaultProbability = 0.45;
static int DethLim = 3;
static int BirthLim = 4;
static unsigned width = 80;
static unsigned height = 80;
static unsigned iterationOrd = 17;

static unsigned scale = 1;
static char const * defaultPath ="/home/max/Projects/AutomataDungeone/buffer/dungeone.png";

static unsigned window_x = 0;
static unsigned window_y = 0;
static unsigned window_width = 640;
static unsigned window_height = 480;


int main(){
    CellAutomat Map(defaultProbability, DethLim, BirthLim, width, height);
    Map.runSimulation();
    Map.update(iterationOrd);
    Png pic(Map.synthesis(), defaultPath, scale, stounPalette, cavePalette);

//    Png pic(Map.synthesis(), defaultPath, scale,  oceanPalette, stounPalette);
//    Png pic(map, defaultPath, scale, sandPalette, forestPalette);
    pic.genPng();

    Graphics Engine(defaultPath, window_x, window_y, window_width, window_height);
    SDL_Event event;
    while(event.type!= SDL_QUIT){
        SDL_PollEvent(&event);
        Engine.draw();
    }
    return 0;
}
