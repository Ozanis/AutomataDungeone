#ifndef AUTOMATADUNGEONE_IMAGEPROCESSOR_H
#define AUTOMATADUNGEONE_IMAGEPROCESSOR_H

#include "CellAutomat.h"
#include "gd.h"


using std::cerr;
using std::cout;


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
                if(this->raw->grid[i][j]) gdImageRectangle(image, i*scale, j*scale, i*scale+scale, j*scale+scale, brown);
                else gdImageRectangle(image, i, j, i*scale, j*scale, black);
        }
    }
    this->pngOut = fopen(this->path, "wb");
    gdImagePng(image, this->pngOut);
    fclose(this->pngOut);
    gdImageDestroy(image);
}


#endif //AUTOMATADUNGEONE_IMAGEPROCESSOR_H
