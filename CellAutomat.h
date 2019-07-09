#ifndef AUTOMATADUNGEONE_CELLAUTOMAT_H
#define AUTOMATADUNGEONE_CELLAUTOMAT_H

#include "unistd.h"
#include "random"
#include "iostream"


using std::cout;
using std::endl;


std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0, 1);

size_t width = 256;
size_t height = 256;

float stayAliveChance = 0.45;
int deathLimit = 3;
int birthLimit = 6;


typedef struct{
    bool ** grid;
    unsigned height;
    unsigned width;
}Map;


void display(Map * map){
    for(unsigned i = 0; i < map->height; i++){
        cout << endl;
        for(unsigned j = 0; j < map->width; j++){
            if(map->grid[i][j]) cout << " ";
            else cout << "#";
        }
    } cout << endl;
}


Map * init(unsigned height, unsigned width){
    Map * newMap = new Map[sizeof(Map)];
    newMap->height = height;
    newMap->width = width;
    newMap->grid = new bool*[height];
    for(unsigned i = 0; i < height; i++){
        newMap->grid[i] = new bool[width]{false};
    }
    return newMap;
}


void GenBitmap(Map * map) {
    for(unsigned i = 0; i < map->height; i++ ){
        for(unsigned j = 0; j < map->width; j++ ){
            map->grid[i][j] = distribution(generator) < stayAliveChance;
        }
    }
}


int countAliveNeighbours(Map * map, unsigned x, unsigned y){
    int count = 0;
    for(int i=-1; i<2; i++){
        for(int j=-1; j<2; j++){
            int neighbour_i = x+i;
            int neighbour_j = y+j;
            if(i == 0 && j == 0) continue;
            else if(neighbour_i < 0 || neighbour_j < 0 || neighbour_i >= map->height || neighbour_i >= map->width) ++count;
            else if(map->grid[neighbour_i][neighbour_j]) ++count;
        }
    }
    return count;
}


Map * RunSimulation(Map * map) {
    Map * newMap = init(map->height, map->width);
    for (int i = 0; i < map->height-1; i++) {
        for (int j = 0; j < map->width-1; j++) {
            int nbs = countAliveNeighbours(map, i, j);
            if (map->grid[i][j]) {
                newMap->grid[i][j] = nbs >= deathLimit;
            }
            else {
                newMap->grid[i][j] = nbs > birthLimit;
            }
        } cout << endl;
    }
    return newMap;
}


Map * initialiseMap(Map * map){
    Map * newMap = init(map->height, map->height);
   for(unsigned i = 0; i < map->height; i++){
        for(int j = 0; j < map->width; j++){
             newMap->grid[i][j] = (distribution(generator) < stayAliveChance);
        }
    }
    return newMap;
}


Map * generateMap(){
   Map * Automat = init(height, width);
   GenBitmap(Automat);
//   display(Automat);
   Automat = initialiseMap(Automat);
//   display(Automat);
   for(unsigned i = 0; i < 10; i++){
       Automat = RunSimulation(Automat);
//       display(Automat);
   }
    return Automat;
}


#endif //AUTOMATADUNGEONE_CELLAUTOMAT_H
