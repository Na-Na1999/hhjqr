#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
extern int step1;
//extern int T3,TH2,T4,delta,th4,th3;;
//extern int arr[30];
//extern int arrlen;
void TIM1_PWM_Init(u16 arr,u16 psc);
//void TIM2_Cap_Init(u16 arr,u16 psc);
//void TIM3_Int_Init(u16 arr,u16 psc);
//void TIM5_Cap_Init(u16 arr,u16 psc);
void TIM4_Int_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
void setPID(int x,int y);
#endif
