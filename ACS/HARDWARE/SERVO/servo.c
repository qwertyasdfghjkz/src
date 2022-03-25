#include "servo.h"

////			if(t==0)
////			TIM_SetCompare4(TIMx,180);//旋转135度，模拟开门
////			else
////			TIM_SetCompare4(TIMx,195);//旋转0度，模拟关门	
////			t=!t;


void Servo_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(Servo_GPIO_CLK|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(TIMx_CLK, ENABLE);

	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Pin=Servo_GPIO_PIN;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(Servo_GPIO_PORT,&GPIO_InitStrue);
	
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure); 
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;//选择定时器输出模式PWM2
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High; //设置有效为高电平
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//使能输出引脚
	TIM_OC4Init(TIMx,&TIM_OCInitStructure);//初始化定时器4 
	
	TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);//使能预装载寄存器
	TIM_Cmd(TIMx,ENABLE);//开启定时器
		TIM_SetCompare4(TIMx,195);
}

//控制舵机
//输入参数：195旋转0度
//					180旋转135度
//返回值：无
void ServoControl(u8 n)
{
	TIM_SetCompare4(TIMx,n);

}

