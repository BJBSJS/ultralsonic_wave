#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "gpio.h"
#include "timer.h"
#include "dma.h"

#define SEND_BUF_SIZE 2000	//�������ݳ���
u16 SendBuff[SEND_BUF_SIZE];	//�������ݻ�����
 
extern int flag;

int i,j,k;

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
  GPIO_OUT_Init();				//��ʼ��GPIO
	TIM11_PWM_Init(20-1,42-1);	//168M/42=4Mhz�ļ���Ƶ��,��װ��ֵ20������PWMƵ��Ϊ 4M/20=200Khz. 
	TIM_SetCompare1(TIM11,10);
	TIM10_PWM_Init(20-1,42-1);	//168M/42=4Mhz�ļ���Ƶ��,��װ��ֵ20������PWMƵ��Ϊ 4M/20=200Khz.
  TIM_SetCompare1(TIM10,10);	
	delay_init(168);  //��ʼ����ʱ����
	
 	TIM3_Int_Init(100-1,84-1);	//��ʱ��ʱ��84M����Ƶϵ��84������84M/84=1MHz�ļ���Ƶ�ʣ�����100��Ϊ100us    
	delay_ms(3);
	TIM4_Int_Init(100-1,84-1);	//��ʱ��ʱ��84M����Ƶϵ��84������84M/84=1MHz�ļ���Ƶ�ʣ�����100��Ϊ100us
	uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
	GPIO_INPUT_Init();				//��ʼ��GPIO
	MYDMA_Config(DMA2_Stream7,DMA_Channel_4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA2,STEAM7,CH4,����Ϊ����1,�洢��ΪSendBuff,����Ϊ:SEND_BUF_SIZE.
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //ʹ�ܴ���1��DMA���
	while(1)
	{

		if(flag == 1)
		{
//			MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //��ʼһ��DMA����
			printf("ͨ��һ����Ϊ�� \r\n");					
			for(i=0;i < SEND_BUF_SIZE;i++)
			{
				SendBuff[i] = ((uint16_t)GPIOB->IDR) & 0x1FFF;
//				printf("%d\r\n",(GPIO_ReadInputData(GPIOB))&0x1FFF);
			}
			
		}
		else if(flag == 2)
		{
//			MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //��ʼһ��DMA����			
			printf("ͨ��������Ϊ�� \r\n");
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
//		USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //ʹ�ܴ���1��DMA����
//		MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //��ʼһ��DMA����
//		for(k=0;k < SEND_BUF_SIZE;k++)
//		{
//			printf("%d\r\n",SendBuff[k]);
//		}	
	}
}
