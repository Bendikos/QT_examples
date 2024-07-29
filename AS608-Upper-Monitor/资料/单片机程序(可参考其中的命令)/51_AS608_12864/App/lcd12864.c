#include "lcd12864.h"
char local_date=0;
//LCD初始化
void lcd12864_init(void)
{
	LCD12864_PSB = 1; //选择8位或4位并口方式
	lcd12864_write_cmd(0x30);        //显示模式设置，开始要求每次检测忙信号
	lcd12864_write_cmd(0x01);        //显示清屏
	lcd12864_write_cmd(0x06);        //显示光标移动设置
	lcd12864_write_cmd(0x0C);        //显示开及光标设置

}

//写指令
void lcd12864_write_cmd(u8 cmd)
{

	LCD12864_RS = 0;
	LCD12864_WR = 0;
	LCD12864_E = 0;
	LCD12864_DATAPORT = cmd;
	delay_ms(1);
	LCD12864_E = 1;
	delay_ms(1);
	LCD12864_E = 0;
}

//写数据
void lcd12864_write_data(u8 dat)
{

	LCD12864_RS = 1;
	LCD12864_WR = 0;
	LCD12864_E = 0;
	LCD12864_DATAPORT = dat;
	delay_ms(1);
	LCD12864_E = 1;
	delay_ms(1);
	LCD12864_E = 0;
}

//清屏
void lcd12864_clear(void)
{
	lcd12864_write_cmd(0x01);        //显示清屏
}

/*******************************************************************************
* 函 数 名       : lcd12864_show_char
* 函数功能		 : LCD12864显示一个字符
* 输    入       : x,y：显示坐标，x=0~7，y=0~3;
				   DData：显示的字符
* 输    出    	 : 无
*******************************************************************************/
void lcd12864_show_char(u8 X, u8 Y, u8 DData)
{
	if(Y<=0)Y=0;
	if(Y>3)Y=3;
	X &= 0x0F;      //限制X不能大于16，Y不能大于1
	switch (Y) {
		case 0:
			X |= 0x80;
			break;
		case 1:
			X |= 0x90;
			break;
		case 2:
			X |= 0x88;
			break;
		case 3:
			X |= 0x98;
			break;
	}

	lcd12864_write_cmd(X);      //这里不检测忙信号，发送地址码
	lcd12864_write_data(DData);
}

/*******************************************************************************
* 函 数 名       : lcd12864_show_string
* 函数功能		 : LCD12864显示字符串
* 输    入       : x,y：显示坐标，x=0~7，y=0~3;
				   DData：显示字符串数据
* 输    出    	 : 无
*******************************************************************************/
void lcd12864_show_string(u8 X, u8 Y, u8 *DData)
{
	u8 ListLength, X2;
	ListLength = 0;
	X2 = X;
	if(Y<=0)Y=0;
	if(Y>3)Y=3;
	X &= 0x0F;      //限制X不能大于16，Y在1-4之内
	switch (Y) {
		case 0:
			X2 |= 0x80;
			break;
		case 1:
			X2 |= 0x90;
			break;
		case 2:
			X2 |= 0x88;
			break;
		case 3:
			X2 |= 0x98;
			break;
	}
	lcd12864_write_cmd(X2);     //发送地址码
	while (DData[ListLength] >= 0x20) { //若到达字串尾则退出
		if (X <= 0x0F) { //X坐标应小于0x0F
			lcd12864_write_data(DData[ListLength]);
			ListLength++;
			X++;
			delay_ms(5);
		}
	}
}




/*******************************************************************************
* 函 数 名       : lcd12864_show_num
* 函数功能		 : LCD12864显示数字
* 输    入       : x,y：显示坐标，x=0~7，y=0~3;
				   number：显示字符串数据
                   Length：要显示数字的长度
* 输    出    	 : 无
*******************************************************************************/

void lcd12864_show_num(u8 X, u8 Y, u32 number, u8 Length)
{
	u8 array[11];
	u8 i;
	array[Length] = 0;
  
    
	for (i = Length; i > 0; i--) {
		array[i - 1] = number % 10 + '0';
		number /= 10;
	}

	for (i = 0; i < Length - 1; i++) {
		if (array[i] == '0') {
			array[i] = ' ';
		}
		else {
			break;
		}
	}
	lcd12864_show_string(X, Y, array);
}

/*******************************************************************************
* 函 数 名       : lcd12864_show_image
* 函数功能		 : LCD12864显示图片
* 输    入       : DData：要显示的图片
                    阴码，顺向（高位在前），逐行
* 输    出    	 : 无
*******************************************************************************/

void lcd12864_show_image(u8 code *DData)
{
    u8 x, y, i;
    u16 tmp = 0;
    for(i = 0; i < 9; i+=8)     //分两屏，上半屏和下半屏
    {
        for(x=0; x<32; x++)
        {
            lcd12864_write_cmd(0x34);
            lcd12864_write_cmd(0x80+x);      //列地址
            lcd12864_write_cmd(0x80+i);      //行地址，下半屏
            for(y=0;y<16;y++)
            {
                lcd12864_write_data(DData[tmp+y]); //读取数据写入LCD
            }
            tmp +=16;
        }
    }
    lcd12864_write_cmd(0x36);        //扩充功能设定
    lcd12864_write_cmd(0x30);
}