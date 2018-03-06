#ifndef MOTION_STRUCTURE_H
#define MOTION_STRUCTURE_H

/********** MOTION STRUCTURES **********/
struct pos_t{
	float x, y;
};

struct vel_t{
	float V0, theta;
};

struct acc_t{
	float a_mod;
};

struct ball_t{
	struct pos_t pin, pfin, pstart;
	struct vel_t v, vstart;
	struct acc_t acc;
	int R;
	int col;
};
/*************************************************/

#endif
