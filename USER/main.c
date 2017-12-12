#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "gpio.h"
#include "timer.h"
#include "dma.h"

#define SEND_BUF_SIZE 8000	//�������ݳ���,��õ���sizeof(TEXT_TO_SEND)+2��������.
u16 SendBuff[SEND_BUF_SIZE];	//�������ݻ�����

extern int flag;

int i,j;

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
 	GPIOS_Init();				//��ʼ��GPIO
	TIM13_PWM_Init(10-1,42-1);	//84M/42=2Mhz�ļ���Ƶ��,��װ��ֵ10������PWMƵ��Ϊ 2M/10=200Khz. 
	TIM14_PWM_Init(10-1,42-1);	//84M/42=2Mhz�ļ���Ƶ��,��װ��ֵ10������PWMƵ��Ϊ 2M/10=200Khz. 
	
 	TIM3_Int_Init(100-1,84-1);	//��ʱ��ʱ��84M����Ƶϵ��84������84M/84=1MHz�ļ���Ƶ�ʣ�����100��Ϊ100us    
	delay_ms(3);
	TIM4_Int_Init(100-1,84-1);	//��ʱ��ʱ��84M����Ƶϵ��84������84M/84=1MHz�ļ���Ƶ�ʣ�����100��Ϊ100us
	uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
	MYDMA_Config(DMA2_Stream7,DMA_Channel_4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA2,STEAM7,CH4,����Ϊ����1,�洢��ΪSendBuff,����Ϊ:SEND_BUF_SIZE.
	
	while(1)
	{
		USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //ʹ�ܴ���1��DMA����
		if(flag == 1)
		{
			printf("ͨ��һ����Ϊ�� \r\n");
			for(i=0;i < SEND_BUF_SIZE;i++)
			{
					SendBuff[i] = (GPIO_ReadInputData(GPIOB))&0x1FFF;
			}
			MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //��ʼһ��DMA����	
		}
		else if(flag == 2)
		{
			printf("ͨ��������Ϊ�� \r\n");
			for(j=0;j < SEND_BUF_SIZE;j++)
			{
					SendBuff[j] = (GPIO_ReadInputData(GPIOC))&0x1FFF;
			}
			MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //��ʼһ��DMA����	
		}
	}
}
