#ifndef GRAVITY_H
#define GRAVITY_H

#include "../Backbone/Backbone.h"

#define VER 0
#define HOR 1
#define STOPH 4
#define STOPV 5
#define VATTENUATION 1
#define HATTENUATION 1
#define G 9.8
#define TIME_INTERVAL 10
#define PI 3.14159265
#define FLAT_ANGLE 180.0

struct position_t{
	float x, y;
};

struct velocity_t{
	float x, y;
};

struct acceleration_t{
	float x, y;
};

struct dt_t{
	float x, y;
};

struct figure_t{
	struct position_t p0, pfin;
	struct velocity_t v0, vfin;
	struct acceleration_t a;
	struct dt_t dt;
	int R;
} figure;

struct interface_t{
	struct position_t pfin;
	struct velocity_t vfin;
} interface;

void define_gravity(void);
void move();
void move_horizontal();
void init_figure(float x, float y, float V, float theta, float accmod, int R);
void invertion(int dir);
void drawBorder();
void check_invertion();
void motion();
void set_Environnement(int R);

struct position_t pos;
struct velocity_t vel;
struct dt_t dt;
float ax;


#endif
