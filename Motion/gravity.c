#include "gravity.h"

void init_figure(float x, float y, float V, float theta, float accmod, int R){
	drawBorder();
	figure.p0.x = x;
	figure.p0.y = y;
	figure.pfin.x = figure.p0.x;
	figure.pfin.y = figure.p0.y;
	figure.dt.x = 0;
	figure.dt.y = 0;;
	figure.v0.x = V * cos(theta * PI / FLAT_ANGLE);
	figure.v0.y = V * (-sin(theta * PI / FLAT_ANGLE));
	figure.vfin.x = figure.v0.x;
	figure.vfin.y = figure.v0.y;
	figure.a.x = accmod * cos(theta * PI / FLAT_ANGLE);
	figure.a.y = - accmod * sin(theta * PI / FLAT_ANGLE);	
	figure.R = R;
}

void set_Environnement(int R){
	figure.R = R;
	LEFT = figure.R;
	RIGHT = WID - figure.R;
	TOP = figure.R;
	FLOOR = HEI - figure.R;
}

void drawBorder(){
	line(screen, TOP - figure.R, TOP - figure.R, WID, TOP - figure.R, 15);
	line(screen, TOP - figure.R, TOP - figure.R, TOP - figure.R, HEI, 15);
	line(screen, WID - 1, HEI - 1, WID - 1, TOP - figure.R, 15);
	line(screen, WID - 1, HEI - 1, TOP - figure.R, HEI - 1, 15);
}

void incTimeX(){
	figure.dt.x *= TIME_INTERVAL;
	figure.dt.x++;
	figure.dt.x /= TIME_INTERVAL;
}

void incTimeY(){
	figure.dt.y *= TIME_INTERVAL;
	figure.dt.y++;
	figure.dt.y /= TIME_INTERVAL;
}

void motion(){
	check_invertion();
	move_horizontal();
	define_gravity();
}

void check_invertion(){
	if (figure.pfin.y >= FLOOR || figure.pfin.y <= (TOP - figure.R))
		invertion(VER);

	if (figure.pfin.x >= RIGHT || figure.pfin.x <= LEFT)
		invertion(HOR);
}

void invertion(int dir){
	if (dir == VER){
		figure.vfin.y /= VATTENUATION;
		figure.v0.y = -figure.vfin.y;
		if (figure.pfin.y >= HEI - figure.R)
			figure.p0.y = FLOOR;
		else if (figure.pfin.y <= TOP)
			figure.p0.y = TOP;
		figure.dt.y = 0;

	}
	else if (dir == HOR){
		figure.vfin.x /= HATTENUATION;
		figure.v0.x = -figure.vfin.x;
		if (figure.pfin.x >= WID - figure.R)
			figure.p0.x = RIGHT;
		else if (figure.pfin.x <= LEFT){
			figure.p0.x = LEFT;
		}
		figure.dt.x = 0;
	}
}

void move_horizontal(){
	int tempx;
	incTimeX(); 
	tempx = figure.pfin.x;

	figure.pfin.x = figure.p0.x + figure.v0.x * figure.dt.x + 0.5 * figure.a.x * figure.dt.x * figure.dt.x;
	figure.vfin.x = figure.v0.x + figure.a.x * figure.dt.x;
	
	interface.pfin.x = figure.pfin.x;
	interface.vfin.x = figure.vfin.x;
}

void define_gravity(void){
	int tempy;
	incTimeY();
	tempy = figure.pfin.y;
	figure.pfin.y = figure.p0.y + figure.v0.y * figure.dt.y + 0.5 * (/*G - */figure.a.y) * figure.dt.y * figure.dt.y;
	figure.vfin.y = figure.v0.y + (/*G - */figure.a.y) * figure.dt.y;
	
	interface.pfin.y = figure.pfin.y;
	interface.vfin.y = figure.vfin.y;
}

