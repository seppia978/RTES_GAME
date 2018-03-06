#include "inits.h"

/* #6 init_balls()
 * initializes the balls
*/

void init_balls(){
	
	ball[I].R = 50 / level;
	if (ball[I].R > 10)
		ball[I].R = 10;
	
	if (I == 0)
		set_Environnement(ball[0].R);
	if (I != 0){
		ball[I].pstart.x = rand() % (RIGHT - LEFT) + LEFT;
		ball[I].pstart.y = rand() % (FLOOR - TOP) + TOP;
		ball[I].vstart.V0 = rand() % 100 + 10 * level;
		ball[I].vstart.theta = rand() % 360;
		ball[I].acc.a_mod = 0;
		set_init_Color(I, 16);
	}
	else{
		ball[0].pstart.x = LEFT;
		ball[0].pstart.y = TOP;
		ball[0].vstart.V0 = rand() % 200 + 50;
		ball[0].vstart.theta = rand() % 360;
		ball[0].acc.a_mod = 0;
		ball[0].R = 15;
		ball[0].col = PLAYER_COL;
	}
	
	ball[I].pin.x = ball[I].pstart.x;
	ball[I].pin.y = ball[I].pstart.y;
	ball[I].v.V0 = ball[I].vstart.V0;
	ball[I].v.theta = ball[I].vstart.theta;

	drawCircle(ball[I].pin.x, ball[I].pin.y, ball[I].R, ball[I].col);

	I++;
}

/* #17 initialize_parameters()
 * just does what is written :)
*/

void initialize_parameters(){
	int i;
	t = 0;
	score = 0;
	printScore();
	LAST = N_BALLS + 1;
	I = 0;
	for (i = 0; i < N_BALLS; i++)
		CATCH[i] = 1;
}
