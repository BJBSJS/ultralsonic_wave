#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "gpio.h"
#include "timer.h"
#include "dma.h"

#define SEND_BUF_SIZE 2000	//·¢ËÍÊý¾Ý³¤¶È
u16 SendBuff[SEND_BUF_SIZE];	//·¢ËÍÊý¾Ý»º³åÇø
 
extern int flag;

int i,j,k;

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ÉèÖÃÏµÍ³ÖÐ¶ÏÓÅÏÈ¼¶·Ö×é2
  GPIO_OUT_Init();				//³õÊ¼»¯GPIO
	TIM11_PWM_Init(20-1,42-1);	//168M/42=4MhzµÄ¼ÆÊýÆµÂÊ,ÖØ×°ÔØÖµ20£¬ËùÒÔPWMÆµÂÊÎª 4M/20=200Khz. 
	TIM_SetCompare1(TIM11,10);
	TIM10_PWM_Init(20-1,42-1);	//168M/42=4MhzµÄ¼ÆÊýÆµÂÊ,ÖØ×°ÔØÖµ20£¬ËùÒÔPWMÆµÂÊÎª 4M/20=200Khz.
  TIM_SetCompare1(TIM10,10);	
	delay_init(168);  //³õÊ¼»¯ÑÓÊ±º¯Êý
	
 	TIM3_Int_Init(100-1,84-1);	//¶¨Ê±Æ÷Ê±ÖÓ84M£¬·ÖÆµÏµÊý84£¬ËùÒÔ84M/84=1MHzµÄ¼ÆÊýÆµÂÊ£¬¼ÆÊý100´ÎÎª100us    
	delay_ms(3);
	TIM4_Int_Init(100-1,84-1);	//¶¨Ê±Æ÷Ê±ÖÓ84M£¬·ÖÆµÏµÊý84£¬ËùÒÔ84M/84=1MHzµÄ¼ÆÊýÆµÂÊ£¬¼ÆÊý100´ÎÎª100us
	uart_init(115200);//³õÊ¼»¯´®¿Ú²¨ÌØÂÊÎª115200
	GPIO_INPUT_Init();				//³õÊ¼»¯GPIO
	MYDMA_Config(DMA2_Stream7,DMA_Channel_4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA2,STEAM7,CH4,ÍâÉèÎª´®¿Ú1,´æ´¢Æ÷ÎªSendBuff,³¤¶ÈÎª:SEND_BUF_SIZE.
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //Ê¹ÄÜ´®¿Ú1µÄDMA·¢Ë
	while(1)
	{

		if(flag == 1)
		{
//			MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //¿ªÊ¼Ò»´ÎDMA´«Êä
			printf("Í¨µÀÒ»Êý¾ÝÎª£º \r\n");					
			for(i=0;i < SEND_BUF_SIZE;i++)
			{
				SendBuff[i] = ((uint16_t)GPIOB->IDR) & 0x1FFF;
//				printf("%d\r\n",(GPIO_ReadInputData(GPIOB))&0x1FFF);
			}
			
		}
		else if(flag == 2)
		{
//			MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //¿ªÊ¼Ò»´ÎDMA´«Êä			
			printf("Í¨µÀ¶þÊý¾ÝÎª£º \r\n");
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
//		USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //Ê¹ÄÜ´®¿Ú1µÄDMA·¢ËÍ
//		MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //¿ªÊ¼Ò»´ÎDMA´«Êä
//		for(k=0;k < SEND_BUF_SIZE;k++)
//		{
//			printf("%d\r\n",SendBuff[k]);
//		}	
	}
}
