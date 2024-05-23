#ifndef ROBOT_H
#define ROBOT_H

#include "grid.h"
#include "target.h"

typedef struct {
    int x;
    int y;
    char symbol;
} Robot;

void place_robots(Grid *grid, Robot *robots, int num_robots);
void move_robot(Grid *grid, Robot *robot, char direction,Target *targets[]);

#endif // ROBOT_H