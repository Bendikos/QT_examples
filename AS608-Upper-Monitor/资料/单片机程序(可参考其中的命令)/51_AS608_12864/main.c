#include <buzz.h>
#include <key.h>
#include <uart.h>
#include <FPM10A.h>
#include <lcd12864.h>

void main()
{
	lcd12864_init();			//初始化液晶
    delay_10us(1);
    lcd12864_clear();
	Uart_Init();			//初始化串口
	Key_Init();				//初始化按键
	delay_ms(500);          //延时500MS，等待指纹模块复位
	Device_Check();		   	//校对指纹模块是否接入正确，液晶做出相应的提示
	delay_ms(500);			//对接成功界面停留一定时间
    lcd12864_clear();
    lcd12864_show_string(2,0,"指纹测试");
    lcd12864_show_string(1,1,"搜索指纹");
	lcd12864_show_string(1,2,"添加指纹");	 //添加和删除指纹
 	lcd12864_show_string(1,3,"清空指纹");
   
	while (1) {
		/**************进入主功能界面****************/

		if (local_date == 0) {
            lcd12864_show_char(0,1,'*');
            lcd12864_show_char(0,2,' ');
            lcd12864_show_char(0,3,' ');
		}
		else if (local_date == 1) {
            lcd12864_show_char(0,1,' ');
            lcd12864_show_char(0,2,'*');
            lcd12864_show_char(0,3,' ');
		}
		else if (local_date == 2) {
            lcd12864_show_char(0,1,' ');
            lcd12864_show_char(0,2,' ');
            lcd12864_show_char(0,3,'*');
            
		}
		//确认键
		if (KEY_OK == 0) {
			while (KEY_OK == 0); //等待松开按键
			switch (local_date) {
				case 0:  //搜索指纹
					FPM10A_Find_Fingerprint();
					break;

				case 1:	 //添加指纹
					FPM10A_Add_Fingerprint();
					break;

				case 2:	//清空指纹
					FPM10A_Delete_All_Fingerprint();
					break;
			}
		}
		if (KEY_UP == 0) {
			while (KEY_UP == 0); //等待松开按键
			if (local_date >= -1) {
				local_date--;
				if (local_date == -1)
					local_date = 2;
			}
		}
		//切换键
		if (KEY_DOWN == 0) {
			while (KEY_DOWN == 0); //等待松开按键
			if (local_date <= 2) {
				local_date++;
				if (local_date == 3)
					local_date = 0;
			}
		}
		delay_ms(100); //延时判断100MS检测一次
	}
}
