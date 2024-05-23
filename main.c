#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "target.h"
#include "wall.h"
#include "build_grid.h"
#include "robot.h"
#include <unistd.h>

#define NUM_ROBOTS 4
#define NUM_TARGETS 18
#define SECONDS_TO_WAIT 30
#define NUM_ROUNDS 5

int main() {
    srand(time(NULL));
    // Demander le nombre de joueurs
    int num_players;
    printf("Combien de joueurs êtes-vous ? ");
    scanf("%d", &num_players);

    if (num_players <= 0) {
        printf("Le nombre de joueurs doit être supérieur à 0.\n");
        return 1;
    }

    // Initialiser les scores
    int *scores = malloc(num_players * sizeof(int));
    for (int i = 0; i < num_players; i++) {
        scores[i] = 0;
    }

    for (int round = 0; round < NUM_ROUNDS; round++) {
        // Afficher le numéro du round
        display_round(round + 1);

        // Créer la grille avec des dimensions aléatoires
        Grid *grid = malloc(sizeof(Grid));
        create_grid(grid);

        // Initialiser les cibles
        Target *targets[NUM_TARGETS];
        create_target(targets);

        // Placer les cibles avec les murs
        placement_target(targets, grid);
        place_random_walls(grid);
        // Initialiser et placer les robots
        Robot robots[NUM_ROBOTS] = {{.symbol = '1'}, {.symbol = '2'}, {.symbol = '3'}, {.symbol = '4'}};
        place_robots(grid, robots, NUM_ROBOTS);

        // Afficher la grille
        score_display(scores, num_players);
        build_grid(grid);

        // Sélectionner un robot et une cible aléatoires
        int selected_robot = rand() % NUM_ROBOTS;
        int selected_target = rand() % NUM_TARGETS;

        // Afficher les sélections
        printf("Robot sélectionné : %c\n", robots[selected_robot].symbol);
        printf("Cible sélectionnée : %c\n", targets[selected_target]->symbol);

        // Chronométrer pour laisser les joueurs réfléchir
        printf("Vous avez %d secondes pour estimer le nombre de mouvements...\n", SECONDS_TO_WAIT);
        sleep(SECONDS_TO_WAIT); // Utilisez `sleep` ou toute autre méthode de temporisation

        // Masquer la grille après les 45 secondes
        hide_grid();

        // Demander les estimations de chaque joueur
        int player_moves[num_players];
        for (int i = 0; i < num_players; i++) {
            printf("Joueur %d, combien de mouvements pour atteindre la cible %c ? ", i + 1, targets[selected_target]->symbol);
            scanf("%d", &player_moves[i]);
        }

        // Afficher la grille après les réponses des joueurs
        show_grid(grid);

        // Trouver le joueur avec l'estimation la plus basse
        int min_moves = player_moves[0];
        int min_player = 0;
        for (int i = 1; i < num_players; i++) {
            if (player_moves[i] < min_moves) {
                min_moves = player_moves[i];
                min_player = i;
            }
        }

        printf("Joueur %d doit déplacer le robot %c en %d mouvements pour atteindre la cible %c.\n",
               min_player + 1, robots[selected_robot].symbol, min_moves, targets[selected_target]->symbol);

        // Le joueur essaie de déplacer le robot en saisissant les commandes (N/S/E/O)
        char direction;
        int moves_made = 0;
        while (moves_made < min_moves) {
            printf("Direction (N/S/E/O) : ");
            scanf(" %c", &direction);
            move_robot(grid, &robots[selected_robot], direction, targets);
            moves_made++;

            score_display(scores, num_players);
            build_grid(grid);

            // Vérifier si la cible est atteinte
            if (robots[selected_robot].x == targets[selected_target]->x && robots[selected_robot].y == targets[selected_target]->y) {
                printf("Cible %c atteinte par le robot %c !\n", targets[selected_target]->symbol, robots[selected_robot].symbol);
                if (moves_made == min_moves) {
                    scores[min_player] += 2;
                } else {
                    scores[min_player] -= 1;
                }
                break;
            }
        }

        // Si le joueur a échoué, les autres marquent 1 point chacun
        if (moves_made >= min_moves && (robots[selected_robot].x != targets[selected_target]->x || robots[selected_robot].y != targets[selected_target]->y)) {
            printf("Le robot n'a pas atteint la cible %c.\n", targets[selected_target]->symbol);
            for (int i = 0; i < num_players; i++) {
                if (i != min_player) {
                    scores[i]++;
                }
            }
        }

        // Libérer la mémoire
        for (int i = 0; i < NUM_TARGETS; i++) {
            free(targets[i]);
        }

        for (int i = 0; i < grid->height; i++) {
            free(grid->cells[i]);
        }
        free(grid);

        // Afficher le séparateur
        display_limit();
    }

    // Afficher les scores finaux
    int max_score = scores[0];
    int winner = 0;
    int tie = 0;
    for (int i = 1; i < num_players; i++) {
        if (scores[i] > max_score) {
            max_score = scores[i];
            winner = i;
            tie = 0;
        } else if (scores[i] == max_score) {
            tie = 1;
        }
    }

    for (int i = 0; i < num_players; i++) {
        printf("Joueur %d : %d points\n", i + 1, scores[i]);
    }

    if (tie) {
        printf("Il y a une égalité entre plusieurs joueurs avec %d points !\n", max_score);
    } else {
        printf("Le gagnant est le joueur %d avec %d points !\n", winner + 1, max_score);
    }

    // Libérer la mémoire
    free(scores);

    return 0;
}