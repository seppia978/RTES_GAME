#include "game_flow.h"

void *initialize(void *arg)
{
	sem_wait(&sem_balls_init);
		init_balls();
	sem_post(&sem_balls_init);
}

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
	char s[255];
	
	I = 0;
	LOSE = 0;
	
	do{
		BG_COLOR = rand() % 15; 
	} while (BG_COLOR == PLAYER_COL || BG_COLOR == 0);
	if (level > 12)
		BG_COLOR = 0;
		
	clear_to_color(screen, BG_COLOR);
	
	GAMETIME = set_game_time(level, time_gained);
	
	adjust_sample(intro, VOL_MIN, 128, 1000, 1);
			
	pthread_attr_init(&attr);
	for (j = 0; j < N_BALLS; j++)
		pthread_create(&p[j], &attr, initialize, NULL);
	pthread_attr_destroy(&attr);
		
	for (j = 0; j < N_BALLS; j++)
		pthread_join(p[j], NULL);
		
	initialize_parameters();
	
	drawBorder();

	install_int(move, timing);
	install_int(inc_Timet, 1000);
	while(LOSE == 0) ;
	remove_int(move);
	remove_int(inc_Timet);
	for (I = 0; I < N_BALLS; I++)
		drawCircle(ball[I].pin.x, ball[I].pin.y, ball[I].R, BG_COLOR);

	if (score == N_BALLS - 1){
		textout_ex(screen, font, "YOU WIN :)", HOR_CENTER, 450, 15, 0);
		snprintf(s, 255, "time gained: %d", time_gained);
		textout_ex(screen, font, s, HOR_CENTER, 470, 15, 0);
		result = load_sample("File/winner.wav");
	}
	else{
		textout_ex(screen, font, "YOU LOSE :(", HOR_CENTER, 450, 15, 0);
		result = load_sample("File/loser.wav");
	}
	//textout_ex(screen, font, s, 450, 450, 15, 0);
	play_sample(result, VOL_MAX, 128, 1000, 0);		
		
	printScore();
	sleep(2);
	
	if (score == N_BALLS - 1)
		textout_ex(screen, font, "Enter to next level", HOR_CENTER, 490, 15, 0);
	else
		textout_ex(screen, font, "Enter to retry", HOR_CENTER, 490, 15, 0);
	textout_ex(screen, font, "Esc to exit", HOR_CENTER, 510, 15, 0);
	stop_sample(result);
	adjust_sample(intro, VOL_MAX, 128, 1000, 1);
}

void inc_Timet(){
	t++;
	printScore();
}

