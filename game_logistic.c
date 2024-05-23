#include "game_logistic.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

int select_random_robot(Robot *robots, int num_robots) {
    return rand() % num_robots;
}

int select_random_target(Target *target, int num_cibles) {
    return rand() % num_cibles;
}


void play_round(Grid *grid, Robot *robots, int num_robots, Target *targets, int num_targets, int *scores, int num_players) {
    srand(time(NULL));

    // Sélection aléatoire d'un robot et d'une cible
    int selected_robot = select_random_robot(robots, num_robots);
    int selected_target = select_random_target(targets, num_targets);

    Robot *robot = &robots[selected_robot];
    Target *target = &targets[selected_target];

    // Estimation des mouvements par les joueurs
    int player_moves[num_players];
    for (int i = 0; i < num_players; i++) {
        printf("Joueur %d, combien de mouvements pour atteindre la cible %c ? ", i + 1, target->symbol);
        scanf("%d", &player_moves[i]);
    }

    // Trouver le joueur avec la plus petite estimation
    int min_moves = player_moves[0];
    int min_player = 0;
    for (int i = 1; i < num_players; i++) {
        if (player_moves[i] < min_moves) {
            min_moves = player_moves[i];
            min_player = i;
        }
    }

    printf("Joueur %d doit déplacer le robot %c en %d mouvements pour atteindre la cible %c.\n",
           min_player + 1, robot->symbol, min_moves, target->symbol);

    // Effectuer les mouvements
    char direction;
    for (int i = 0; i < min_moves; i++) {
        printf("Direction (N/S/E/O) : ");
        scanf(" %c", &direction);
        move_robot(grid, robot, direction,targets);

        // Vérifier si la cible est atteinte
        if (robot->x == target->x && robot->y == target->y) {
            printf("Cible %c atteinte par le robot %c !\n", target->symbol, robot->symbol);
            scores[min_player]++;
            return;
        }
    }

    // Le joueur a échoué, les autres marquent un point
    printf("Le robot n'a pas atteint la cible %c.\n", target->symbol);
    for (int i = 0; i < num_players; i++) {
        if (i != min_player) {
            scores[i]++;
        }
    }
}

void play_guessing_round(Grid *grid, Robot *robot, Target *target, int *scores, int num_players) {
    int player_moves[num_players];

    // Demander aux joueurs combien de mouvements ils estiment nécessaires pour atteindre la cible
    for (int i = 0; i < num_players; i++) {
        printf("Joueur %d, combien de mouvements pour atteindre la cible %c ? ", i + 1, target->symbol);
        scanf("%d", &player_moves[i]);
    }

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
           min_player + 1, robot->symbol, min_moves, target->symbol);

    // Le joueur essaie de déplacer le robot en saisissant les commandes (N/S/E/O)
    char direction;
    for (int i = 0; i < min_moves; i++) {
        printf("Direction (N/S/E/O) : ");
        scanf(" %c", &direction);
        move_robot(grid, robot, direction,target);

        // Vérifier si la cible est atteinte
        if (robot->x == target->x && robot->y == target->y) {
            printf("Cible %c atteinte par le robot %c !\n", target->symbol, robot->symbol);
            scores[min_player]++;
            return;
        }
    }

    // Le joueur a échoué, les autres marquent un point
    printf("Le robot n'a pas atteint la cible %c.\n", target->symbol);
    for (int i = 0; i < num_players; i++) {
        if (i != min_player) {
            scores[i]++;
        }
    }
}