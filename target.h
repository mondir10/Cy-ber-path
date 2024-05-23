
#ifndef TARGET_H
#define TARGET_H

#include "grid.h"

typedef struct {
    char symbol;
    int x, y;
} Target;


void create_target(Target *target[]);
int is_valid_position(Grid *grid, int x, int y);
void placement_target(Target *targets[18], Grid *grid);

#endif // TARGET_H