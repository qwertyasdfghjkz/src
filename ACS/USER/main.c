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
 ALIENTEK精英STM32开发板实验13
 TFTLCD显示实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

 int main(void)
 {	
	u8 ensure;
	u16 key_num;
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为115200
	usart2_init(57600);//初始化串口2,用于与指纹模块通讯
	//BEEP_Init();  			//初始化蜂鸣器
 	LED_Init();			     //LED端口初始化
	Servo_Init(199,7199);//舵机初始化，定时器输出PWM
	LCD_Init();
	tp_dev.init();	
	 
  RC522_Init ();/*RC522模块所需外设的初始化配置*/
	PcdReset ();
	M500PcdConfigISOType ( 'A' );/*设置工作方式*/ 
	 
	/*加载指纹识别界面*/
	LCD_Clear(WHITE);
	POINT_COLOR=RED;			    	 
 	POINT_COLOR=BLUE;
	LCD_ShowString(0,40,240,16,16,(u8*)"Connect with AS608...");	
	while(PS_HandShake(&AS608Addr))
	 {
		 LCD_Clear(WHITE);
		 LCD_ShowString(0,40,240,16,16,(u8*)" AS608 Error");	
	 }//与AS608模块握手
	ensure=PS_ValidTempleteNum(&ValidN);//读库指纹个数
	if(ensure!=0x00) ShowErrMessage(ensure);//显示确认码错误信息	
	ensure=PS_ReadSysPara(&AS608Para);  //读参数 
	
	LCD_Clear(WHITE);
	Load_Keyboard(0,170);//加载虚拟键盘
	while(1)
	{
		MainMenu();//主菜单
		key_num=Get_KeyNumber(0,170);	
		if(key_num)
		{
			if(key_num==1)Unlock();		//解锁
			if(key_num==2)Add_FR();		//录指纹		
			if(key_num==3)Del_FR();		//删指纹
			if(key_num==4)Add_IC_Card();		//添加IC
			if(key_num==5)Del_IC_Card();		//删除IC
			if(key_num==6)ServoControl(195);		//修改密码							
		}
		if(PS_Sta)	 //检测PS_Sta状态，如果有手指按下
		{
			press_FR();//刷指纹			
		}	
		Verify_IC_Card();
	} 	
}	 


