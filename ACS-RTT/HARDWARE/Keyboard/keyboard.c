#include "keyboard.h"
#include "lcd.h"
#include "touch.h"
#include "delay.h"
#include "servo.h"
#include "rtthread.h"
//��ʼ������
u16 Password[2] = {1234, 0};
u8 bit = 0; //��ʾ����λ����־λ
static  u8  numberBit = 0; //���������־λ
u8 rootMenuFlag = 0 ;
const u8 NUMBER[12] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', '0', ' '};
const char *TEXT[5] = {"Enter", "DEL", "SET", "Clear", "Back"};


//��ʾ���̽���
//x,y���ü�����ʾ��λ�ã�x=0��y��0~170֮��
void Load_Keyboard(u16 x, u16 y)
{

    u8 i;
    POINT_COLOR = RED;
    LCD_Fill(x, y, x + 240, y + 150, WHITE);
    LCD_DrawRectangle(x, y, x + 240, y + 150);
    LCD_DrawRectangle(x + 80, y - 30, x + 160, y + 150);
    LCD_DrawRectangle(x, y - 30, x + 240, y + 150);
    LCD_DrawRectangle(x, y + 30, x + 240, y + 60);
    LCD_DrawRectangle(x, y + 90, x + 240, y + 120);
    POINT_COLOR = BLUE;

    //LCD_ShowString(30,3,240,16,16,(u8*)"Access Control System");
    //AdminInterface();
    //LCD_ShowString(50,75,46,24,24,(u8*)"PW:");
    bit = 0;
    numberBit = 0;
    SpecifyClear(85, 145, 70, 16);
    delay_ms(3);

    for( i = 0; i < 15; i++)
    {
        if(i != 9 && i != 11 && i != 12 && i != 13 && i != 14)
            LCD_ShowChar(x + (i % 3) * 80 + 32, y + 7 + 30 * (i / 3), ((u8)NUMBER[i]), 16, 0);
        else if(i == 9)
            LCD_ShowString(x + (i % 3) * 80 + 21, y + 7 + 30 * (i / 3), 80, 30, 16, (u8*)TEXT[0]);
        else if(i == 11)
            LCD_ShowString(x + (i % 3) * 80 + 30, y + 7 + 30 * (i / 3), 80, 30, 16, (u8*)TEXT[1]);
        else if(i == 12)
            LCD_ShowString(x + (i % 3) * 80 + 30, y + 7 + 30 * (i / 3), 80, 30, 16, (u8*)TEXT[2]);
        else if(i == 13)
            LCD_ShowString(x + (i % 3) * 80 + 21, y + 7 + 30 * (i / 3), 80, 30, 16, (u8*)TEXT[3]);
        else if(i == 14)
            LCD_ShowString(x + (i % 3) * 80 + 21, y + 7 + 30 * (i / 3), 80, 30, 16, (u8*)TEXT[4]);
    }
}

//�õ�������������
//x,y:��������
//����ֵ:��1~15,��Ӧ������
u8 Get_KeyNumber(u16 x, u16 y)
{
    u16 i, j;
    static u8 key_x = 0; //0,û���κΰ�������
    u8 key = 0;
    tp_dev.scan(0);

    if(tp_dev.sta & TP_PRES_DOWN) //������������
    {
        for(i = 0; i < 5; i++)
        {
            for(j = 0; j < 3; j++)
            {
                if(tp_dev.x[0] < (x + j * 80 + 80) && tp_dev.x[0] > (x + j * 80) && tp_dev.y[0] < (y + i * 30 + 30) && tp_dev.y[0] > (y + i * 30))
                {
                    key = i * 3 + j + 1;
                    break;
                }
            }

            if(key)
            {
                if(key_x == key)key = 0;
                else
                {
                    Key_Staset(x, y, key_x - 1, 0);
                    key_x = key;
                    Key_Staset(x, y, key_x - 1, 1);
                }

                break;
            }
        }
    }
    else if(key_x)
    {
        Key_Staset(x, y, key_x - 1, 0);
        key_x = 0;
    }

    return key;
}


//����״̬����
//x,y:��������
//key:��ֵ(0~14)
//sta:״̬��0���ɿ���1�����£�
void Key_Staset(u16 x, u16 y, u8 keyx, u8 sta)
{
    u8 k;
    u16 i = keyx / 3, j = keyx % 3;

    if(keyx > 16)return;

    if(sta)//
        LCD_Fill(x + j * 80 + 1, y + i * 30 + 1, x + j * 80 + 78, y + i * 30 + 28, GREEN);
    else
        LCD_Fill(x + j * 80 + 1, y + i * 30 + 1, x + j * 80 + 78, y + i * 30 + 28, WHITE);

    for( k = 0; k < 15; k++)
    {
        if(k != 9 && k != 11 && k != 12 && k != 13 && k != 14)
            LCD_ShowChar(x + (k % 3) * 80 + 32, y + 7 + 30 * (k / 3), ((u8)NUMBER[k]), 16, 1);
        else if(k == 9)
            LCD_ShowString(x + (k % 3) * 80 + 21, y + 7 + 30 * (k / 3), 80, 30, 16, (u8*)TEXT[0]);
        else if(k == 11)
            LCD_ShowString(x + (k % 3) * 80 + 30, y + 7 + 30 * (k / 3), 80, 30, 16, (u8*)TEXT[1]);
        else if(k == 12)
            LCD_ShowString(x + (k % 3) * 80 + 30, y + 7 + 30 * (k / 3), 80, 30, 16, (u8*)TEXT[2]);
        else if(k == 13)
            LCD_ShowString(x + (k % 3) * 80 + 21, y + 7 + 30 * (k / 3), 80, 30, 16, (u8*)TEXT[3]);
        else if(k == 14)
            LCD_ShowString(x + (k % 3) * 80 + 21, y + 7 + 30 * (k / 3), 80, 30, 16, (u8*)TEXT[4]);
    }

}

//��ȡ������ֵ
u16 GET_NUM(void)
{
    u8  key_num = 0;
    Password[1] = 0; //����

    while(1)
    {

        key_num = Get_KeyNumber(0, 170);

        if(key_num)
        {
            if(key_num > 0 && key_num < 10 && numberBit < 4) //��1-9����(��������3λ��)
            {
                numberBit++;
                Password[1] = Password[1] * 10 + key_num;
                bit++;
            }

            else if(key_num == 11 && numberBit < 4)
            {
                numberBit++;
                Password[1] = Password[1] * 10;
                bit++;
            }//��0����

            else if(key_num == 12 && bit != 0)
            {
                if(Password[1] > 0) Password[1] = Password[1] / 10;

                bit--;
                numberBit--;

                SpecifyClear(85, 145, 70, 16);

                LCD_ShowPassword(105, 145, Password[1], bit, 16);

            }//��Del����


            else if(key_num == 10) return 0xffff; //��Enter����
            else if(key_num == 13) return 0xfff0; // 'SET'��
            else if(key_num == 15) return 0xff00; //��back'��
            else if(key_num == 14)
            {
                numberBit = 0;
                bit = 0;
                Password[1] = 0;
                SpecifyClear(85, 145, 70, 16);
                Load_Keyboard(0, 170);
            }//Clear ��

        }

        LCD_ShowPassword(105, 145, Password[1], bit, 16);

        if(rootMenuFlag)
        {
            Menu(0);
            rootMenuFlag = 0;
        }

        rt_thread_delay(1);
    }
}

/*
* ָ���������
*  x,y���͸�
*/
void SpecifyClear(u16 x, u16 y, u16 dx, u16 dy)
{
    LCD_Fill(x, y, x + dx, y + dy, WHITE);
}


/*
*�˵�����
*
*/
void MainMenu(void)
{
    LCD_ShowString(50, 3, 240, 16, 16, (u8*)"Input 1-6 selection");

    LCD_ShowString(55, 23, 240, 16, 16, (u8*)"1.Unlock");
    LCD_ShowString(55, 43, 240, 16, 16, (u8*)"2.Add fingerprint");
    LCD_ShowString(55, 63, 240, 16, 16, (u8*)"3.Del fingerprint");
    LCD_ShowString(55, 83, 240, 16, 16, (u8*)"4.Add IC ");
    LCD_ShowString(55, 103, 240, 16, 16, (u8*)"5.Del IC ");
    LCD_ShowString(55, 123, 240, 16, 16, (u8*)"6.Change Passwd");

}

void Unlock(void)
{
    u16 key_num;
    Unlockmenu(0);
AGAIN:

    while((key_num = GET_NUM()) != 0xffff)
        Load_Keyboard(0, 170);

    if(key_num == 0xffff)
    {
        if(Password[1] == Password[0])
        {
            Load_Keyboard(0, 170);
            ServoControl(185);
            ServoFlag = 1;
        }
        else
        {
            Load_Keyboard(0, 170);
            Unlockmenu(1);
            goto AGAIN;
        }
    }

    Load_Keyboard(0, 170);
    LCD_Fill(0, 0, lcddev.width, 139, WHITE);
}



void RUserEnter( uint8_t * n)
{
    u16 key_num;
    Menu(0);
AGAIN:

    while((key_num = GET_NUM()) != 0xffff)
    {
        rt_thread_delay(1);
        Load_Keyboard(0, 170);
    }

    if(key_num == 0xffff)
    {
        if(Password[1] == Password[0])
        {
            Load_Keyboard(0, 170);
            *n = 1;
        }
        else
        {
            Load_Keyboard(0, 170);
            Menu(1);
            goto AGAIN;
        }
    }

    Load_Keyboard(0, 170);
    LCD_Fill(0, 0, lcddev.width, 139, WHITE);
}

//�޸�����

void ChangePasswd(void)
{
    u16 key_num;
    Unlock();
    ChangePWmenu();

    while((key_num = GET_NUM()) != 0xffff)
        Load_Keyboard(0, 170);

    if(key_num == 0xffff)
    {
        Password[0] = Password[1];
    }

    Load_Keyboard(0, 170);
    LCD_Fill(0, 0, lcddev.width, 139, WHITE);
}


//ɾ��ָ�ƽ���

void DelFingerMenu(u8 c)
{
    if(c)
    {
        LCD_ShowString(55, 23, 240, 16, 16, (u8*)"1.Del one");
        LCD_ShowString(55, 43, 240, 16, 16, (u8*)"2.Del all");

    }
    else
    {
        LCD_ShowString(20, 80, 240, 16, 16, (u8*)"Delete Fingerprint");
        LCD_ShowString(20, 96, 240, 16, 16, (u8*)"0=< ID <=299");

    }

}

//����������
void Unlockmenu(u8 n)
{
    if(n == 0)
    {
        LCD_Fill(0, 0, lcddev.width, 139, WHITE);
        LCD_ShowString(30, 80, 240, 16, 16, (u8*)"Please enter ");
        LCD_ShowString(20, 96, 240, 16, 16, (u8*)"4 digit password");
    }
    else if(n == 1)
    {
        LCD_Fill(0, 0, lcddev.width, 139, WHITE);
        LCD_ShowString(20, 80, 240, 16, 16, (u8*)"Password Wrong");
        LCD_ShowString(20, 96, 240, 16, 16, (u8*)"Enter again");
    }
}

//����������
void Menu(u8 n)
{

    if(n == 0)
    {
        LCD_Fill(0, 0, lcddev.width, 139, WHITE);
        LCD_ShowString(30, 3, 240, 16, 16, (u8*)"Access Control System");
        LCD_ShowString(30, 80, 240, 16, 16, (u8*)"Please enter ");
        LCD_ShowString(20, 96, 240, 16, 16, (u8*)"4 digit password");
    }
    else if(n == 1)
    {
        LCD_Fill(0, 0, lcddev.width, 139, WHITE);
        LCD_ShowString(30, 3, 240, 16, 16, (u8*)"Access Control System");
        LCD_ShowString(20, 80, 240, 16, 16, (u8*)"Password Wrong");
        LCD_ShowString(20, 96, 240, 16, 16, (u8*)"Enter again");
    }
}



//�޸��������
void ChangePWmenu(void)
{

    LCD_Fill(0, 0, lcddev.width, 139, WHITE);
    LCD_ShowString(30, 80, 240, 16, 16, (u8*)"Please change your passwd ");
    LCD_ShowString(20, 96, 240, 16, 16, (u8*)"4 digit password");


}

