#include "dma.h"

int test=0;

u8 USART2_RX_BUF[ARRLEN];
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx,u16 reloadlen)
{ 
DMA_Cmd(DMA_CHx, DISABLE ); //�ر�USART1 TX DMA1 ��ָʾ��ͨ�� 
DMA_SetCurrDataCounter(DMA_CHx,reloadlen);//�������û����С,ָ������0
DMA_Cmd(DMA_CHx, ENABLE); //ʹ��USART1 TX DMA1 ��ָʾ��ͨ�� 
}
void MYDMA_Config2(USART_TypeDef * uart,DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);    //ʹ��DMA����
	DMA_DeInit(DMA_CHx); //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar; //DMA�������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar; //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	DMA_InitStructure.DMA_BufferSize = cndtr; //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //����������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA_CHx, &DMA_InitStructure); //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Rx_DMA ����ʶ�ļĴ���
	USART_Cmd(uart, ENABLE); //ʹ�ܴ���1 
	DMA_Cmd(DMA_CHx, ENABLE); //ʹ��USART1 TX DMA1 ��ָʾ��ͨ�� 
	MYDMA_Enable(DMA_CHx,cndtr);//��ʼһ��DMA���䣡
}
void MYDMA_Config(USART_TypeDef * uart,DMA_Channel_TypeDef* DMA_CHx,u32 cmar,u16 cndtr)
{
	DMA_InitTypeDef DMA_InitStructure;
	u32 cpar=(u32)&uart->DR;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);    //ʹ��DMA����
	{
  NVIC_InitTypeDef NVIC_InitStructure;     /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);     
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;     
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;          
  NVIC_Init(&NVIC_InitStructure);
}
	DMA_DeInit(DMA_CHx); //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar; //DMA�������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar; //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	DMA_InitStructure.DMA_BufferSize = cndtr; //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //����������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA_CHx, &DMA_InitStructure); //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Rx_DMA ����ʶ�ļĴ���
	USART_Cmd(uart, ENABLE); //ʹ�ܴ���1 
	DMA_ITConfig(DMA_CHx,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA_CHx, ENABLE); //ʹ��USART1 TX DMA1 ��ָʾ��ͨ�� 
	MYDMA_Enable(DMA_CHx,cndtr);//��ʼһ��DMA���䣡
}

void DMA1_Channel5_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC5))
    {
			a=0;
			handledma();
			//MYDMA_Enable(DMA1_Channel5,ARRLEN);
        DMA_ClearITPendingBit(DMA1_IT_GL5); //���ȫ���жϱ�־
    }
}