#ifndef MOTION_H
#define MOTION_H

#include <pthread.h>
#include <semaphore.h>
#include "../Global_Variables/global_variables.h"
#include "../Motion/gravity.h"
#include "graphic.h"
#include "controllers.h"

void move();
void reset(int ind);
void vel_left();
void vel_right();
void vel_up();
void vel_down();

#endif
