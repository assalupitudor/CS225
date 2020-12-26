/* Your code here! */
#pragma once
#include <vector>
#include "cs225/PNG.h"
#include "dsets.h" 
#include <stdlib.h>
#include <queue>
#include <assert.h>

enum { RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3 };
enum { CLEAR = 0, RIGHT_WALL = 1, DOWN_WALL = 2, BOTH_WALLS = 3 };

class SquareMaze {

  public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    std::vector<int> solveMaze();
    cs225::PNG *drawMaze() const;
    cs225::PNG *drawMazeWithSolution();
    cs225::PNG *drawCreativeMaze();

  private:
    DisjointSets sets; 
    std::vector<int> squares; // index is the square, value is walls
    int width;
    int height;
    int get_x(int index) const;
    int get_y(int index) const;
    int get_idx(int x, int y) const;
};