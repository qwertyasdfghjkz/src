#ifndef _SERVO_H
#define _SERVO_H

#include "sys.h"

#define TIMx							TIM4
#define TIMx_CLK					RCC_APB1Periph_TIM4

#define Servo_GPIO_CLK		RCC_APB2Periph_GPIOB
#define Servo_GPIO_PORT		GPIOB
#define Servo_GPIO_PIN		GPIO_Pin_9


void Servo_Init(u16 arr,u16 psc);
void ServoControl(u8 n);

#endif
