#ifndef __ARM_H
#define __ARM_H	 
#include "sys.h"
#include "stm32f10x_dma.h"
#include "math.h"
#include "stepper.h"

#define l1 200 //mm
#define w 27 //mm
#define l2 208
#define l3 209.745083


typedef struct {
 float bottom_theata;
 float top_theata;
}Angles;

Angles postion_transform(float x,float y);

#endif