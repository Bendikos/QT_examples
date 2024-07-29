#ifndef _lcd12864_H
#define _lcd12864_H

#include "public.h"

extern char local_date;

sbit LCD12864_RS=P2^6;//数据命令选择
sbit LCD12864_WR=P2^5;//读写选择
sbit LCD12864_E=P2^7;//使能信号

#define LCD12864_DATAPORT	P0	//LCD12864数据端口定义
sbit LCD12864_PSB=P3^2;//8位或4并口/串口选择


void lcd12864_init(void);     //LCD初始化
void lcd12864_write_cmd(u8 WCLCD);    //写指令
void lcd12864_write_data(u8 WDLCD);     //写数据
void lcd12864_clear(void);                //清屏
void lcd12864_show_char(u8 X,u8 Y,u8 DData);   //显示一个字符
void lcd12864_show_string(u8 X, u8 Y, u8 *DData);   //显示一串字符
void lcd12864_show_image(u8 code *DData);   //显示图形
void lcd12864_show_num(u8 X, u8 Y, u32 number,u8 Length);    //显示一串数字



#endif
