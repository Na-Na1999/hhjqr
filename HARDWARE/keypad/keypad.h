#ifndef __keypad_H
#define __keypad_H

#include "sys.h"
typedef struct{
	u8 word;
	uint16_t id;
}IO_reg;
GPIO_TypeDef* getgpiox(char gpiox);
void keyevent(int i,int j);
void keypad_Init(void);
void scankeypad();
void init_io_out(char io, uint16_t GPIO_Pin); 
void init_io_in(char io, uint16_t GPIO_Pin);
extern int key;
extern const char pw[];//={5,4,0,2,2,2};
extern char pwb[];//={0};
extern char step;
extern char keybuffer[];
extern char keybufferlen;
#endif