#ifndef AUTOMATADUNGEONE_GRAPHICALENGINE_H
#define AUTOMATADUNGEONE_GRAPHICALENGINE_H


#include "SDL_image.h"
#include "SDL2/SDL.h"
#include "CellAutomat.h"
#include "gd.h"


using std::cerr;
using std::cout;

/*
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
*/

class Graphics{
    public:
    Graphics(const char * imgPath, int x, int y, int w, int h);
    ~Graphics();
    void draw();

    SDL_Window * win = nullptr;
    SDL_Texture * tex = nullptr;
    SDL_Renderer * ren = nullptr;
    SDL_Surface * surf = nullptr;
    SDL_Rect rect = {0,0,0,0};
    const char * winCapt = "AutomataDungeone";
};


Graphics :: Graphics(const char * imgPath, int x, int y, int w, int h){
     if(SDL_Init(SDL_INIT_VIDEO) != 0){
        cerr << "Failed to initialize SDL";
        _exit(0);
    }

    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
         cerr << "Failed to initialize SDL_img";
        _exit(0);
    }

    this->win = SDL_CreateWindow(this->winCapt, x, y, w, h, SDL_WINDOW_SHOWN);
    if (!win){
        cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        _exit(0);
    }

   this->surf = IMG_Load(imgPath);
    if (!this->surf){
        cerr << "Failed to load image";
        SDL_FreeSurface(this->surf);
        _exit(0);
    }

    this->ren = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!this->ren){
        cerr << "No SDL renderer";
        _exit(0);
    }

    this->tex = SDL_CreateTextureFromSurface(this->ren, this->surf);
    if(!this->tex) {
        cerr << "Failede to crate texture";
        _exit(0);
    }

    SDL_FreeSurface(this->surf);
    this->rect = {x, y, w, h};
}


Graphics :: ~Graphics(){
    SDL_DestroyTexture(this->tex);
    SDL_DestroyRenderer(this->ren);
    SDL_DestroyWindow(this->win);
    IMG_Quit();
    SDL_Quit();
}


void Graphics :: draw(){
    if(this->tex)
        SDL_RenderCopy(this->ren, this->tex, nullptr, &rect);
    else{
        SDL_SetRenderDrawColor(this->ren, 100, 100, 100, 0);
        SDL_RenderFillRect(this->ren, &rect);

    }
    SDL_RenderPresent(this->ren);
}


#endif //AUTOMATADUNGEONE_GRAPHICALENGINE_H
