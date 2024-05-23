// build_grid.c
#include "build_grid.h"
#include <stdio.h>


#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"

void build_grid(Grid *grid) {
    // Dessiner la ligne supérieure
    printf("+");
    for (int j = 0; j < grid->width; j++) {
        printf("--+");
    }
    printf("\n");

    // Dessiner chaque ligne avec des murs verticaux
    for (int i = 0; i < grid->height; i++) {
        // Ligne de contenu avec des murs verticaux
        printf("|");
        for (int j = 0; j < grid->width; j++) {
            char cell = grid->cells[i][j];

            // Imprimer le contenu de la cellule en couleur
            switch (cell) {
                case '1':
                    printf(RED " 1" RESET "|");  // Robot 1 en Rouge
                    break;
                case '2':
                    printf(GREEN " 2" RESET "|");  // Robot 2 en Vert
                    break;
                case '3':
                    printf(YELLOW " 3" RESET "|");  // Robot 3 en Jaune
                    break;
                case '4':
                    printf(BLUE " 4" RESET "|");  // Robot 4 en Bleu
                    break;
                case '#':
                    printf("##|");  // Mur
                    break;
                default:
                    // Vérifier si c'est une cible entre 'A' et 'R'
                    if (cell >= 'A' && cell <= 'R') {
                        printf(MAGENTA " %c" RESET "|", cell);  // Cible en Violet (Magenta)
                    } else {
                        printf("  |");  // Case vide
                    }
                    break;
            }
        }
        printf("\n");

        // Dessiner la ligne inférieure
        printf("+");
        for (int j = 0; j < grid->width; j++) {
            printf("--+");
        }
        printf("\n");
    }
}

void score_display(int *scores, int num_players) {
    printf("Scores:\n");
    for (int i = 0; i < num_players; i++) {
        printf("j%d = %d points\n", i + 1, scores[i]);
    }
    printf("\n");
}

void display_round(int round) {
    // Calculer le nombre d'espaces pour centrer le texte
    int width_terminal = 80; // Suppose une largeur de terminal de 80 caractères
    int width_texte = 10; // Largeur du texte "Round X"
    int padding = (width_terminal - width_texte) / 2;

    // Afficher le numéro du round en rouge et centré
    printf("\n%s", RED);
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("Round %d\n", round);
    for (int i = 0; i < width_terminal; i++) {
        printf(" ");
    }
    printf("%s\n", RESET);
}

void display_limit() {
    int width_terminal = 80; // Suppose une largeur de terminal de 80 caractères
    printf("%s", RED);
    for (int i = 0; i < width_terminal; i++) {
        printf("_");
    }
    printf("%s\n", RESET);
}