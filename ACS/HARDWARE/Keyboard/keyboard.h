#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include "stm32f10x.h"

//�洢��������
//Password[0]��ʼ�����룬Password[1]��������
extern u16 Password[2];

void Load_Keyboard(u16 x,u16 y);//���ؼ��̽���
void Key_Staset(u16 x,u16 y,u8 keyx,u8 sta);//����״̬����
u8 Get_KeyNumber(u16 x,u16 y);//��ü�ֵ
u16 GET_NUM(void);//���̷���ֵ�Զ��庯��
void SpecifyClear(u16 x ,u16 y,u16 dx,u16 dy);//���ָ��ҳ��
void MainMenu(void);
void DelFingerMenu(u8 c);
void Unlock(void);
void Unlockmenu(u8 n);

#endif
