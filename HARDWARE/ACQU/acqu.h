#ifndef _ACQU_H
#define _ACQU_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/6/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
extern FlagStatus flag_acqu;

void chans_acqu(void);
void chan1_acqu(uint16_t* data);
void chan2_acqu(uint16_t* data);
//float data_to_value(uint16_t data);
void print_chan_data(uint16_t* data);
#endif
