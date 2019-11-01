#ifndef __ENCODER_H
#define __ENCODER_H

#include <sys.h>
void TIM2_Encoder1_Init(u16 arr,u16 psc);
void TIM3_Encoder2_Init(u16 arr,u16 psc);
int Read_Encoder(u8 TIMX);

#endif
