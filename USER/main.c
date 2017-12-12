#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "gpio.h"
#include "timer.h"
#include "dma.h"

#define SEND_BUF_SIZE 8000	//·¢ËÍÊý¾Ý³¤¶È,×îºÃµÈÓÚsizeof(TEXT_TO_SEND)+2µÄÕûÊý±¶.
u16 SendBuff[SEND_BUF_SIZE];	//·¢ËÍÊý¾Ý»º³åÇø

extern int flag;

int i,j;

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ÉèÖÃÏµÍ³ÖÐ¶ÏÓÅÏÈ¼¶·Ö×é2
	delay_init(168);  //³õÊ¼»¯ÑÓÊ±º¯Êý
 	GPIOS_Init();				//³õÊ¼»¯GPIO
	TIM13_PWM_Init(10-1,42-1);	//84M/42=2MhzµÄ¼ÆÊýÆµÂÊ,ÖØ×°ÔØÖµ10£¬ËùÒÔPWMÆµÂÊÎª 2M/10=200Khz. 
	TIM14_PWM_Init(10-1,42-1);	//84M/42=2MhzµÄ¼ÆÊýÆµÂÊ,ÖØ×°ÔØÖµ10£¬ËùÒÔPWMÆµÂÊÎª 2M/10=200Khz. 
	
 	TIM3_Int_Init(100-1,84-1);	//¶¨Ê±Æ÷Ê±ÖÓ84M£¬·ÖÆµÏµÊý84£¬ËùÒÔ84M/84=1MHzµÄ¼ÆÊýÆµÂÊ£¬¼ÆÊý100´ÎÎª100us    
	delay_ms(3);
	TIM4_Int_Init(100-1,84-1);	//¶¨Ê±Æ÷Ê±ÖÓ84M£¬·ÖÆµÏµÊý84£¬ËùÒÔ84M/84=1MHzµÄ¼ÆÊýÆµÂÊ£¬¼ÆÊý100´ÎÎª100us
	uart_init(115200);//³õÊ¼»¯´®¿Ú²¨ÌØÂÊÎª115200
	MYDMA_Config(DMA2_Stream7,DMA_Channel_4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA2,STEAM7,CH4,ÍâÉèÎª´®¿Ú1,´æ´¢Æ÷ÎªSendBuff,³¤¶ÈÎª:SEND_BUF_SIZE.
	
	while(1)
	{
		USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //Ê¹ÄÜ´®¿Ú1µÄDMA·¢ËÍ
		if(flag == 1)
		{
			printf("Í¨µÀÒ»Êý¾ÝÎª£º \r\n");
			for(i=0;i < SEND_BUF_SIZE;i++)
			{
					SendBuff[i] = (GPIO_ReadInputData(GPIOB))&0x1FFF;
			}
			MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //¿ªÊ¼Ò»´ÎDMA´«Êä£	
		}
		else if(flag == 2)
		{
			printf("Í¨µÀ¶þÊý¾ÝÎª£º \r\n");
			for(j=0;j < SEND_BUF_SIZE;j++)
			{
					SendBuff[j] = (GPIO_ReadInputData(GPIOC))&0x1FFF;
			}
			MYDMA_Enable(DMA2_Stream7,SEND_BUF_SIZE);     //¿ªÊ¼Ò»´ÎDMA´«Êä£	
		}
	}
}
