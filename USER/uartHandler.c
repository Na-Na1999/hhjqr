#include "sys.h"
#include "usart.h"
#include "dma.h"
#include "oled.h"

void handleUart3(){
		if(USART2_RX_BUF[0])    //����0�������ˣ�˵��DMA��ʼ����һ������
		{
			OLED_ShowStr(0,0,USART2_RX_BUF,0);
			
				memset(USART2_RX_BUF,0,200);    //�������
				MYDMA_Enable(DMA1_Channel3,200);//��ʼһ��DMA���䣡

		
			
			
		}
}