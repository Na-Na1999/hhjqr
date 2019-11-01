#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "oled.h"
#include "stdio.h"
#include "timer.h"
#include "dma.h"
#include "usart.h"
#include "string.h"
#include "encoder.h"
#include "keypad.h"
#include "stepper.h"
//ALIENTEK Mini STM32开发板范例代码2
//按键输入实验		   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
#include "jy901.h"
#include "arm.h"
 int a=0;
 struct SAngle 	stcAngle;
 struct SMag stcMag;
	
	 
 extern float xx,yy,zz;
 
 char str[12]={0};

 #include "math.h"
 
 
 void handledma(){
	if(USART2_RX_BUF[0])    //数组0有数据了，说明DMA开始接收一段数据
		{
			int i;
				if(USART2_RX_BUF[i]==0x55&&USART2_RX_BUF[i+1]==0x53){
					if(strlen((char*)USART2_RX_BUF)-i>=10){
						memcpy(&stcAngle,&USART2_RX_BUF[i+2],8);
						xx=(float)stcAngle.Angle[0]/32768*180;
						yy=(float)stcAngle.Angle[1]/32768*180;
						zz=(float)stcAngle.Angle[2]/32768*180;
					}
					
				}
				DMA_Cmd(DMA1_Channel5, DISABLE );
				MYDMA_Enable(DMA1_Channel5,ARRLEN);//开始一次DMA传输！

		}
	
 }
 void dokey(){
	if(keybufferlen>0){
			int i;
			for(i=0;i<keybufferlen;i++){
				switch(keybuffer[i]){
					case 3:
						bottom_off=!bottom_off;
						if(bottom_off){
							OLED_ShowStr(0,1,"off ",1);
						}else{
							OLED_ShowStr(0,1,"on  ",1);
						}
						break;
					case 7:
						bottom_up=!bottom_up;
						if(bottom_up){
							OLED_ShowStr(0,2,"+",1);
						}else{
							OLED_ShowStr(0,2,"-",1);
						}
						
					break;
					case 11:
						
						top_off=!top_off;
						if(top_off){
							OLED_ShowStr(4,1,"off ",1);
						}else{
							OLED_ShowStr(2,1,"on ",1);
						}
					break;
					case 5:
						
						bottom_homemode=1;
					break;
					case 9:
						top_homemode=1;
						
						break;
					case 15:
						top_up=!top_up;
					break;
				}
			}
			keybufferlen=0;
		}
}
 int main(void)
 {	
	 
	
	char strbuf[20];
	delay_init();	    	 //延时函数初始化	  
	 
	 //LED_Init();		 //初始化与LED连接的硬件接口
	
	 
	  stepper_init();
	 
	OLED_Init();
	OLED_ON();
	 
	OLED_Fill(0xff);
	 
	
	
//	 Timer1_Init(7199,199);  
	TIM4_PWM_Init(400,359);
	 
//	TIM2_Encoder1_Init(65535,0);
//	TIM3_Encoder2_Init(65535,0);
//	 //uart2_init(115200);	
//	uart_init(115200);
//	 
	keypad_Init();         	//初始化与按键连接的硬件接口
//						//点亮LED
//	MYDMA_Config(USART1,DMA1_Channel5,(u32)USART2_RX_BUF,ARRLEN);
//	//MYDMA_Config2(USART1,DMA1_Channel5,(u32)&USART1->DR,(u32)USART2_RX_BUF,200);
//	 //delay_ms(10000);
//	 
//	              `



EXTIX_Init();
	settarget(150,50);
	 TIM_SetCompare1(TIM4,400);
	 TIM_SetCompare3(TIM4,400);
	 top_homemode=1;
	 bottom_homemode=1;
	{
		Angles angle= postion_transform(200,0);
		 
		top_target=top_TopStep+angle.top_theata*60.0;
		bottom_target=bottom_TopStep+angle.bottom_theata*60.0;
		
		while(1){
			
			
			sprintf(strbuf,"%2d %5d %5d",key,bottom_step,top_step);       
			OLED_ShowStr(0,6,(u8*)strbuf,1);
			//sprintf(strbuf,"%f %f",bottom_tarangle,top_tarangle);       
			sprintf(strbuf,"%f %f",angle.bottom_theata,angle.top_theata);       
			OLED_ShowStr(0,4,(u8*)strbuf,1);
			scankeypad();
			dokey();
		}
	}
	
}
