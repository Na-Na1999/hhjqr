#include "sys.h"
#include "usart.h"
#include "dma.h"
#include "oled.h"

void handleUart3(){
		if(USART2_RX_BUF[0])    //数组0有数据了，说明DMA开始接收一段数据
		{
			OLED_ShowStr(0,0,USART2_RX_BUF,0);
			
				memset(USART2_RX_BUF,0,200);    //清空数组
				MYDMA_Enable(DMA1_Channel3,200);//开始一次DMA传输！

		
			
			
		}
}