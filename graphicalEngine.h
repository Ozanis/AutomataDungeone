#ifndef AUTOMATADUNGEONE_GRAPHICALENGINE_H
#define AUTOMATADUNGEONE_GRAPHICALENGINE_H


#include "SDL2/SDL.h"
#include "CellAutomat.h"


unsigned char fileHeader[14] = {'B','M',0,0,0,0,0,0,0,0,54,0,0,0};
unsigned char bmpinfoheader[40] = { 0x28,0,0,0, 141, 0,0,0, 70,0,0,0, 1,0, 24,0,0,0,0,0, 0x8c,0x05,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char white[3] = {255,255,255};
unsigned char black[3] = {0,0,0};
unsigned char pad = 0;





unsigned char defSize(Map * map){
    return (unsigned char)(54 + map->height * map->width);
}


void genBmp(Map * map, const char * name){
    FILE * bmp = fopen(name, "wb");
    unsigned filesize = defSize(map);
    fileHeader[2] = filesize;
    fileHeader[3] = filesize >> 8;
    fileHeader[4] = filesize >> 16;
    fileHeader[5] = filesize >> 24;

    fwrite(&fileHeader, 1, 14, bmp);
    fwrite(&bmpinfoheader, 1, 40, bmp);
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            if (map->grid[i][j]) {
                fwrite(&black, 1, 3, bmp);
//                fwrite(&black, 1, 3, bmp);
            }
            else {
                fwrite(&white, 1, 3, bmp);
//                fwrite(&white, 1, 3, bmp);
            }
        }
        fwrite(&pad, 1, 1, bmp);
    }
    fclose(bmp);
}


SDL_Texture* LoadImage(const char * file, SDL_Renderer * renderer){
    SDL_Surface *loadedImage = nullptr;
    SDL_Texture *texture = nullptr;
    loadedImage = SDL_LoadBMP(file);
    if (loadedImage != nullptr){
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    else
        std::cout << SDL_GetError() << std::endl;
    return texture;
}


void createWindow() {
    SDL_Window *win = SDL_CreateWindow("AutomataDungeone", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr) std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;

    SDL_RenderClear(ren);

    SDL_Texture * tex = LoadImage("/home/max/Dunge.bmp" , ren);

    SDL_RenderCopy(ren, tex, nullptr, nullptr);
    SDL_RenderPresent(ren);

    SDL_Delay(10000);

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
#endif //AUTOMATADUNGEONE_GRAPHICALENGINE_H
