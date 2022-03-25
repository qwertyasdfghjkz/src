#include "delay.h"



//void delay_us(u32 nus)
//{
//	uint32_t times=(nus*16);
//	while(times-->0);
//	
//}
//void delay_ms(u32 nms)
//{
//	u8 i,j,k;
//	while(nms-->0)
//	{
//		for(i=0;i<10;i++)
//			for(j=0;j<10;j++)
//				for(k=0;k<10;k++) delay_us(1);
//	}

//}

void delay_us(rt_uint32_t us)
{
    rt_uint32_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t reload = SysTick->LOAD;

    /* �����ʱ������ tick �� */
    ticks = us * reload / (1000000 / RT_TICK_PER_SECOND);
    /* ��õ�ǰʱ�� */
    told = SysTick->VAL;
    while (1)
    {
        /* ѭ����õ�ǰʱ�䣬ֱ���ﵽָ����ʱ����˳�ѭ�� */
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}

void delay_ms(rt_uint32_t ms)
{
    rt_uint32_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t reload = SysTick->LOAD;

    /* �����ʱ������ tick �� */
    ticks = ms * reload / (1000 / RT_TICK_PER_SECOND);
    /* ��õ�ǰʱ�� */
    told = SysTick->VAL;
    while (1)
    {
        /* ѭ����õ�ǰʱ�䣬ֱ���ﵽָ����ʱ����˳�ѭ�� */
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}



































