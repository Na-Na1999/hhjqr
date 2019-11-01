
#include "keypad.h"
u8 keydowncount[4][4]={0};
IO_reg rowio[4];

IO_reg colio[4];
u8 rowcount=0,colcount=0;
char keybuffer[16]={0};
char keybufferlen=0;
int key=-1;
GPIO_TypeDef* getgpiox(char gpiox){
	switch(gpiox){
		case 'A':
		case 'a':
			return GPIOA;
			break;
		case 'B':
		case 'b':
			return GPIOB;
		break;
		case 'C':
		case 'c':
			return GPIOC;
		break;
		case 'D':
		case 'd':
			return GPIOD;
		break;
		case 'E':
		case 'e':
			return GPIOE;
		break;
		case 'F':
		case 'f':
			return GPIOF;
		break;
		case 'G':
		case 'g':
			return GPIOG;
		break;
	}
}
void keypad_Init(void)
{
	
  init_io_out('c',GPIO_Pin_0);
	init_io_out('c',GPIO_Pin_2);
	init_io_out('a',GPIO_Pin_0);
	init_io_out('a',GPIO_Pin_2);
	
	init_io_in('a',GPIO_Pin_4);
	init_io_in('a',GPIO_Pin_6);
	init_io_in('c',GPIO_Pin_4);//a10≤ªƒ‹”√
	init_io_in('b',GPIO_Pin_0);//
}
void scankeypad(){
	int i,j;
	
//	GPIO_SetBits(getgpiox(rowio[0].word),rowio[0].id);
//	if(GPIO_ReadInputDataBit(&colio[0].gtd,colio[0].id)){
//		key=1;
//	}
  for(i=0;i<4;i++){
		GPIO_SetBits(getgpiox(rowio[i].word),rowio[i].id);
		for(j=0;j<4;j++){
			
			if(GPIO_ReadInputDataBit(getgpiox(colio[j].word),colio[j].id)){
				if(keydowncount[i][j]!=250)keydowncount[i][j]++;
			}else{
				keydowncount[i][j]=0;
			}
			keyevent(i,j);
		}
		GPIO_ResetBits(getgpiox(rowio[i].word),rowio[i].id);
	}
}
void keyevent(int i,int j){
	if(keydowncount[i][j]==3){
		
		key=i*4+j;
		keybuffer[keybufferlen++]=key;
		
	}
}
void init_io_in(char io, uint16_t GPIO_Pin){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_TypeDef * gtd;
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin;
	
	
	switch(io){
		case 'A':
		case 'a':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
			gtd=GPIOA;
			break;
		case 'B':
		case 'b':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		gtd=GPIOB;
		break;
		case 'C':
		case 'c':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		gtd=GPIOC;
		break;
		case 'D':
		case 'd':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
		gtd=GPIOD;
		break;
		case 'E':
		case 'e':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
		gtd=GPIOE;
		break;
		case 'F':
		case 'f':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
		gtd=GPIOF;
		break;
		case 'G':
		case 'g':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
		gtd=GPIOG;
		break;
	}
	colio[colcount].id=GPIO_Pin;
	colio[colcount++].word=io;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //???????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(gtd, &GPIO_InitStructure);//???row
}
void init_io_out(char io, uint16_t GPIO_Pin){
	GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_TypeDef * gtd;

	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin;
	
	switch(io){
		case 'A':
		case 'a':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
			gtd=GPIOA;
			break;
		case 'B':
		case 'b':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		gtd=GPIOB;
		break;
		case 'C':
		case 'c':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		gtd=GPIOC;
		break;
		case 'D':
		case 'd':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
		gtd=GPIOD;
		break;
		case 'E':
		case 'e':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
		gtd=GPIOE;
		break;
		case 'F':
		case 'f':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
		gtd=GPIOF;
		break;
		case 'G':
		case 'g':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
		gtd=GPIOG;
		break;
	}
	rowio[rowcount].id=GPIO_Pin;
	rowio[rowcount++].word=io;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //???????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(gtd, &GPIO_InitStructure);//???row
	GPIO_ResetBits(gtd,GPIO_Pin);
}
