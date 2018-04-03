#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#include "Motion/Gravity2.h"

/********** RELEVANT CONSTANT ***********/

#define N_BALLS 20
#define K_TIME 25
#define GAME_TIME 5
#define PLAYER_COL 4
#define VOL_MAX 255
#define VOL_MIN 50

/***************************************/
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
/**************** FUNCTIONS LIST *****************/

void drawCircle(float x, float y, int R, int c);
void drawBorder();
void move();
void reset();
void init_balls();
void check_bouncing();
int intersection(struct pos_t p0, struct pos_t p1);
void vel_left();
void vel_right();
void vel_up();
void vel_down();
void set_init_Color(int i, int color);
void setColor(int i);
void printAcc();
void printScore();
void inc_Timet();
void accelerate();
void decelerate();
void stop();
void play_the_game(int timing);
void init_sounds();
/************************************************/
/*************** GLOBAL VARIABLES ***************/

struct ball_t ball[N_BALLS];
int score;
int I, LAST, t, BG_COLOR, level, GAMETIME;
sem_t sem_balls;
SAMPLE *pop, *intro, *result;
/************************************/
/*************** MAIN ***************/

int main(){
	char s[255];
	int timing = (K_TIME / N_BALLS) + 1;
	
	srand(time(NULL));
	
	sem_init(&sem_balls, 0, 1);
		
	allegro_init();
		install_keyboard();
		install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);
		pop = load_sample("File/pop.wav");
		intro = load_sample("File/intro.wav");

		if (intro == NULL)
			exit(1);
		play_sample(intro, VOL_MAX, 128, 1000, 1);
		set_color_depth(8);
		set_gfx_mode(GFX_AUTODETECT, WID, HEI, 0, 0);
		textout_ex(screen, font, "CATCH ALL THE BALLS!!", 450, 300, 15, 0);
		textout_ex(screen, font, "Arrows to drive", 450, 430, 15, 0);
		textout_ex(screen, font, "A to accelerate, D to decelerate, S to stop", 350, 450, 15, 0);
		level = 1;
		textout_ex(screen, font, "Enter to start", 450, 470, 15, 0);
		while(!key[KEY_ENTER]) ;
		
		play_the_game(timing);
		
		while(!key[KEY_ENTER]) {
			if (key[KEY_SPACE]){
				//select_Level();
				if (score == N_BALLS - 1)
					level++;

				adjust_sample(intro, VOL_MIN, 128, 1000, 1);
				play_the_game(timing);
			}
		}
		
	allegro_exit();
}
/*******************************************/
/**************** THREAD *******************/

/* T#1 initialize(void *arg)
 * this threads initialize their ball
*/

void *initialize(void *arg)
{
	sem_wait(&sem_balls);
		init_balls();
	sem_post(&sem_balls);
}
/******************************************/
/************** FUNCTIONS *****************/

/* #1 play_the_game(int timing)
 * 
 * manages the flow of the game.
 * 
 * divided in steps:
 * - colors the screen
 * - set the game time
 * - create N_BALLS thread to create the balls
 * - sets some game variables
 * - draws borders
 * - install the handler function
 * - detects esc pressed
 * - declares victory or losing state
 * - controls the audio
 */

void play_the_game(int timing){	
	pthread_attr_t attr;
	pthread_t p[N_BALLS];
	int j;
	
	I = 0;
	
	do{
		BG_COLOR = rand() % 15; 
	} while (BG_COLOR == PLAYER_COL || BG_COLOR == 0);
	if (level > 12)
		BG_COLOR = 0;
		
	clear_to_color(screen, BG_COLOR);
	
	GAMETIME = GAME_TIME * N_BALLS / level;
	if (GAMETIME < 10)
		GAMETIME = 10;
	
	adjust_sample(intro, VOL_MIN, 128, 1000, 1);
			
	pthread_attr_init(&attr);
	for (j = 0; j < N_BALLS; j++)
		pthread_create(&p[j], &attr, initialize, NULL);
	pthread_attr_destroy(&attr);
		
	for (j = 0; j < N_BALLS; j++)
		pthread_join(p[j], NULL);
		
	t = 0;
	score = 0;
	printScore();
	LAST = N_BALLS + 1;
	
	I = 0;
	
	drawBorder();
	install_int(move, timing);
	install_int(inc_Timet, 1000);
	while(!key[KEY_ESC] && score != (N_BALLS - 1) && t < GAMETIME) ;
	remove_int(move);
	remove_int(inc_Timet);
	for (I = 0; I < N_BALLS; I++)
		drawCircle(ball[I].pin.x, ball[I].pin.y, ball[I].R, BG_COLOR);
	textout_ex(screen, font, "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", 512, 650, BG_COLOR, BG_COLOR);
	//snprintf(s, 255, "SCORE: %d", score);
	textout_ex(screen, font, "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", 450, 450, BG_COLOR, BG_COLOR);
	if (score == N_BALLS - 1){
		textout_ex(screen, font, "YOU WIN :)", 450, 450, 15, 0);
		textout_ex(screen, font, "Space to next level", 450, 490, 15, 0);
		result = load_sample("File/winner.wav");
	}
	else{
		textout_ex(screen, font, "YOU LOSE :(", 450, 450, 15, 0);
		textout_ex(screen, font, "Space to retry", 450, 490, 15, 0);
		result = load_sample("File/loser.wav");
	}
	//textout_ex(screen, font, s, 450, 450, 15, 0);
	play_sample(result, VOL_MAX, 128, 1000, 0);
	textout_ex(screen, font, "Enter to exit", 450, 470, 15, 0);		
		
	printScore();
	sleep(2);
	stop_sample(result);
	adjust_sample(intro, VOL_MAX, 128, 1000, 1);
}

void inc_Timet(){
	t++;
	printScore();
}

/* #2 printScore()
 * prints out the current score, the remaining time (in seconds) and the current level
*/

void printScore(){
	char s[255];
	snprintf(s, 255, "SCORE: %d | TIME: %d | LEVEL: %d", score, GAMETIME - t + 1, level);
	textout_ex(screen, font, s, LEFT, TOP, BG_COLOR, BG_COLOR);
	snprintf(s, 255, "SCORE: %d | TIME: %d | LEVEL: %d", score, GAMETIME - t, level);
	textout_ex(screen, font, s, LEFT, TOP, 15, 0);
}

/* #3 printAcc()
 * prints out the current velocity (module and angle)
*/

void printAcc(){
	char s[255];
	snprintf(s, 255, "|v|: %f - theta: %f", ball[0].v.V0, ball[0].v.theta);
	textout_ex(screen, font, s, 750, 758, 15, 0); 
}

/* #4 set_init_Color(int i, in color)
 * sets the initial color of the ball passed
*/

void set_init_Color(int i, int color){
	do{
		ball[i].col = (rand() % 15) + 1;
	} while (ball[i].col == color || ball[i].col == PLAYER_COL || ball[i].col == BG_COLOR);
}

/* #5 setColor(int i)
 * sets the color of the caught ball
*/

void setColor(int i){
	ball[i].col = 0; //PLAYER_COL;
}

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
		ball[I].vstart.V0 = rand() % 100 + 100;
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

/* #7 drawCircle(float x, float y, int R, int c)
* draws a circle with the data passed 
*/

void drawCircle(float x, float y, int R, int c){
	acquire_screen();
		circlefill(screen, x, y, R, c);
	release_screen();
}

int intersection(struct pos_t p0, struct pos_t p1){
	bool ans = 0;
	float dist = pow(p0.x - p1.x, 2) + pow(p0.y - p1.y, 2);
	if (dist <= 4 *ball[I].R * ball[I].R){
		ans = 1;
	}	
	return ans;
}

/* #8 check_bouncing()
 * checks whether two balls are colliding or not
*/

void check_bouncing(){
	int J = I;
	float tmp;
	
	for (J = I + 1; J < N_BALLS; J++){
		if (intersection(ball[J].pin, ball[I].pin)){
			if (LAST != J){
				if (I == 0 && ball[J].col != 0){
					score++;
					setColor(J);
					LAST = J;
					play_sample(pop, VOL_MAX, 128, 1000, 0);
				}
			}
		}
	}
}

/* #9:#14
 * control the velocity or the acceleration of the player ball
*/

void vel_right(){
	ball[I].v.theta = 0;
}

void vel_left(){
	ball[I].v.theta = 180;
}

void vel_up(){
	ball[I].v.theta = 90;
}

void vel_down(){
	ball[I].v.theta = 270;
}

void accelerate(){
	ball[I].v.V0 += 2;
}
void decelerate(){
	ball[I].v.V0 -= 2;
}
void stop(){
	ball[I].v.V0 = 0.000001;
}

/* #15 move()
 * controls the motion of the balls using Gravity2.h
*/

void move(){
	printScore();
	printAcc();
	check_bouncing();
	init_figure(ball[I].pin.x, ball[I].pin.y, ball[I].v.V0, ball[I].v.theta, ball[I].acc.a_mod, ball[I].R);
	
	drawCircle(ball[I].pin.x, ball[I].pin.y, ball[I].R, BG_COLOR);
	
	motion();
	reset();	
	
	if (key[KEY_RIGHT] && I == 0)
		vel_right();
	
	if (key[KEY_LEFT] && I == 0)
		vel_left();
		
	if (key[KEY_UP] && I == 0)
		vel_up();
	
	if (key[KEY_DOWN] && I == 0)
		vel_down();
	
	if (key[KEY_A] && I == 0)
		accelerate();
		
	if (key[KEY_S] && I == 0)
		stop();
	
	if (key[KEY_D] && I == 0)
		decelerate();
	
	drawCircle(ball[I].pin.x, ball[I].pin.y, ball[I].R, ball[I].col);
	
	drawBorder();
	
	I++;
	I = I%N_BALLS;
}

/* #16 reset()
 * takes computed values from Gravity2.h and stores them into its state variables
*/

void reset(){
	ball[I].pfin.x = interface.pfin.x;
	ball[I].pfin.y = interface.pfin.y;
	ball[I].pin.x = interface.pfin.x;
	ball[I].pin.y = interface.pfin.y;
	ball[I].v.V0 = pow((interface.vfin.x*interface.vfin.x+interface.vfin.y*interface.vfin.y),0.5);
	if (interface.vfin.x != 0 && interface.vfin.y != 0){
		if (interface.vfin.x < 0)
			ball[I].v.theta = FLAT_ANGLE + atan((-interface.vfin.y)/interface.vfin.x)*FLAT_ANGLE/PI;
		else
			ball[I].v.theta = atan((-interface.vfin.y)/interface.vfin.x)*FLAT_ANGLE/PI;
	}
	else
		ball[I].v.theta = 0;
}
/******************************************/
