// build_grille.h
#ifndef BUILD_GRILLE_H
#define BUILD_GRILLE_H

#include "grid.h"

void build_grid(Grid *grille);
void score_display(int *scores, int num_players);
void display_limit();
void display_round(int round);

#endif // BUILD_GRILLE_H