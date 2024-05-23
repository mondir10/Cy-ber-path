#include "wall.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>





// Placer deux murs autour d'une cible formant un angle droit
void place_walls_around_target(Grid *grid, int x, int y) {
    int orientation = rand() % 4;

    switch (orientation) {
        case 0: // Mur à droite et en bas
            if (x < grid->width - 1) grid->cells[y][x + 1] = '#';
            if (y < grid->height - 1) grid->cells[y + 1][x] = '#';
            if (x < grid->width - 1 && y < grid->height - 1) grid->cells[y + 1][x + 1] = '#'; // Angle droit
            break;
        case 1: // Mur à gauche et en bas
            if (x > 0) grid->cells[y][x - 1] = '#';
            if (y < grid->height - 1) grid->cells[y + 1][x] = '#';
            if (x > 0 && y < grid->height - 1) grid->cells[y + 1][x - 1] = '#'; // Angle droit
            break;
        case 2: // Mur à gauche et en haut
            if (x > 0) grid->cells[y][x - 1] = '#';
            if (y > 0) grid->cells[y - 1][x] = '#';
            if (x > 0 && y > 0) grid->cells[y - 1][x - 1] = '#'; // Angle droit
            break;
        case 3: // Mur à droite et en haut
            if (x < grid->width - 1) grid->cells[y][x + 1] = '#';
            if (y > 0) grid->cells[y - 1][x] = '#';
            if (x < grid->width - 1 && y > 0) grid->cells[y - 1][x + 1] = '#'; // Angle droit
            break;
    }
}

// murs sur la bordure
void place_random_walls(Grid *grid) {
    int positions[grid->width];
    for (int i = 0; i < grid->width; i++) {
        positions[i] = 0;
    }

    for (int i = 0; i < 2; i++) {
        // Murs sur la bordure supérieure
        int x_top;
        do {
            x_top = rand() % (grid->width - 4) + 2;
        } while (positions[x_top] || positions[x_top - 1] || positions[x_top + 1]);
        grid->cells[0][x_top] = '#';
        positions[x_top] = 1;

        // Murs sur la bordure inférieure
        int x_bottom;
        do {
            x_bottom = rand() % (grid->width - 4) + 2;
        } while (positions[x_bottom] || positions[x_bottom - 1] || positions[x_bottom + 1]);
        grid->cells[grid->height - 1][x_bottom] = '#';
        positions[x_bottom] = 1;
    }

    int pos_y[grid->height];
    for (int i = 0; i < grid->height; i++) {
        pos_y[i] = 0;
    }

    for (int i = 0; i < 2; i++) {
        // Murs sur la bordure gauche
        int y_left;
        do {
            y_left = rand() % (grid->height - 4) + 2;
        } while (pos_y[y_left] || pos_y[y_left - 1] || pos_y[y_left + 1]);
        grid->cells[y_left][0] = '#';
        pos_y[y_left] = 1;

        // Murs sur la bordure droite
        int y_right;
        do {
            y_right = rand() % (grid->height - 4) + 2;
        } while (pos_y[y_right] || pos_y[y_right - 1] || pos_y[y_right + 1]);
        grid->cells[y_right][grid->width - 1] = '#';
        pos_y[y_right] = 1;
    }
}


