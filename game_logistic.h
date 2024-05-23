#ifndef GAME_LOGISTIC_H
#define GAME_LOGISTIC_H

#include "grid.h"
#include "target.h"
#include "robot.h"

int select_random_robot(Robot *robots, int num_robots);
int select_random_target(Target *targets, int num_targets);
void play_guessing_round(Grid *grid, Robot *robot, Target *target, int *scores, int num_players);
void play_round(Grid *grid, Robot *robots, int num_robots, Target *targets, int num_cibles, int *scores, int num_players);

#endif // GAME_LOGISTIC_H