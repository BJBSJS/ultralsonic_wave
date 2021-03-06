#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "gpio.h"
#include "timer.h"
#include "dma.h"

#define SEND_BUF_SIZE 8000	//发送数据长度,最好等于sizeof(TEXT_TO_SEND)+2的整数倍.
u16 SendBuff[SEND_BUF_SIZE];	//发送数据缓冲区

extern int flag;

int i,j;

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
 	GPIOS_Init();				//初始化GPIO
	TIM13_PWM_Init(10-1,42-1);	//84M/42=2Mhz的计数频率,重装载值10，所以PWM频率为 2M/10=200Khz. 
	TIM14_PWM_Init(10-1,42-1);	//84M/42=2Mhz的计数频率,重装载值10，所以PWM频率为 2M/10=200Khz. 
	
 	TIM3_Int_Init(100-1,84-1);	//定时器时钟84M，分频系数84，所以84M/84=1MHz的计数频率，计数100次为100us    
	delay_ms(3);
	TIM4_Int_Init(100-1,84-1);	//定时器时钟84M，分频系数84，所以84M/84=1MHz的计数频率，计数100次为100us
	uart_init(115200);//初始化串口波特率为115200
	MYDMA_Config(DMA2_Stream7,DMA_Channel_4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA2,STEAM7,CH4,外设为串口1,存储器为SendBuff,长度为:SEND_BUF_SIZE.
	
	while(1)
	{
		USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //使能串口1的DMA发送
		if(flag == 1)
		{
			printf("通道一数据为： \r\n");
			for(i=0;i < SEND_BUF_SIZE;i++)
			{
					SendBuff[i] = (GPIO_ReadInputData(GPIOB))&0x1FFF;
			}
			MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //开始一次DMA传输�	
		}
		else if(flag == 2)
		{
			printf("通道二数据为： \r\n");
			for(j=0;j < SEND_BUF_SIZE;j++)
			{
					SendBuff[j] = (GPIO_ReadInputData(GPIOC))&0x1FFF;
			}
			MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //开始一次DMA传输�	
		}
	}
}
