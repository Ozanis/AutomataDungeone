#ifndef AUTOMATADUNGEONE_IMAGEPROCESSOR_H
#define AUTOMATADUNGEONE_IMAGEPROCESSOR_H

#include "CellAutomat.h"
#include "gd.h"


using std::cerr;
using std::cout;


static int brownPalette[8][3] = {
        {22, 184, 135},
        {156, 82, 17},
        {144, 72, 10},
        {102, 51, 0},
        {204, 102, 0},
        {173, 156, 0},
        {127, 73, 26},
        {107, 54, 8}
};


static int greenPalette[8][3] = {
        {0, 204, 0},
        {76, 153, 0},
        {51, 102, 0},
        {0, 102, 51},
        {0, 153, 0},
        {102, 51, 0},
        {127, 73, 26},
        {28, 208, 58}
};


static int bluePalette[8][3]{
        {102, 178, 255},
        {51, 153, 255},
        {0, 128, 255},
        {0, 102, 204},
        {0, 76, 153},
        {0, 51, 102},
        {51, 51, 255},
        {0, 255, 255}
};


class ColorPallete{
public:
    template <typename P, unsigned pos, unsigned RGB>
    ColorPallete(gdImagePtr image, P (&clr)[pos][RGB]);
    ~ColorPallete() = default;
    int color[8] = {0};
};

template <typename P, unsigned pos, unsigned RGB>
ColorPallete :: ColorPallete(gdImagePtr image, P (&clr)[pos][RGB]) {
    for(unsigned i = 0; i < 8; i++){
        color[i] = gdImageColorAllocate(image, );
    }
}





class Png{
public:
    Png(Patern * map, char const * path);
    ~Png() = default;
    void genPng(unsigned scale);
    friend int CellAutomat :: countAliveNeighbours(unsigned x, unsigned y);

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
                else gdImageRectangle(image, i, j, i*scale, j*scale, brown[countAliveNeighbours(i, j)]);
        }
    }
    this->pngOut = fopen(this->path, "wb");
    gdImagePng(image, this->pngOut);
    fclose(this->pngOut);
    gdImageDestroy(image);
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
