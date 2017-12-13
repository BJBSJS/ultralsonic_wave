#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "gpio.h"
#include "timer.h"
#include "dma.h"

#define SEND_BUF_SIZE 2000	//发送数据长度
u16 SendBuff[SEND_BUF_SIZE];	//发送数据缓冲区
 
extern int flag;

int i,j,k;

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
  GPIO_OUT_Init();				//初始化GPIO
	TIM11_PWM_Init(20-1,42-1);	//168M/42=4Mhz的计数频率,重装载值20，所以PWM频率为 4M/20=200Khz. 
	TIM_SetCompare1(TIM11,10);
	TIM10_PWM_Init(20-1,42-1);	//168M/42=4Mhz的计数频率,重装载值20，所以PWM频率为 4M/20=200Khz.
  TIM_SetCompare1(TIM10,10);	
	delay_init(168);  //初始化延时函数
	
 	TIM3_Int_Init(100-1,84-1);	//定时器时钟84M，分频系数84，所以84M/84=1MHz的计数频率，计数100次为100us    
	delay_ms(3);
	TIM4_Int_Init(100-1,84-1);	//定时器时钟84M，分频系数84，所以84M/84=1MHz的计数频率，计数100次为100us
	uart_init(115200);//初始化串口波特率为115200
	GPIO_INPUT_Init();				//初始化GPIO
	MYDMA_Config(DMA2_Stream7,DMA_Channel_4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA2,STEAM7,CH4,外设为串口1,存储器为SendBuff,长度为:SEND_BUF_SIZE.
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //使能串口1的DMA发�
	while(1)
	{

		if(flag == 1)
		{
//			MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //开始一次DMA传输
			printf("通道一数据为： \r\n");					
			for(i=0;i < SEND_BUF_SIZE;i++)
			{
				SendBuff[i] = ((uint16_t)GPIOB->IDR) & 0x1FFF;
//				printf("%d\r\n",(GPIO_ReadInputData(GPIOB))&0x1FFF);
			}
			
		}
		else if(flag == 2)
		{
//			MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //开始一次DMA传输			
			printf("通道二数据为： \r\n");
			for(j=0;j < SEND_BUF_SIZE;j++)
			{
				SendBuff[j] = ((uint16_t)GPIOC->IDR) & 0x1FFF;
				printf("%d\r\n",SendBuff[i]);				
			}
		}
//		else
//		{
//			printf("There is no value now!!!");
//		}
//		USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //使能串口1的DMA发送
//		MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //开始一次DMA传输
//		for(k=0;k < SEND_BUF_SIZE;k++)
//		{
//			printf("%d\r\n",SendBuff[k]);
//		}	
	}
}
