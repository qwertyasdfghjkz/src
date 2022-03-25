#include "servo.h"

////			if(t==0)
////			TIM_SetCompare4(TIMx,180);//��ת135�ȣ�ģ�⿪��
////			else
////			TIM_SetCompare4(TIMx,195);//��ת0�ȣ�ģ�����	
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
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;//ѡ��ʱ�����ģʽPWM2
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High; //������ЧΪ�ߵ�ƽ
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//ʹ���������
	TIM_OC4Init(TIMx,&TIM_OCInitStructure);//��ʼ����ʱ��4 
	
	TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);//ʹ��Ԥװ�ؼĴ���
	TIM_Cmd(TIMx,ENABLE);//������ʱ��
		TIM_SetCompare4(TIMx,195);
}

//���ƶ��
//���������195��ת0��
//					180��ת135��
//����ֵ����
void ServoControl(u8 n)
{
	TIM_SetCompare4(TIMx,n);

}

