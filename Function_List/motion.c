#include "motion.h"

/**************** THREAD *******************/

/* T#1 initialize(void *arg)
 * this threads initialize their ball
*/

void *move_ball(void *arg)
{
	int ind = (int)arg;
	
	if (LOSE == 0 && CATCH[ind] == 1){
	
		sem_wait(&sem_balls_move);
		
			init_figure(ball[ind].pin.x, ball[ind].pin.y, ball[ind].v.V0, ball[ind].v.theta, ball[ind].acc.a_mod, ball[ind].R);
			
			drawCircle(ball[ind].pin.x, ball[ind].pin.y, ball[ind].R, BG_COLOR);
			
			motion();
			reset(ind);
			
			drawCircle(ball[ind].pin.x, ball[ind].pin.y, ball[ind].R, ball[ind].col);
			
			if (ind != 0)
				detect_collision(ind);
		
			drawBorder();
					
		sem_post(&sem_balls_move);
	
	}
}

void *player_controller(void *arg)
{
	if (LOSE == 0){
		if (R)
			vel_right();
		
		if (L)
			vel_left();
			
		if (U)
			vel_up();
		
		if (D)
			vel_down();
		
		if (ACC)
			accelerate();
			
		if (STP)
			stop();
		
		if (DEC)
			decelerate();
			
		U = D = L = R = ACC = DEC = STP = 0;
	}
}
/******************************************/

/* #9:#14
 * control the velocity or the acceleration of the player ball
*/

void vel_right(){
	ball[0].v.theta = 0;
}

void vel_left(){
	ball[0].v.theta = 180;
}

void vel_up(){
	ball[0].v.theta = 90;
}

void vel_down(){
	ball[0].v.theta = 270;
}

/* #15 move()
 * controls the motion of the balls using Gravity2.h
*/

void move(){
	pthread_attr_t attr;
	pthread_t p[N_BALLS], c;
	int j;
	//printf("%d %d %d\n", LOSE, t, score);

	printScore();
	printAcc();
	//detect_collision();
	
	pthread_attr_init(&attr);
	
	for (j = 0; j < N_BALLS; j++)
		pthread_create(&p[j], &attr, move_ball, (void *)j);
		
	if (key[KEY_ESC] || score == (N_BALLS - 1) || t >= GAMETIME){
		LOSE = 1;
		if (score == (N_BALLS - 1)){
			time_gained = GAMETIME - t;
			STRIKES = 0;
		}
		else {
			STRIKES++;
		}
	}
	
	for (j = 0; j < N_BALLS; j++)
		pthread_join(p[j], NULL);	
			
	if (key[KEY_UP])
		U = 1;
	
	if (key[KEY_DOWN])
		D = 1;
		
	if (key[KEY_LEFT])
		L = 1;
	
	if (key[KEY_RIGHT])
		R = 1;
		
	if (key[KEY_A])
		ACC = 1;
		
	if (key[KEY_S])
		STP = 1;
	
	if (key[KEY_D])
		DEC = 1;
	
	pthread_create(&c, &attr, player_controller, NULL);
	pthread_join(c, NULL);
	pthread_attr_destroy(&attr);
}

/* #16 reset()
 * takes computed values from Gravity2.h and stores them into its state variables
*/

void reset(int ind){
	ball[ind].pfin.x = interface.pfin.x;
	ball[ind].pfin.y = interface.pfin.y;
	ball[ind].pin.x = interface.pfin.x;
	ball[ind].pin.y = interface.pfin.y;
	ball[ind].v.V0 = pow((interface.vfin.x*interface.vfin.x+interface.vfin.y*interface.vfin.y),0.5);
	if (interface.vfin.x < 0)
		ball[ind].v.theta = FLAT_ANGLE + atan((-interface.vfin.y)/interface.vfin.x)*FLAT_ANGLE/PI;
	else
		ball[ind].v.theta = atan((-interface.vfin.y)/interface.vfin.x)*FLAT_ANGLE/PI;

}

