#include "level_params.h"

void enlarge_radius(){
	ball[0].R += RAD_INC;
}

int set_game_time(int level, int time){
	int game_time;
	game_time = GAME_TIME * N_BALLS / level;
	if (game_time < MIN_GAME_TIME)
		game_time = MIN_GAME_TIME;
	
	if (level > MIN_LEVEL_BONUS && STRIKES)
		time += LEVEL_BONUS_INC * STRIKES;
	
	game_time = set_extra_time(time, game_time);
	return game_time;
}

int set_extra_time(int time, int game_time){
	int extra_time;
	extra_time = game_time + time;
	return extra_time;
}

int time_bonus(int t, int level){
	if (level > 8 ) 
		t -= 2;
	return t;
}
