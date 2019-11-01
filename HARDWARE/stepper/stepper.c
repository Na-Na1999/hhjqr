
#include "stepper.h"
#include "math.h"

int bottom_step=0;
int top_step=0;
float bottom_tarangle,top_tarangle;

void stepper_init(){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_12);//bottom_off
	GPIO_ResetBits(GPIOC,GPIO_Pin_10);//bottom_+
	
	GPIO_SetBits(GPIOC,GPIO_Pin_11);//top_off

}
void settarget(float x,float y){
	float a1,a2,o1,o2;
	
	a1=atan2(x,h1-y)/PI*180;
	a2=acos(sqrt(x*x+(h1-y)*(h1-y))/2/r1)/PI*180;
	bottom_tarangle=180-a1-a2;
	top_tarangle=a1-a2;
}

//EXTI 中断配置
void EXTIX_Init(void)
{

    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14|GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOE4
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //使能复用功能时钟

   //GPIOE.4      中断线以及中断初始化配置  下降沿触发 //KEY0
  
}

u8 bottom_homemode=0;
u8 bottom_downcount=0;

u8 top_homemode=0;
u8 top_downcount=0;

int top_target = 5080;
int bottom_target=4840;
void top_Control(){
	if(top_btn==0){
		top_downcount=0;
	}else{
		if(top_downcount>=20){
			top_homemode=0;
			top_step=0;
		}else{
			top_downcount++;
		}
	}
	
	if(top_homemode){
		top_up=0;
		TIM4->CCR3=200;
	}else if(top_step!=top_target){
		if(top_up){
			TIM4->CCR3=200;
			top_step++;
		}else{
			if(TIM4->CCR3!=0){
				if(top_step==0)
					TIM_SetCompare3(TIM4,0);
				else
					top_step--;
			}
		}
	}else{
		TIM4->CCR3=0;
		
	}
}
void bottom_Control(){
	if(bottom_btn==0){//限位开关状态计数
		bottom_downcount=0;
	}else{
		
		if(bottom_downcount>=20){
			bottom_homemode=0;
			bottom_step=0;
		}else{
			bottom_downcount++;
		}
	}
	
	if(bottom_homemode){
		bottom_up=0;//控制方向为复位方向
		TIM4->CCR1=200;
	}else if(bottom_step!=bottom_target){
		if(bottom_up){
			TIM4->CCR1=200;
			bottom_step++;
		}else{
			if(TIM4->CCR1!=0){
				if(bottom_step==0)
					TIM_SetCompare1(TIM4,0);
				else
					bottom_step--;
			}
		}
	}else{
		
		TIM4->CCR1=0;
	}
}
