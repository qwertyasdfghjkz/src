#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include "stm32f10x.h"

//存储密码数据
//Password[0]初始化密码，Password[1]输入密码
extern u16 Password[2];

void Load_Keyboard(u16 x,u16 y);//加载键盘界面
void Key_Staset(u16 x,u16 y,u8 keyx,u8 sta);//键盘状态返回
u8 Get_KeyNumber(u16 x,u16 y);//获得键值
u16 GET_NUM(void);//键盘返回值自定义函数
void SpecifyClear(u16 x ,u16 y,u16 dx,u16 dy);//清除指定页面
void MainMenu(void);
void DelFingerMenu(u8 c);
void Unlock(void);
void Unlockmenu(u8 n);

#endif
