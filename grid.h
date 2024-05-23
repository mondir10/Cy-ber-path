// grid.h
#ifndef GRID_H
#define GRID_H

typedef struct {
    int height;
    int width;
    char **cells;
} Grid;

void create_grid(Grid *grille);
void hide_grid();
void show_grid();

#endif // GRID_H
