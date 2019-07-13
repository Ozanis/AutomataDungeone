#ifndef AUTOMATADUNGEONE_CELLAUTOMAT_H
#define AUTOMATADUNGEONE_CELLAUTOMAT_H

#include "unistd.h"
#include "random"
#include "iostream"


using std::cout;
using std::endl;
using std::random_device;
using std::uniform_real_distribution;


typedef struct {
    int ** grid;
    size_t width;
    size_t height;
}Patern;

int ** init(unsigned height, unsigned width){
    int ** newMap = new int*[height*sizeof(int)];
    for(unsigned i = 0; i < height; i++){
        newMap[i] = new int[width]{0};
    }
    return newMap;
}


class CellAutomat{
public:
    CellAutomat(float chance, int deathLimit, int birthLimit, unsigned h, unsigned w);
    ~CellAutomat();
    void update(unsigned steps);
    Patern * synthesis();
    int ** grid = nullptr;
    unsigned height;
    unsigned width;

private:
    int countAliveNeighbours(unsigned x, unsigned y);
    int ** runSimulation();
    float stayAliveChance;
    int deathLimit;
    int birthLimit;
};


CellAutomat :: CellAutomat(float chance, int death, int birth, unsigned h, unsigned w){
    this->stayAliveChance = chance;
    this->deathLimit = death;
    this->birthLimit = birth;
    this->height = h;
    this->width = w;
    this->grid = init(h, w);
    random_device generator;
    uniform_real_distribution<float> distribution(0, 1);
    for(unsigned i = 1; i < this->height; i++ ){
        for(unsigned j = 1; j < this->width; j++ ){
            this->grid[i][j] = distribution(generator) < this->stayAliveChance;
        }
    }
}


CellAutomat :: ~CellAutomat(){
    delete(grid);
}


int CellAutomat :: countAliveNeighbours(unsigned x, unsigned y){
    int count = 0;
    for(int i=-1; i<2; i++){
        for(int j=-1; j<2; j++){
            int neighbour_i = x+i;
            int neighbour_j = y+j;
              if(neighbour_i < 0 || neighbour_j < 0 || neighbour_i >= this->height || neighbour_i >= this->width) ++count;
              else if(this->grid[neighbour_i][neighbour_j]) ++count;

        }
    }
    return count;
}


int ** CellAutomat :: runSimulation() {
    int ** newMap = init(this->height, this->width);
    for (int i = 1; i < this->height-1; i++) {
        for (int j = 1; j < this->width-1; j++) {
            int nbs = this->countAliveNeighbours(i, j);
            if (this->grid[i][j] > 0) {
                if(nbs >= deathLimit) newMap[i][j] = 1-nbs;
                else newMap[i][j] = nbs;
            }
            else {
                if(nbs > birthLimit) newMap[i][j] = 1-nbs;
            }
        }
    }
    return newMap;
}


void CellAutomat :: update(unsigned steps){
   for(unsigned i = 0; i < steps; i++){
       this->grid = runSimulation();
   }
}


Patern * CellAutomat :: synthesis(){
    auto * map = new Patern[sizeof(Patern)];
    map->grid = this->grid;
    map->height = this->height;
    map->width = this->width;
    return map;
}

#endif //AUTOMATADUNGEONE_CELLAUTOMAT_H
