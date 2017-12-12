#ifndef _ACQU_H
#define _ACQU_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/6/16
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
extern FlagStatus flag_acqu;

void chans_acqu(void);
void chan1_acqu(uint16_t* data);
void chan2_acqu(uint16_t* data);
//float data_to_value(uint16_t data);
void print_chan_data(uint16_t* data);
#endif
