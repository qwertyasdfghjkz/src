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
/************************************************
 ALIENTEK��ӢSTM32������ʵ��13
 TFTLCD��ʾʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

 int main(void)
 {	
	u8 ensure;
	u16 key_num;
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	usart2_init(57600);//��ʼ������2,������ָ��ģ��ͨѶ
	//BEEP_Init();  			//��ʼ��������
 	LED_Init();			     //LED�˿ڳ�ʼ��
	Servo_Init(199,7199);//�����ʼ������ʱ�����PWM
	LCD_Init();
	tp_dev.init();	
	 
  RC522_Init ();/*RC522ģ����������ĳ�ʼ������*/
	PcdReset ();
	M500PcdConfigISOType ( 'A' );/*���ù�����ʽ*/ 
	 
	/*����ָ��ʶ�����*/
	LCD_Clear(WHITE);
	POINT_COLOR=RED;			    	 
 	POINT_COLOR=BLUE;
	LCD_ShowString(0,40,240,16,16,(u8*)"Connect with AS608...");	
	while(PS_HandShake(&AS608Addr))
	 {
		 LCD_Clear(WHITE);
		 LCD_ShowString(0,40,240,16,16,(u8*)" AS608 Error");	
	 }//��AS608ģ������
	ensure=PS_ValidTempleteNum(&ValidN);//����ָ�Ƹ���
	if(ensure!=0x00) ShowErrMessage(ensure);//��ʾȷ���������Ϣ	
	ensure=PS_ReadSysPara(&AS608Para);  //������ 
	
	LCD_Clear(WHITE);
	Load_Keyboard(0,170);//�����������
	while(1)
	{
		MainMenu();//���˵�
		key_num=Get_KeyNumber(0,170);	
		if(key_num)
		{
			if(key_num==1)Unlock();		//����
			if(key_num==2)Add_FR();		//¼ָ��		
			if(key_num==3)Del_FR();		//ɾָ��
			if(key_num==4)Add_IC_Card();		//���IC
			if(key_num==5)Del_IC_Card();		//ɾ��IC
			if(key_num==6)ServoControl(195);		//�޸�����							
		}
		if(PS_Sta)	 //���PS_Sta״̬���������ָ����
		{
			press_FR();//ˢָ��			
		}	
		Verify_IC_Card();
	} 	
}	 


