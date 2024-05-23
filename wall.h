
#ifndef WALL_H
#define WALL_H

#include "grid.h"

void place_random_walls(Grid *grid);
void place_walls_around_target(Grid *grid, int x, int y);

#endif // WALL_H