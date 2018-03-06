#include "controllers.h"

void accelerate(){
	if (ball[0].v.V0 < 1)
		ball[0].v.V0 = 0;
	ball[0].v.V0 += 2;
}
void decelerate(){
	ball[0].v.V0 -= 2;
	if (ball[0].v.V0 == 0)
		ball[0].v.V0 = 0.0000001;
}
void stop(){
	ball[0].v.V0 = 0.0000001;
}

