#ifndef __DMA_H
#define __DMA_H	 
#include "sys.h"
#include "stm32f10x_dma.h"
#define ARRLEN 11
extern u8 USART2_RX_BUF[];
extern int a;
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx,u16 reloadlen);
void MYDMA_Config(USART_TypeDef * uart,DMA_Channel_TypeDef* DMA_CHx,u32 cmar,u16 cndtr);
void MYDMA_Config2(USART_TypeDef * uart,DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);
 void handledma();
#endif