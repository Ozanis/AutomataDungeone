#include "graphicalEngine.h"


int main(){
    Map * map = generateMap();
//    genPng(map);
    Graphics Engine("/home/max/dungeone.png", 0, 0, 640, 480);
    SDL_Event event;
    while(event.type!= SDL_QUIT){
        SDL_PollEvent(&event);
        Engine.draw();
    }
    return 0;
}