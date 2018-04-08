#include "init_game_params.h"

/*
 * Intro
*/
void init_game_params(){
	textout_ex(screen, font, "CATCH ALL THE BALLS!!", HOR_CENTER - 65, VER_CENTER, 15, 0);
	textout_ex(screen, font, "Arrows to drive", HOR_CENTER - 40, VER_CENTER + 130, 15, 0);
	textout_ex(screen, font, "A to accelerate, D to decelerate, S to stop", HOR_CENTER - 150, VER_CENTER + 150, 15, 0);
	level = 1;
	textout_ex(screen, font, "Enter to start", HOR_CENTER - 40, VER_CENTER + 170, 15, 0);
}
