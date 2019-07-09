#ifndef AUTOMATADUNGEONE_GRAPHICALENGINE_H
#define AUTOMATADUNGEONE_GRAPHICALENGINE_H


#include <SDL_image.h>
#include "SDL2/SDL.h"
#include "CellAutomat.h"
#include "gd.h"


void genPng(Map * map){
    gdImagePtr im;
    FILE *pngout;
    int black;
    int brown;
    im = gdImageCreate(map->height*10, map->width*10);
    black = gdImageColorAllocate(im, 0, 0, 0);
    brown = gdImageColorAllocate(im, 222, 184, 135);
    unsigned i = 0, j = 0;
    while(i <= map->height*10){
        while(j <= map->width*10){
            unsigned x = i+10, y = j+10;
            gdImageRectangle(im, i, j, x, y, brown);
            i = x, j = y;
        }
    }
    pngout = fopen("/home/max/dungeone.png", "wb");
    gdImagePng(im, pngout);
    fclose(pngout);
    gdImageDestroy(im);
}


SDL_Texture * loadPNG(const char * path, SDL_Renderer * ren) {
   if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "Failed to initialize SDL_img";
        _exit(0);
    }
   SDL_Surface * image = nullptr;
   image = IMG_Load(path);
   if (!image){
       std::cerr << "Failed to create surface";
       _exit(0);
   }
   SDL_Texture * tex = SDL_CreateTextureFromSurface(ren, image);
   if(!tex) {
       std::cerr << "Failede to crate texture";
       _exit(0);
   }
   SDL_FreeSurface(image);
   return tex;
}


SDL_Window * createWin(unsigned x, unsigned y, unsigned w, unsigned h){
   SDL_Window * win = SDL_CreateWindow("AutomataDungeone", x, y, w, h, SDL_WINDOW_SHOWN);
    if (win == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        _exit(0);
    }
    return win;
}


void cleaner(SDL_Renderer * ren, SDL_Window * win, SDL_Texture * tex){
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}


void draw(SDL_Renderer * ren, SDL_Texture * tex, int x, int y, int h, int w){
    SDL_Rect rect = {x, y, w, h};
    if(tex)
        SDL_RenderCopy(ren, tex, nullptr, &rect);
    else{
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
        SDL_RenderFillRect(ren, &rect);
    }
}


void GraphicalEngine(){
    SDL_Window * win = nullptr;
    SDL_Texture * tex = nullptr;
    SDL_Renderer * ren = nullptr;

    win = createWin(100, 100, 640, 480);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    tex = loadPNG("/home/max/dungeone.png", ren);
    draw(ren, tex, 100, 100, 640, 480);

    SDL_Delay(1000);

    cleaner(ren, win, tex);
}


#endif //AUTOMATADUNGEONE_GRAPHICALENGINE_H
