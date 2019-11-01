#include "arm.h"

Angles postion_transform(float x,float y){
	float d2=x*x+y*y;
	float d=sqrtf(d2);
	float theata2= acosf(l1/2/l3+l3/2/l1-d2/2/l1/l3);
	float theata1=asinf(l3/d*sinf(theata2));
	float theata3=atan2f(y,x);
	Angles angles;
	angles.top_theata=PI/2-theata3-theata1;
	angles.bottom_theata=angles.top_theata-theata2;
	
	angles.top_theata*=180.0/PI;
	angles.bottom_theata*=180.0/PI;
	
	return angles;
}