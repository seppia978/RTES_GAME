#ifndef GAMEFLOW_H
#define GAMEFLOW_H

#include <pthread.h>
#include <semaphore.h>
#include "../Global_Variables/global_variables.h"
#include "../Level_params/level_params.h"
#include "motion.h"
#include "graphic.h"
#include "inits.h"

void play_the_game(int timing);
void inc_Timet();

#endif
