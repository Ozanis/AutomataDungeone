#ifndef AUTOMATADUNGEONE_CELLAUTOMAT_H
#define AUTOMATADUNGEONE_CELLAUTOMAT_H

#include "unistd.h"
#include "random"
#include "iostream"


using std::cout;
using std::endl;
using std::default_random_engine;
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
    int ** grid = nullptr;
    unsigned height;
    unsigned width;
    int countAliveNeighbours(unsigned x, unsigned y);
    void update(unsigned steps);
    Patern * synthesis();

private:
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

    default_random_engine generator;
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
//            if(i == 0 && j == 0 && i == this->height - 1 && j == this->width) continue;
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
//                else newMap[i][j] = nbs;
            }
        } cout << endl;
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
