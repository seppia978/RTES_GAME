#include "header.h"

/*************** MAIN ***************/
int main(){
	char s[255]; // variable for the snprintf()
	int timing = (K_TIME / N_BALLS) + 1; // variable forthe handler
	time_gained = 0;
	srand(time(NULL));
	
	sem_init(&sem_balls_init, 0, 1);
	sem_init(&sem_balls_move, 0, 1);
	sem_init(&sem_player_controller, 0, 0);
		
	allegro_init();
		install_keyboard();
		install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);
		pop = load_sample("File/pop.wav");
		intro = load_sample("File/intro.wav");

		if (intro == NULL || pop == NULL)
			error_manager("Audio Error");
			
		play_sample(intro, VOL_MAX, 128, 1000, 1);
		set_color_depth(8);
		set_gfx_mode(GFX_AUTODETECT_WINDOWED, WID, HEI, 0, 0);
		init_game_params();
		while(!key[KEY_ENTER]) 
			usleep(10);
		
		play_the_game(timing);
		
		while(!key[KEY_ESC]) {
			if (key[KEY_ENTER]){
				if (score == N_BALLS - 1)
					level++;
					
				adjust_sample(intro, VOL_MIN, 128, 1000, 1);
				play_the_game(timing);
			}
		}
		
	allegro_exit();
}
/************************************/
