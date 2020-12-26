/* Your code here! */
#include "maze.h"
#include <iostream>
#include <algorithm>
using namespace std;
using namespace cs225;

int SquareMaze::get_x(int index) const { 
  return index % width;
}

int SquareMaze::get_y(int index) const { 
  return index / width;
}

int SquareMaze::get_idx(int x, int y) const { 
  return y * width + x;
}

SquareMaze::SquareMaze() {
  width = 0;
  height = 0;
}

void SquareMaze::makeMaze(int width, int height) {
  this->width = width;
  this->height = height;
  squares.resize(width*height, BOTH_WALLS);
  sets.addelements(width*height);

  while(sets.size(0) != width * height) { 
    int rsquare = rand() % (width*height); 
    int rwall = rand() % 2; 
    if(rwall == 0) {
      if((rsquare+1)%width == 0 || sets.find(rsquare) == sets.find(rsquare+1)) {
        continue;
      } else {
        setWall(get_x(rsquare), get_y(rsquare), 0, false); 
        sets.setunion(rsquare, rsquare+1); 
      }
    } else { 
      if (rsquare+width >= width*height || sets.find(rsquare) == sets.find(rsquare+width)) {
        continue;
      } else { 
        setWall(get_x(rsquare), get_y(rsquare), 1, false); 
        sets.setunion(rsquare, rsquare+width); 
      }
    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
  
  if (width == 0 || height == 0) {
    return false;
  }

  if (dir == RIGHT) { 
    if (x < width-1 && squares.at(get_idx(x, y)) != RIGHT_WALL && squares.at(get_idx(x, y)) != BOTH_WALLS) {
      return true;
    }
  }
  if (dir == DOWN) { 
    if (y < height-1 && squares.at(get_idx(x, y)) != DOWN_WALL && squares.at(get_idx(x, y)) != BOTH_WALLS) {
      return true;
    }
  }
  if (dir == LEFT) { 
    if (x != 0 && squares.at(get_idx(x - 1, y)) != RIGHT_WALL && squares.at(get_idx(x - 1, y)) != BOTH_WALLS) {
      return true;
    }
  }
  if (dir == UP) { 
    if (y != 0 && squares.at(get_idx(x, y - 1)) != DOWN_WALL && squares.at(get_idx(x, y - 1)) != BOTH_WALLS) {
      return true;
    }
  }

  return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  int wall = squares.at(get_idx(x, y));
  if(dir == RIGHT && exists){ 
    if (wall == CLEAR) {
      squares.at(get_idx(x, y)) = RIGHT_WALL;
    } else if (wall == DOWN_WALL) {
      squares.at(get_idx(x, y)) = BOTH_WALLS;
    }
  }
  else if(dir == DOWN && exists){ 
    if (wall == CLEAR) {
      squares.at(get_idx(x, y)) = DOWN_WALL;
    } else if (wall == RIGHT_WALL) {
      squares.at(get_idx(x, y)) = BOTH_WALLS;
    }
  } else if (dir == RIGHT && !exists) { 
    if (wall == RIGHT_WALL) {
      squares.at(get_idx(x, y)) = CLEAR;
    } else if (wall == BOTH_WALLS) {
      squares.at(get_idx(x, y)) = DOWN_WALL;
    }
  } else if (dir == DOWN && !exists) { 
    if (wall == DOWN_WALL) {
      squares.at(get_idx(x, y)) = CLEAR;
    } else if (wall == BOTH_WALLS) {
      squares.at(get_idx(x, y)) = RIGHT_WALL;
    }
  }
}

PNG * SquareMaze::drawMaze() const {
  PNG* result = new PNG(width * 10 + 1, height * 10 + 1);
  for (int i = 0; i < width * 10 + 1; i++) { 
    if (i < 1 || i > 9) {
      HSLAPixel & pixel = result->getPixel(i, 0);
      pixel.l = 0;
    }
  }
  for (int i = 0; i < height * 10 + 1; i++) { 
    HSLAPixel & pixel = result->getPixel(0, i);
    pixel.l = 0;
  }
  for (int x = 0; x < width; x++) { 
    for (int y = 0; y < height; y++) {
      if (squares.at(get_idx(x, y)) == RIGHT_WALL || squares.at(get_idx(x, y)) == BOTH_WALLS) {
        for (int k = 0; k <= 10; k++) {
          HSLAPixel & pixel = result->getPixel((x+1)*10, y*10+k);
          pixel.l = 0;
        }
      }
      if (squares.at(get_idx(x, y)) == DOWN_WALL || squares.at(get_idx(x, y)) == BOTH_WALLS) {
        for (int k = 0; k <= 10; k++) {
          HSLAPixel & pixel = result->getPixel(x*10+k, (y+1)*10);
          pixel.l = 0;
        }
      }
    }
  }
  return result;
}

vector<int> SquareMaze::solveMaze() {
  vector<int> length(width * height, -1); 
  vector<int> path(width * height, -1);
  vector<int> previous(width * height, -1);
  queue<int> backtrack; 
  backtrack.push(0);

  while (!backtrack.empty()) { 
    int index = backtrack.front();
    int x = get_x(index);
    int y = get_y(index);
    if (canTravel(x, y, RIGHT) && length[index + 1] < 0) {
      length[index + 1] = length[index] + 1; 
      path[index + 1] = 0;
      previous[index + 1] = index;
      backtrack.push(index + 1);
    }
    if (canTravel(x, y, DOWN) && length[index + width] < 0) {
      length[index + width] = length[index] + 1;
      path[index + width] = 1;
      previous[index + width] = index;
      backtrack.push(index + width);
    }
    if (canTravel(x, y, LEFT) && length[index - 1] < 0) {
      length[index - 1] = length[index] + 1;
      path[index - 1] = 2;
      previous[index - 1] = index;
      backtrack.push(index - 1);
    }
    if (canTravel(x, y, UP) && length[index - width] < 0) {
      length[index - width] = length[index] + 1;
      path[index - width] = 3;
      previous[index - width] = index;
      backtrack.push(index - width);
    }
    backtrack.pop();
  }

  int longest_path_idx = -1;
  int distance = -1;

  for (int i = get_idx(0, height - 1); i < width * height; i++) {
    if (length[i] > distance) {
      longest_path_idx = i;
      distance = length[i];
    }
  }

  vector<int> result;
  while (longest_path_idx > 0) { 
    result.push_back(path[longest_path_idx]);
    longest_path_idx = previous[longest_path_idx];
  }

  std::reverse(result.begin(), result.end());

  return result;
}



PNG * SquareMaze::drawMazeWithSolution() {
  PNG* result = drawMaze();
  vector<int> solution = solveMaze();

  int x = 5;
  int y = 5;

  for (size_t i = 0; i < solution.size(); i++) {
    for (int j = 0; j < 10; j++) {
      HSLAPixel & pixel = result->getPixel(x, y);
      pixel.h = 0;
      pixel.s = 1;
      pixel.l = 0.5;
      pixel.a = 1;
      if (solution[i] == RIGHT) {x++;}
      if (solution[i] == DOWN) {y++;}
      if (solution[i] == LEFT) {x--;}
      if (solution[i] == UP) {y--;}
    }
  }

  HSLAPixel & pixel = result->getPixel(x, y);
  pixel.h = 0;
  pixel.s = 1;
  pixel.l = 0.5;
  pixel.a = 1;

  x -= 4;
  y += 5;
  for (int i = 0; i < 9; i++) {
    HSLAPixel & pixel = result->getPixel(x + i, y);
    pixel.l = 1;
  }

  return result;
}

PNG * SquareMaze::drawCreativeMaze() {
  PNG base;
  base.readFromFile("base.png");
  assert(width <= (int)(base.width() / 10) && height <= (int)(base.height() / 10));
  PNG* result = new PNG(width * 10 + 1, height * 10 + 1);
  for (int i = 0; i < width * 10 + 1; i++) { 
    if (i < 1 || i > 9) {
      HSLAPixel & base_pixel = base.getPixel(i, 0);
      HSLAPixel & new_pixel = result->getPixel(i, 0);
      new_pixel = base_pixel;
    }
  }
  for (int i = 0; i < height * 10 + 1; i++) { 
    HSLAPixel & base_pixel = base.getPixel(0, i);
    HSLAPixel & new_pixel = result->getPixel(0, i);
    new_pixel = base_pixel;
  }
  for (int x = 0; x < width; x++) { 
    for (int y = 0; y < height; y++) {
      if (squares.at(get_idx(x, y)) == RIGHT_WALL || squares.at(get_idx(x, y)) == BOTH_WALLS) {
        for (int k = 0; k <= 10; k++) {
          HSLAPixel & base_pixel = base.getPixel((x+1)*10, y*10+k);
          HSLAPixel & new_pixel = result->getPixel((x+1)*10, y*10+k);
          new_pixel = base_pixel;
        }
      }

      if (squares.at(get_idx(x, y)) == DOWN_WALL || squares.at(get_idx(x, y)) == BOTH_WALLS) {
        for (int k = 0; k <= 10; k++) {
          HSLAPixel & base_pixel = base.getPixel(x*10+k, (y+1)*10);
          HSLAPixel & new_pixel = result->getPixel(x*10+k, (y+1)*10);
          new_pixel = base_pixel;
        }
      }
    }
  }

  vector<int> solution = solveMaze();

  int x = 5;
  int y = 5;

  for (size_t i = 0; i < solution.size(); i++) {
    for (int j = 0; j < 10; j++) {
      HSLAPixel & pixel = result->getPixel(x, y);
      HSLAPixel & base_pixel = base.getPixel(x, y);
      if (base_pixel.l != 1) { 
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
      }
      if (solution[i] == RIGHT) {x++;}
      if (solution[i] == DOWN) {y++;}
      if (solution[i] == LEFT) {x--;}
      if (solution[i] == UP) {y--;}
    }
  }

  return result;
}