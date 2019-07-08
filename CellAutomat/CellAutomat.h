#ifndef AUTOMATADUNGEONE_CELLAUTOMAT_H
#define AUTOMATADUNGEONE_CELLAUTOMAT_H

#include "unistd.h"
#include "random"
#include "iostream"

std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0, 1);

float stayAliveChance = 0.45;
int deathLimit = 100;
int birthLimit = 100;


using std::cout;
using std::endl;

template <typename G, size_t x, size_t y>
void GenBitmap(G (&grid)[x][y]) {
    for(unsigned i = 0; i < x; i++ ){
        for(unsigned j = 0; j < y; j++ ){
            if(distribution(generator) < stayAliveChance) grid[i][j] = 1;
            cout <<  grid[i][j];
        } cout << endl;
    } cout << "Grid have done" << endl;
}


template <typename G, size_t x, size_t y>
int countAliveNeighbours(G (&grid)[x][y]){
    int count = 0;
    for(int i=-1; i<2; i++){
        for(int j=-1; j<2; j++){
            int neighbour_x = x+i;
            int neighbour_y = y+j;
            if(i == 0 && j == 0) continue;
            else if(neighbour_x < 0 || neighbour_y < 0 || neighbour_x >= x || neighbour_y >= y) ++count;
            else if(grid[neighbour_x][neighbour_y]) ++count;
        }
    }
    return count;
}


template <typename G, size_t x, size_t y>
bool ** RunSimulation(G (&grid)[x][y]) {
    bool ** newGrid = new bool*[y];
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            int nbs = countAliveNeighbours(grid);
            if (grid[i][j]) {
                if (nbs < deathLimit) {
                    newGrid[i][j] = false;
                } else {
                    newGrid[x][y] = true;
                }
            }
            else {
                newGrid[x][y] = nbs > birthLimit;
                cout << grid[i][j];
            }
        }
        cout << endl;
        return newGrid;
    }
}
#endif //AUTOMATADUNGEONE_CELLAUTOMAT_H
