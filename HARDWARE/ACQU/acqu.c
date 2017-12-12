#include "acqu.h"
#include "usart.h"
#include "dma.h"

u16 chan1[8000];
u16 chan2[8000];




void chans_acqu(void)
{
			if(flag_acqu == SET)
			{
				chan1_acqu(chan1);	
			}
			else if(flag_acqu == RESET)
			{
				chan2_acqu(chan2);
			}
}

void chan1_acqu(uint16_t* data)		
{
			u32 i;
			uint16_t ch1; 
			for(i = 0 ;i < 8000;i++)
			{
					ch1 = GPIO_ReadInputData(GPIOB);
					ch1 = ch1&0x1FFF;
					data[i] = ch1;
			}
}

void chan2_acqu(uint16_t* data)		
{
		  u32 i;
	    uint16_t ch2;
			for(i = 0 ;i < 8000;i++)
			{
					ch2 = GPIO_ReadInputData(GPIOC);
					ch2 = ch2&0x1FFF;
					data[i] = ch2;
			}
}




