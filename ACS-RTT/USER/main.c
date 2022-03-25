#include "board.h"
#include "rtthread.h"
#include "rthw.h"
/*
*****************************************************************
*       ����
*****************************************************************
*/

/*�����߳̿��ƿ�*/
static rt_thread_t thread1 = RT_NULL;
static rt_thread_t thread2 = RT_NULL;
static rt_thread_t thread3 = RT_NULL;
static rt_thread_t thread4 = RT_NULL;




/*
*****************************************************************
*       ��������
*****************************************************************
*/

static void thread1_entry(void* parameter);
static void thread2_entry(void* parameter);
static void thread3_entry(void* parameter);
static void thread4_entry(void* parameter);


/*
*****************************************************************
*       main����
*****************************************************************
*/


int main(void)
{
    /*******��ʼ��**********/
    u8 ensure;

    while(PS_HandShake(&AS608Addr))
    {
        LCD_Clear(WHITE);
        LCD_ShowString(0, 40, 240, 16, 16, (u8*)" AS608 Error");
    }//��AS608ģ������

    ensure = PS_ValidTempleteNum(&ValidN); //����ָ�Ƹ���

    if(ensure != 0x00) ShowErrMessage(ensure); //��ʾȷ���������Ϣ

    ensure = PS_ReadSysPara(&AS608Para); //������
    LCD_Clear(WHITE);
    Load_Keyboard(0, 170); //�����������
    /************************/

    thread1 =                          /* �߳̿��ƿ�ָ�� */
        rt_thread_create("th1",               /* �߳����� */
                         thread1_entry,   /* �߳���ں��� */
                         RT_NULL,             /* �߳���ں������� */
                         512,                 /* �߳�ջ��С */
                         3,                   /* �̵߳����ȼ� */
                         20);                 /* �߳�ʱ��Ƭ */

    if(thread1 != RT_NULL)
        rt_thread_startup(thread1);

    thread2 =                          /* �߳̿��ƿ�ָ�� */
        rt_thread_create("th2",               /* �߳����� */
                         thread2_entry,   /* �߳���ں��� */
                         RT_NULL,             /* �߳���ں������� */
                         512,                 /* �߳�ջ��С */
                         3,                   /* �̵߳����ȼ� */
                         20);                 /* �߳�ʱ��Ƭ */

    if(thread2 != RT_NULL)
        rt_thread_startup(thread2);

    thread3 =                          /* �߳̿��ƿ�ָ�� */
        rt_thread_create("th3",               /* �߳����� */
                         thread3_entry,   /* �߳���ں��� */
                         RT_NULL,             /* �߳���ں������� */
                         512,                 /* �߳�ջ��С */
                         3,                   /* �̵߳����ȼ� */
                         20);                 /* �߳�ʱ��Ƭ */

    if(thread3 != RT_NULL)
        rt_thread_startup(thread3);

    thread4 =                          /* �߳̿��ƿ�ָ�� */
        rt_thread_create("th3",               /* �߳����� */
                         thread4_entry,   /* �߳���ں��� */
                         RT_NULL,             /* �߳���ں������� */
                         512,                 /* �߳�ջ��С */
                         3,                   /* �̵߳����ȼ� */
                         20);                 /* �߳�ʱ��Ƭ */

    if(thread4 != RT_NULL)
        rt_thread_startup(thread4);



}
/*
*****************************************************************
*       �̶߳���
*****************************************************************
*/

static  void thread1_entry(void* parameter)
{
    //���г�ʼ��

    u16 key_num;
    u16 cnt = 0;
    static u8 root = 0;


    while(1)
    {
        if(!root)
        {
            RUserEnter(&root);
        }
        else
        {
            rt_enter_critical();

            while(1)
            {
                MainMenu();//���˵�
                key_num = Get_KeyNumber(0, 170);

                if(key_num)
                {
                    if(key_num == 1)Unlock();		//����

                    if(key_num == 2)Add_FR();		//¼ָ��

                    if(key_num == 3)Del_FR();		//ɾָ��

                    if(key_num == 4)Add_IC_Card();		//���IC

                    if(key_num == 5)Del_IC_Card();		//ɾ��IC

                    if(key_num == 6)ChangePasswd();		//�޸�����

                    if(key_num == 8)ServoControl(195);

                    if(key_num == 15)root = 0;
                }

                delay_ms(1);
                ++cnt;
                if(cnt == 500 && ServoFlag)
                {
										ServoControl(195);
                    ServoFlag = 0;
                    cnt = 0;
                }

                if(!root) break;

            }

            rt_exit_critical();

        }

        rt_thread_delay(1);
    }
}
static  void thread2_entry(void* parameter)
{
    while(1)
    {
        if(PS_Sta)	 //���PS_Sta״̬���������ָ����
        {
            rt_enter_critical();
            press_FR();//ˢָ��
            rt_exit_critical();
        }

        rt_thread_delay(1);
    }
}

static  void thread3_entry(void* parameter)
{

    while(1)
    {
        rt_enter_critical();
        Verify_IC_Card();
        rt_exit_critical();

        rt_thread_delay(1);
    }
}

static  void thread4_entry(void* parameter)
{
    while(1)
    {
        if(ServoFlag)
        {
            rt_thread_delay(1500);
            ServoControl(195);
            ServoFlag = 0;
        }

        rt_thread_delay(1);
    }

}




