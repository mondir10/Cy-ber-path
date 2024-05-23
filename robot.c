#include "robot.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>


void place_robots(Grid *grid, Robot *robots, int num_robots) {
    srand(time(NULL));
    for (int i = 0; i < num_robots; i++) {
        int x, y;
        int placed = 0;
        while (!placed) {
            x = rand() % grid->width;
            y = rand() % grid->height;
            if (grid->cells[y][x] == ' ') {
                grid->cells[y][x] = robots[i].symbol;
                robots[i].x = x;
                robots[i].y = y;
                placed = 1;
            }
        }
    }
}



void move_robot(Grid *grid, Robot *robot, char direction,Target *targets[]) {
    // Effacez la position actuelle du robot
    grid->cells[robot->y][robot->x] = ' ';

    int initial_x = robot->x;
    int initial_y = robot->y;

    // Déplacer le robot en fonction de la direction
    switch (toupper(direction)) {
        case 'N':
            while (robot->y > 0 && grid->cells[robot->y - 1][robot->x] != '1' && grid->cells[robot->y - 1][robot->x] != '2' &&
                   grid->cells[robot->y - 1][robot->x] != '3' && grid->cells[robot->y - 1][robot->x] != '4' && grid->cells[robot->y - 1][robot->x] != '#') {
                robot->y--;
                if (grid->cells[robot->y][robot->x] >= 'A' && grid->cells[robot->y][robot->x] <= 'Z') {
                    break; // Si on atteint une cible, arrêter
                }
            }
            break;
        case 'S':
            while (robot->y < grid->height - 1 && grid->cells[robot->y + 1][robot->x] != '1' && grid->cells[robot->y + 1][robot->x] != '2' &&
                   grid->cells[robot->y + 1][robot->x] != '3' && grid->cells[robot->y + 1][robot->x] != '4' && grid->cells[robot->y + 1][robot->x] != '#') {
                robot->y++;
                if (grid->cells[robot->y][robot->x] >= 'A' && grid->cells[robot->y][robot->x] <= 'Z') {
                    break; // Si on atteint une cible, arrêter
                }
            }
            break;
        case 'E':
            while (robot->x < grid->width - 1 && grid->cells[robot->y][robot->x + 1] != '1' && grid->cells[robot->y][robot->x + 1] != '2' &&
                   grid->cells[robot->y][robot->x + 1] != '3' && grid->cells[robot->y][robot->x + 1] != '4' && grid->cells[robot->y][robot->x + 1] != '#') {
                robot->x++;
                if (grid->cells[robot->y][robot->x] >= 'A' && grid->cells[robot->y][robot->x] <= 'Z') {
                    break; // Si on atteint une cible, arrêter
                }
            }
            break;
        case 'O':
            while (robot->x > 0 && grid->cells[robot->y][robot->x - 1] != '1' && grid->cells[robot->y][robot->x - 1] != '2' &&
                   grid->cells[robot->y][robot->x - 1] != '3' && grid->cells[robot->y][robot->x - 1] != '4' && grid->cells[robot->y][robot->x - 1] != '#') {
                robot->x--;
                if (grid->cells[robot->y][robot->x] >= 'A' && grid->cells[robot->y][robot->x] <= 'Z') {
                    break; // Si on atteint une cible, arrêter
                }
            }
            break;
    }

    // Vérifiez si le robot a quitté une cellule de cible et restaurez la cible
    for (int i = 0; i < 18; i++) {
        if (targets[i]->x == initial_x && targets[i]->y == initial_y) {
            grid->cells[initial_y][initial_x] = targets[i]->symbol;
            break;
        }
    }

    // Placez le robot dans la nouvelle position
    grid->cells[robot->y][robot->x] = robot->symbol;
}