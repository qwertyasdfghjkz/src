#ifndef _BOARD_H_
#define _BOARD_H_

/*
*****************************************************************
*         ������ͷ�ļ�
*****************************************************************
*/

/*stme32 �̼����ļ�*/

#include "stm32f10x.h"

/* ������Ӳ��bspͷ�ļ�*/
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "keyboard.h"
#include "touch.h"
#include "beep.h"
#include "as608.h"
#include "as608_use.h"
#include "usart2.h"
#include "servo.h"
#include "rc522_function.h"
#include "rc522_config.h"



/*
*****************************************************************
*         ��������
*****************************************************************
*/


void rt_hw_board_init(void);
void SysTick_Handler(void);


#endif /*  _BOARD_H_*/

