#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "../Backbone/Backbone.h"
#include "../Global_Variables/global_variables.h"

void drawCircle(float x, float y, int R, int c);
void drawBorder();
void set_init_Color(int i, int color);
void setColor(int i);
void printAcc();
void printScore();
void detect_collision(int J);
int intersection(struct pos_t p0, struct pos_t p1, int ind);

#endif
