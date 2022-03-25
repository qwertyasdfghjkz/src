#include "board.h"
#include "rtthread.h"
#include "rthw.h"
/*
*****************************************************************
*       变量
*****************************************************************
*/

/*定义线程控制块*/
static rt_thread_t thread1 = RT_NULL;
static rt_thread_t thread2 = RT_NULL;
static rt_thread_t thread3 = RT_NULL;
static rt_thread_t thread4 = RT_NULL;




/*
*****************************************************************
*       函数声明
*****************************************************************
*/

static void thread1_entry(void* parameter);
static void thread2_entry(void* parameter);
static void thread3_entry(void* parameter);
static void thread4_entry(void* parameter);


/*
*****************************************************************
*       main函数
*****************************************************************
*/


int main(void)
{
    /*******初始化**********/
    u8 ensure;

    while(PS_HandShake(&AS608Addr))
    {
        LCD_Clear(WHITE);
        LCD_ShowString(0, 40, 240, 16, 16, (u8*)" AS608 Error");
    }//与AS608模块握手

    ensure = PS_ValidTempleteNum(&ValidN); //读库指纹个数

    if(ensure != 0x00) ShowErrMessage(ensure); //显示确认码错误信息

    ensure = PS_ReadSysPara(&AS608Para); //读参数
    LCD_Clear(WHITE);
    Load_Keyboard(0, 170); //加载虚拟键盘
    /************************/

    thread1 =                          /* 线程控制块指针 */
        rt_thread_create("th1",               /* 线程名字 */
                         thread1_entry,   /* 线程入口函数 */
                         RT_NULL,             /* 线程入口函数参数 */
                         512,                 /* 线程栈大小 */
                         3,                   /* 线程的优先级 */
                         20);                 /* 线程时间片 */

    if(thread1 != RT_NULL)
        rt_thread_startup(thread1);

    thread2 =                          /* 线程控制块指针 */
        rt_thread_create("th2",               /* 线程名字 */
                         thread2_entry,   /* 线程入口函数 */
                         RT_NULL,             /* 线程入口函数参数 */
                         512,                 /* 线程栈大小 */
                         3,                   /* 线程的优先级 */
                         20);                 /* 线程时间片 */

    if(thread2 != RT_NULL)
        rt_thread_startup(thread2);

    thread3 =                          /* 线程控制块指针 */
        rt_thread_create("th3",               /* 线程名字 */
                         thread3_entry,   /* 线程入口函数 */
                         RT_NULL,             /* 线程入口函数参数 */
                         512,                 /* 线程栈大小 */
                         3,                   /* 线程的优先级 */
                         20);                 /* 线程时间片 */

    if(thread3 != RT_NULL)
        rt_thread_startup(thread3);

    thread4 =                          /* 线程控制块指针 */
        rt_thread_create("th3",               /* 线程名字 */
                         thread4_entry,   /* 线程入口函数 */
                         RT_NULL,             /* 线程入口函数参数 */
                         512,                 /* 线程栈大小 */
                         3,                   /* 线程的优先级 */
                         20);                 /* 线程时间片 */

    if(thread4 != RT_NULL)
        rt_thread_startup(thread4);



}
/*
*****************************************************************
*       线程定义
*****************************************************************
*/

static  void thread1_entry(void* parameter)
{
    //进行初始化

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
                MainMenu();//主菜单
                key_num = Get_KeyNumber(0, 170);

                if(key_num)
                {
                    if(key_num == 1)Unlock();		//解锁

                    if(key_num == 2)Add_FR();		//录指纹

                    if(key_num == 3)Del_FR();		//删指纹

                    if(key_num == 4)Add_IC_Card();		//添加IC

                    if(key_num == 5)Del_IC_Card();		//删除IC

                    if(key_num == 6)ChangePasswd();		//修改密码

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
        if(PS_Sta)	 //检测PS_Sta状态，如果有手指按下
        {
            rt_enter_critical();
            press_FR();//刷指纹
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




