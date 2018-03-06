#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <pthread.h>
#include <semaphore.h>
#include "../Backbone/Backbone.h"
#include "../Global_Constants/global_constants.h"
#include "../Motion_Structure/motion_structure.h"

/*************** GLOBAL VARIABLES ***************/
struct ball_t ball[N_BALLS];
int score;
int I, LAST, t, BG_COLOR, level, GAMETIME, LOSE, CATCH[N_BALLS], 
	ACC, DEC, STP, U, D, L, R, time_gained, STRIKES;
sem_t sem_balls_init, sem_balls_move, sem_player_controller;
SAMPLE *pop, *intro, *result;
/************************************/

#endif
