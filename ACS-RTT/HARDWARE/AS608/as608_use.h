#ifndef _AS608_USE_H
#define _AS608_USE_H
#include "stm32f10x.h"
#include "as608.h"
void ShowErrMessage(u8 ensure);
void Add_FR(void);
void press_FR(void);
void Del_FR(void);

extern SysPara AS608Para;//ָ��ģ��AS608����
extern u16 ValidN;//ģ������Чָ�Ƹ���

#endif
