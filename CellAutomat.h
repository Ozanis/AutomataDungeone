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
    bool ** grid;
    size_t width;
    size_t height;
}Patern;


bool ** init(unsigned height, unsigned width){
    bool ** newMap = new bool*[height*sizeof(bool)];
    for(unsigned i = 0; i < height; i++){
        newMap[i] = new bool[width]{false};
    }
    return newMap;
}


void display(Patern * map){
    for(unsigned i = 0; i < map->height; i++){
        cout << endl;
        for(unsigned j = 0; j < map->width; j++){
            if(map->grid[i][j]) cout << " ";
            else cout << "#";
        }
    } cout << endl;
}


class CellAutomat{
public:
    CellAutomat(float chance, int deathLimit, int birthLimit, unsigned h, unsigned w);
    ~CellAutomat();
    bool ** grid = nullptr;
    unsigned height;
    unsigned width;
    void update(unsigned steps);
    Patern * synthesis();

private:
    int countAliveNeighbours(unsigned x, unsigned y);
    bool ** runSimulation();
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
            if(i == 0 && j == 0) continue;
            if(neighbour_i < 0 || neighbour_j < 0 || neighbour_i >= this->height || neighbour_i >= this->width) ++count;
            else if(this->grid[neighbour_i][neighbour_j]) ++count;
        }
    }
    return count;
}


bool ** CellAutomat :: runSimulation() {
    bool ** newMap = init(this->height, this->width);
    for (int i = 1; i < this->height-1; i++) {
        for (int j = 1; j < this->width-1; j++) {
            int nbs = countAliveNeighbours(i, j);
            if (this->grid[i][j]) {
                newMap[i][j] = nbs >= deathLimit;
            }
            else {
                newMap[i][j] = nbs > birthLimit;
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
