#ifndef LEVEL_PARAMS_H
#define LEVEL_PARAMS_H

#include "../Backbone/Backbone.h"
#include "../Global_Variables/global_variables.h"

#define GAME_TIME 5
#define MIN_LEVEL_BONUS 10
#define LEVEL_BONUS_INC 5
#define MIN_GAME_TIME 10
#define RAD_INC 2

int set_game_time(int level, int time);
int set_extra_time(int time, int game_time);
void enlarge_radius();
int time_bonus(int t, int level);

#endif
