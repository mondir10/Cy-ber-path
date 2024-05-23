#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "target.h"
#include "wall.h"

void create_target(Target* target[18]){
    for(int i =0 ; i<18;i++){
        target[i]= malloc(sizeof(Target));
        if(target[i] == NULL){
            fprintf(stderr, "Erreur d'allocation mémoire pour la cible %d\n", i);
            exit(EXIT_FAILURE);
        }
        else{
            target[i]->symbol = 'A'+ i;
        }
    }
}

int is_valid_position(Grid *grid, int x, int y) {
    if (x < 2 || x >= grid->width - 2 || y < 2 || y >= grid->height - 2) {
        return 0; // Éviter les bordures extérieures
    }

    // Vérifier si les cases environnantes sont libres (orthogonalement et en diagonale)
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (grid->cells[y + dy][x + dx] != ' ') {
                return 0; // Case occupée à proximité
            }
        }
    }

    return 1; // La position est valide
}

// Placer les cibles dans la grille
void placement_target(Target *target[18], Grid *grid) {
    srand(time(NULL));
    for (int i = 0; i < 18; i++) {
        int x, y;
        int placed = 0;
        while (!placed) {
            x = rand() % (grid->width - 2) + 1; // Éviter les bordures extérieures
            y = rand() % (grid->height - 2) + 1;

            if (is_valid_position(grid, x, y)) {
                // Placer la cible
                grid->cells[y][x] = target[i]->symbol;
                target[i]->x = x;
                target[i]->y = y;

                // Placer les murs autour de la cible
                place_walls_around_target(grid, x, y);

                placed = 1;
            }
        }
    }
}