#ifndef AUTOMATADUNGEONE_IMAGEPROCESSOR_H
#define AUTOMATADUNGEONE_IMAGEPROCESSOR_H

#include "CellAutomat.h"
#include "gd.h"


using std::cerr;
using std::cout;


static int stounPalette[9][3] = {
        {222, 184, 135},
        {156, 82, 17},
        {144, 72, 10},
        {102, 51, 0},
        {204, 102, 0},
        {173, 156, 0},
        {127, 73, 26},
        {107, 54, 8},
        {112, 78, 17}
};


static int forestPalette[9][3] = {
        {20, 73, 26},
        {10, 51, 0},
        {76, 153, 0},
        {51, 102, 0},
        {0, 102, 51},
        {0, 153, 0},
        {0, 150, 0},
        {28, 150, 58}
};


static int oceanPalette[9][3]{
        {102, 178, 255},
        {0, 100, 200},
        {51, 153, 255},
        {51, 51, 255},
        {0, 128, 255},
        {0, 102, 204},
        {0, 76, 153},
        {0, 51, 102}
};


static int cavePalette[9][3]{
        {40, 40, 40},
        {35, 35, 35},
        {30, 30, 30},
        {25, 25, 25},
        {20, 20, 20},
        {15, 15, 15},
        {10, 10, 10},
        {5, 5, 5},
        {0, 0, 0},
};



class Png{
public:
    Png(Patern * map, char const * path, unsigned scale, const int (&clr)[9][3], const int (&bckgr)[9][3]);
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
    int backgroundClr[8] = {0};
};


Png :: Png(Patern * map, char const * path, unsigned scale, const int (&clr)[9][3], const int (&bckgr)[9][3]){
    this->path = path;
    this->grid = map->grid;
    this->width = map->width;
    this->height = map->height;
    this->scale = scale;
    this->image = gdImageCreate(this->scale * this->height, this->scale * this->width);
    if(this->image == nullptr) {
        cerr << "unable to open image";
        _exit(0);
    }
    for(unsigned i = 0; i < 9; i++){
        this->Paint[i] = gdImageColorAllocate(this->image, clr[i][0], clr[i][1], clr[i][2]);
        this->backgroundClr[i] = gdImageColorAllocate(this->image, bckgr[i][0], bckgr[i][1], bckgr[i][2]);
    }
}


void Png :: genPng(){
   unsigned iscale = 0, jscale = 0;
   for(unsigned i =0; i < this->height; i ++){
        for(unsigned j = 0; j < this->width; j ++){
            iscale = i*this->scale;
            jscale = j*this->scale;
            if(this->grid[i][j] > 0) gdImageRectangle(this->image, iscale, jscale, iscale+this->scale, jscale+this->scale, this->Paint[this->grid[i][j]]);
            else gdImageRectangle(this->image, i, j, iscale, jscale, this->backgroundClr[-(this->grid[i][j]+1)]);
        }
    }
   this->pngOut = fopen(this->path, "wb");
   if(this->pngOut == nullptr) cerr << "Unable to write image";
   gdImagePng(this->image, this->pngOut);
   fclose(this->pngOut);
   gdImageDestroy(this->image);
}


#endif //AUTOMATADUNGEONE_IMAGEPROCESSOR_H
