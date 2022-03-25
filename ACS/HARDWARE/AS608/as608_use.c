#include "as608_use.h"
#include "as608.h"
#include "lcd.h"
#include "delay.h"
#include "keyboard.h"
#include "beep.h"
#include "servo.h"                                     


SysPara AS608Para;//ָ��ģ��AS608����
u16 ValidN;//ģ������Чָ�Ƹ���


//��ʾȷ���������Ϣ
void ShowErrMessage(u8 ensure)
{
	LCD_Fill(0,0,lcddev.width,139,WHITE);
	LCD_ShowString(20,80,240,16,16,(u8*)EnsureMessage(ensure));
}
//¼ָ��
 void Add_FR(void)
{
	u8 i,ensure ,processnum=0;
	u16 ID;
	Load_Keyboard(0,170);
	while(1)
	{
		switch (processnum)
		{
			case 0:
				i++;
				LCD_Fill(0,0,lcddev.width,139,WHITE);
				LCD_ShowString(20,80,240,16,16,(u8*)"Please press");
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{
					BEEP=1;
					ensure=PS_GenChar(CharBuffer1);//��������
					BEEP=0;
					if(ensure==0x00)
					{
						LCD_Fill(0,0,lcddev.width,139,WHITE);
						LCD_ShowString(20,80,240,16,16,(u8*)"Normal fingerprint");
						i=0;
						processnum=1;//�����ڶ���						
					}else ShowErrMessage(ensure);				
				}else ShowErrMessage(ensure);						
				break;
			
			case 1:
				i++;
				LCD_Fill(0,0,lcddev.width,139,WHITE);
			  LCD_ShowString(20,80,240,16,16,(u8*)"Please press again");
				ensure=PS_GetImage();
				if(ensure==0x00) 
				{
					BEEP=1;
					ensure=PS_GenChar(CharBuffer2);//��������
					BEEP=0;
					if(ensure==0x00)
					{
						LCD_Fill(0,0,lcddev.width,139,WHITE);
						LCD_ShowString(20,80,240,16,16,(u8*)"Normal fingerprint");
						i=0;
						processnum=2;//����������
					}else ShowErrMessage(ensure);	
				}else ShowErrMessage(ensure);		
				break;

			case 2:
				LCD_Fill(0,0,lcddev.width,139,WHITE);
				LCD_ShowString(20,80,240,16,16,(u8*)"Contrast fingerprint");
				ensure=PS_Match();
				if(ensure==0x00) 
				{
					LCD_Fill(0,0,lcddev.width,139,WHITE);
					LCD_ShowString(20,80,240,16,16,(u8*)"Success,sameFingerprint");
					processnum=3;//�������Ĳ�
				}
				else 
				{
					LCD_Fill(0,0,lcddev.width,139,WHITE);
					LCD_ShowString(20,80,240,16,16,(u8*)"Error, please re-enter");
					ShowErrMessage(ensure);
					i=0;
					processnum=0;//���ص�һ��		
				}
				delay_ms(1200);
				break;

			case 3:
				LCD_Fill(0,0,lcddev.width,139,WHITE);
				LCD_ShowString(20,80,240,16,16,(u8*)"Create fingerprint templates");
				ensure=PS_RegModel();
				if(ensure==0x00) 
				{
					LCD_Fill(0,0,lcddev.width,139,WHITE);
					LCD_ShowString(20,80,240,16,16,(u8*)"Success");
					processnum=4;//�������岽
				}else {processnum=0;ShowErrMessage(ensure);}
				delay_ms(1200);
				break;
				
			case 4:	
				LCD_Fill(0,0,lcddev.width,139,WHITE);
				LCD_ShowString(20,80,240,16,16,(u8*)"Please enter ID");
				LCD_ShowString(20,100,240,16,16,(u8*)"0=< ID <=299");
				do{
					ID=GET_NUM();//��ȡ��ֵ
					if(ID==0xffff) ID=Password[1];
				}
				while(!(ID<AS608Para.PS_max));//����ID����С��ָ�����������ֵ
				ensure=PS_StoreChar(CharBuffer2,ID);//����ģ��
				if(ensure==0x00) 
				{			
					LCD_Fill(0,0,lcddev.width,139,WHITE);					
					LCD_ShowString(20,80,240,16,16,(u8*)"Fingerprinting successful");
					PS_ValidTempleteNum(&ValidN);//����ָ�Ƹ���
					LCD_ShowNum(56,100,AS608Para.PS_max-ValidN,3,16);
					delay_ms(1500);
					LCD_Fill(0,0,240,139,WHITE);
					return ;
				}else {processnum=0;ShowErrMessage(ensure);}					
				break;				
		}
		delay_ms(400);
		if(i==5)//����5��û�а���ָ���˳�
		{
			LCD_Fill(0,0,lcddev.width,139,WHITE);
			break;	
		}				
	}
}

//ˢָ��
void press_FR(void)
{
	SearchResult seach;
	u8 ensure;
	//char *str;
	ensure=PS_GetImage();
	if(ensure==0x00)//��ȡͼ��ɹ� 
	{	
		BEEP=1;//�򿪷�����	
		ensure=PS_GenChar(CharBuffer1);
		if(ensure==0x00) //���������ɹ�
		{		
			BEEP=0;//�رշ�����	
			ensure=PS_HighSpeedSearch(CharBuffer1,0,AS608Para.PS_max,&seach);
			if(ensure==0x00)//�����ɹ�
			{				
				LCD_Fill(0,0,lcddev.width,139,WHITE);
				LCD_ShowString(20,80,240,16,16,(u8*)"Fingerprinting successful");	
//				str=mymalloc(SRAMIN,50);
//				sprintf(str,"ID:%d ",seach.pageID);
//				LCD_ShowString(20,120,240,16,16,(u8*)str);	
//				myfree(SRAMIN,str);
				ServoControl(180);
			}
			else 
				ShowErrMessage(ensure);					
	  }
		else
			ShowErrMessage(ensure);
	 BEEP=0;//�رշ�����
	 delay_ms(600);
	 LCD_Fill(0,0,lcddev.width,139,WHITE);
	}
		
}

//ɾ��ָ��
void Del_FR(void)
{
	u8  ensure;
	u16 num;
	LCD_Fill(0,0,lcddev.width,139,WHITE);
	delay_ms(50);
	Load_Keyboard(0,170);
	DelFingerMenu(1);
	num=GET_NUM();//��ȡ���ص���ֵ
	if(num==0xff00)
		goto MENU ; //������ҳ��
	else if(num==0xffff)
	{
		num=Password[1];
		if(num==2) ensure=PS_Empty();//���ָ�ƿ�
		else if(num==1)
		{
			LCD_Fill(0,0,lcddev.width,139,WHITE);
			DelFingerMenu(0);
			num=GET_NUM();//��ȡ���ص���ֵ
			if(num==0xffff)
			{
				num=Password[1];
				ensure=PS_DeletChar(num,1);//ɾ������ָ��
			}
			else if(num==0xff00) goto MENU ; //������ҳ��
		}
		
	}
	if(ensure==0)
	{
		LCD_Clear(WHITE);
		LCD_Fill(0,0,lcddev.width,139,WHITE);
		LCD_ShowString(20,80,240,16,16,(u8*)"Deleted successfully");		
	}
  else
		ShowErrMessage(ensure);	
	delay_ms(1200);
	PS_ValidTempleteNum(&ValidN);//����ָ�Ƹ���
	LCD_ShowNum(56,80,AS608Para.PS_max-ValidN,3,16);
MENU:	
	//LCD_Fill(0,0,lcddev.width,139,WHITE); 
	LCD_Clear(WHITE);
	delay_ms(50);
	MainMenu();
	Load_Keyboard(0,170);
}


