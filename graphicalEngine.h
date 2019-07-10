#ifndef AUTOMATADUNGEONE_GRAPHICALENGINE_H
#define AUTOMATADUNGEONE_GRAPHICALENGINE_H


#include "SDL_image.h"
#include "SDL2/SDL.h"
#include "ImageProcessor.h"


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
