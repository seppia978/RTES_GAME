#include "graphic.h"

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
	ball[i].col = BG_COLOR; //PLAYER_COL;
}

/* #7 drawCircle(float x, float y, int R, int c)
* draws a circle with the data passed 
*/

void drawCircle(float x, float y, int R, int c){
	acquire_screen();
		circlefill(screen, x, y, R, c);
	release_screen();
}

int intersection(struct pos_t p0, struct pos_t p1, int ind){
	bool ans = 0;
	float dist = pow(p0.x - p1.x, 2) + pow(p0.y - p1.y, 2);
	if (dist < pow((ball[ind].R + ball[0].R), 2)){
		ans = 1;
	}	
	return ans;
}

/* #8 detect_collision()
 * checks whether two balls are colliding or not
*/

void detect_collision(int J){	
	//for (J = I + 1; J < N_BALLS; J++){
		if (intersection(ball[J].pin, ball[0].pin, J)){
			//enlarge_radius(ball[0].R);
			score++;
			drawCircle(ball[J].pin.x, ball[J].pin.y, ball[J].R, BG_COLOR);
			t = time_bonus(t, level);
			CATCH[J] = 0;
			play_sample(pop, VOL_MAX, 128, 1000, 0);
		}
	//}
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
