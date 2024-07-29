#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"	 


#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//读取按键2
#define KEY3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//读取按键3 
#define KEY4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//读取按键4
#define KEY5  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//读取按键5

extern u8 key_num;

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);//按键扫描函数					    
#endif
