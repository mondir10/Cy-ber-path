#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "build_grid.h"

void create_grid(Grid* grid){
    srand(time(NULL));
    int largeur =rand()%6 +15;
    int longueur = rand()%6 +15;
    grid->width = largeur;
    grid->height = longueur;
    grid->cells = malloc(longueur * sizeof(char*));

    for(int i = 0; i<longueur; i++){
        grid->cells[i] = malloc(largeur * sizeof(char));
        for(int j=0; j<largeur; j++){
            grid->cells[i][j]= ' ';
        }
    }
}
// Fonction pour masquer la grille
void hide_grid() {
    printf("\033[2J"); // Code ANSI pour effacer l'écran
    printf("\033[H");  // Code ANSI pour repositionner le curseur au coin supérieur gauche
    fflush(stdout);    // Assurez-vous que l'affichage est mis à jour immédiatement
}


// Fonction pour afficher la grille
void show_grid(Grid *grid) {
    build_grid(grid);
}
