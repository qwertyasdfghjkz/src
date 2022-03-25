#ifndef _BOARD_H_
#define _BOARD_H_

/*
*****************************************************************
*         包含的头文件
*****************************************************************
*/

/*stme32 固件库文件*/

#include "stm32f10x.h"

/* 开发板硬件bsp头文件*/
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
*         函数声明
*****************************************************************
*/


void rt_hw_board_init(void);
void SysTick_Handler(void);


#endif /*  _BOARD_H_*/

