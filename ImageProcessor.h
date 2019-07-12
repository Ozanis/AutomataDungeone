#ifndef AUTOMATADUNGEONE_IMAGEPROCESSOR_H
#define AUTOMATADUNGEONE_IMAGEPROCESSOR_H

#include "CellAutomat.h"
#include "gd.h"


using std::cerr;
using std::cout;


int brownPalette[8][3] = {
        {222, 184, 135},
        {156, 82, 17},
        {144, 72, 10},
        {102, 51, 0},
        {204, 102, 0},
        {173, 156, 0},
        {127, 73, 26},
        {107, 54, 8}
};


int greenPalette[8][3] = {
        {0, 204, 0},
        {76, 153, 0},
        {51, 102, 0},
        {0, 102, 51},
        {0, 153, 0},
        {102, 51, 0},
        {127, 73, 26},
        {28, 208, 58}
};


int bluePalette[8][3]{
        {102, 178, 255},
        {51, 153, 255},
        {0, 128, 255},
        {0, 102, 204},
        {0, 76, 153},
        {0, 51, 102},
        {51, 51, 255},
        {0, 255, 255}
};


class Png{
public:
    Png(Patern * map, char const * path, unsigned scale, const int (&clr)[8][3]);
    ~Png()= default;
    void genPng();

    char const * path = nullptr;
    int ** grid;
    unsigned height = 0;
    unsigned width = 0;
    unsigned scale = 1;
    FILE * pngOut = nullptr;
    gdImagePtr image = nullptr;
    int Paint[8] = {0};
    int backgroundClr = 0;
};


Png :: Png(Patern * map, char const * path, unsigned scale, const int (&clr)[8][3]){
    this->path = path;
    this->grid = map->grid;
    this->width = map->width;
    this->height = map->height;
    this->scale = scale;
    this->image = gdImageCreate(this->scale * this->height, this->scale * this->width);
    this->backgroundClr = gdImageColorAllocate(this->image, 0, 0, 0);
    for(unsigned i = 0; i < 8; i++){
        this->Paint[i] = gdImageColorAllocate(this->image, clr[i][0], clr[i][1], clr[i][2]);
    }
}


void Png :: genPng(){
   if(this->image == nullptr) {
       cerr << "unable to open image";
       _exit(0);
   }
   unsigned iscale = 0, jscale = 0;
   for(unsigned i =0; i < this->height; i ++){
        for(unsigned j = 0; j < this->width; j ++){
            iscale = i*this->scale;
            jscale = j*this->scale;
            if(this->grid[i][j]) gdImageRectangle(this->image, iscale, jscale, iscale+this->scale, jscale+this->scale, this->Paint[this->grid[i][j]-1]);
            else gdImageRectangle(this->image, i, j, iscale, jscale,  this->backgroundClr+2);
        }
    }
    this->pngOut = fopen(this->path, "wb");
    gdImagePng(this->image, this->pngOut);
    fclose(this->pngOut);
    gdImageDestroy(this->image);
}


/*
class Png{
public:
    Png(Patern * map, char const * path);
    ~Png() = default;
    void genPng(unsigned scale);

    char const * path = nullptr;
    Patern * raw = nullptr;
    FILE * pngOut = nullptr;
};


Png :: Png(Patern * map, char const * path){
    this->raw = map;
    this->path = path;
    cout << raw->width << endl << raw->height << endl;
}


void Png :: genPng(unsigned scale){
   gdImagePtr image = gdImageCreate(scale * this->raw->height, scale * this->raw->width);
   if(image == nullptr) {
       cerr << "unable to open image";
       _exit(0);
   }
   int black = gdImageColorAllocate(image, 0, 0, 0);
   int brown = gdImageColorAllocate(image, 222, 184, 135);
   for(unsigned i =0; i < this->raw->height; i ++){
        for(unsigned j = 0; j < this->raw->width; j ++){
                if(this->raw->grid[i][j]) gdImageRectangle(image, i*scale, j*scale, i*scale+scale, j*scale+scale, black);
                else gdImageRectangle(image, i, j, i*scale, j*scale, brown);
        }
    }
    this->pngOut = fopen(this->path, "wb");
    gdImagePng(image, this->pngOut);
    fclose(this->pngOut);
    gdImageDestroy(image);
}
*/

#endif //AUTOMATADUNGEONE_IMAGEPROCESSOR_H
