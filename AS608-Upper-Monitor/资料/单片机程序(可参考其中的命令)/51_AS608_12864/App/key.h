#ifndef _KEY_H_
#define _KEY_H_

#include "public.h"
#include <REGX52.H>

//定义按键输入端口
sbit KEY_UP=P1^0;
sbit KEY_DOWN=P1^1;
sbit KEY_OK=P1^2;
sbit KEY_CANCEL=P1^3;


void Key_Init(void);

#endif
