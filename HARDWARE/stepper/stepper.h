#ifndef __stepper_H
#define __stepper_H

#include "sys.h"

#define PI 3.1415926535898

#define bottom_TopStep   4840
#define bottom_StartToTopAngle 108

#define top_TopStep   3080  //90度步进值
#define top_StartToTopAngle 35

#define bottom_off PCout(12)//驱动使能
#define bottom_up PCout(10)
#define bottom_btn PBin(14)

#define top_off PCout(11)//驱动使能
#define top_up PCout(9)
#define top_btn PBin(15)

#define h1 138

#define r1 118





extern int bottom_step;
extern int top_step;
extern float bottom_tarangle,top_tarangle;
extern u8 bottom_homemode,top_homemode;

extern int top_target,bottom_target;

void  stepper_init();
void settarget(float x,float y);
void EXTIX_Init(void);

void top_Control();
void bottom_Control();
#endif