#ifndef __GPIO_H
#define __GPIO_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//PWM�˿ڶ���
#define PWM1 PFout(5)	// 
#define PWM2 PFout(6)	// 
#define PWM3 PFout(7)	// 
#define PWM4 PFout(8)	// 
//LED�˿ڶ���
#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	 


void GPIOS_Init(void);//��ʼ��		 				    
#endif
