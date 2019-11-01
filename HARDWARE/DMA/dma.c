#include "dma.h"

int test=0;

u8 USART2_RX_BUF[ARRLEN];
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx,u16 reloadlen)
{ 
DMA_Cmd(DMA_CHx, DISABLE ); //关闭USART1 TX DMA1 所指示的通道 
DMA_SetCurrDataCounter(DMA_CHx,reloadlen);//从新设置缓冲大小,指向数组0
DMA_Cmd(DMA_CHx, ENABLE); //使能USART1 TX DMA1 所指示的通道 
}
void MYDMA_Config2(USART_TypeDef * uart,DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);    //使能DMA传输
	DMA_DeInit(DMA_CHx); //将DMA的通道1寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar; //DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar; //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //数据传输方向，从内存读取发送到外设
	DMA_InitStructure.DMA_BufferSize = cndtr; //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //工作在正常模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA_CHx, &DMA_InitStructure); //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Rx_DMA 所标识的寄存器
	USART_Cmd(uart, ENABLE); //使能串口1 
	DMA_Cmd(DMA_CHx, ENABLE); //使能USART1 TX DMA1 所指示的通道 
	MYDMA_Enable(DMA_CHx,cndtr);//开始一次DMA传输！
}
void MYDMA_Config(USART_TypeDef * uart,DMA_Channel_TypeDef* DMA_CHx,u32 cmar,u16 cndtr)
{
	DMA_InitTypeDef DMA_InitStructure;
	u32 cpar=(u32)&uart->DR;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);    //使能DMA传输
	{
  NVIC_InitTypeDef NVIC_InitStructure;     /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);     
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;     
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;          
  NVIC_Init(&NVIC_InitStructure);
}
	DMA_DeInit(DMA_CHx); //将DMA的通道1寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar; //DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar; //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //数据传输方向，从内存读取发送到外设
	DMA_InitStructure.DMA_BufferSize = cndtr; //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //工作在正常模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA_CHx, &DMA_InitStructure); //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Rx_DMA 所标识的寄存器
	USART_Cmd(uart, ENABLE); //使能串口1 
	DMA_ITConfig(DMA_CHx,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA_CHx, ENABLE); //使能USART1 TX DMA1 所指示的通道 
	MYDMA_Enable(DMA_CHx,cndtr);//开始一次DMA传输！
}

void DMA1_Channel5_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC5))
    {
			a=0;
			handledma();
			//MYDMA_Enable(DMA1_Channel5,ARRLEN);
        DMA_ClearITPendingBit(DMA1_IT_GL5); //清除全部中断标志
    }
}