
#include <FPM10A.h>

volatile unsigned char FPM10A_RECEICE_BUFFER[32];
unsigned int finger_id = 0;

//FINGERPRINT通信协议定义

code unsigned char FPM10A_Get_Device[10] = {0x01, 0x00, 0x07, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b}; //口令验证
code unsigned char FPM10A_Pack_Head[6] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF}; //协议包头
code unsigned char FPM10A_Get_Img[6] = {0x01, 0x00, 0x03, 0x01, 0x00, 0x05}; //获得指纹图像
code unsigned char FPM10A_Get_Templete_Count[6] = {0x01, 0x00, 0x03, 0x1D, 0x00, 0x21 }; //获得模版总数
code unsigned char FPM10A_Search[11] = {0x01, 0x00, 0x08, 0x04, 0x01, 0x00, 0x00, 0x03, 0xE7, 0x00, 0xF8}; //搜索指纹搜索范围0 - 999,使用BUFFER1中的特征码搜索
code unsigned char FPM10A_Search_0_9[11] = {0x01, 0x00, 0x08, 0x04, 0x01, 0x00, 0x00, 0x00, 0x13, 0x00, 0x21}; //搜索0-9号指纹
code unsigned char FPM10A_Img_To_Buffer1[7] = {0x01, 0x00, 0x04, 0x02, 0x01, 0x00, 0x08}; //将图像放入到BUFFER1
code unsigned char FPM10A_Img_To_Buffer2[7] = {0x01, 0x00, 0x04, 0x02, 0x02, 0x00, 0x09}; //将图像放入到BUFFER2
code unsigned char FPM10A_Reg_Model[6] = {0x01, 0x00, 0x03, 0x05, 0x00, 0x09}; //将BUFFER1跟BUFFER2合成特征模版
code unsigned char FPM10A_Delete_All_Model[6] = {0x01, 0x00, 0x03, 0x0d, 0x00, 0x11}; //删除指纹模块里所有的模版
volatile unsigned char  FPM10A_Save_Finger[9] = {0x01, 0x00, 0x06, 0x06, 0x01, 0x00, 0x0B, 0x00, 0x19}; //将BUFFER1中的特征码存放到指定的位置
//volatile:系统总是重新从它所在的内存读取数据，即使它前面的指令刚刚从该处读取过数据
/*------------------ FINGERPRINT命令字 --------------------------*/
//发送包头
void FPM10A_Cmd_Send_Pack_Head(void)
{
	int i;
	for (i = 0; i < 6; i++) { //包头
		Uart_Send_Byte(FPM10A_Pack_Head[i]);
	}
}
//发送指令
void FPM10A_Cmd_Check(void)
{
	int i = 0;
	FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头
	for (i = 0; i < 10; i++) {
		Uart_Send_Byte(FPM10A_Get_Device[i]);
	}
}
//接收反馈数据缓冲
void FPM10A_Receive_Data(unsigned char ucLength)
{
	unsigned char i;

	for (i = 0; i < ucLength; i++)
		FPM10A_RECEICE_BUFFER[i] = Uart_Receive_Byte();

}

//FINGERPRINT_获得指纹图像命令
void FPM10A_Cmd_Get_Img(void)
{
	unsigned char i;
	FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头
	for (i = 0; i < 6; i++) { //发送命令 0x1d
		Uart_Send_Byte(FPM10A_Get_Img[i]);
	}
}
//讲图像转换成特征码存放在Buffer1中
void FINGERPRINT_Cmd_Img_To_Buffer1(void)
{
	unsigned char i;
	FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头
	for (i = 0; i < 7; i++) { //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
		Uart_Send_Byte(FPM10A_Img_To_Buffer1[i]);
	}
}
//将图像转换成特征码存放在Buffer2中
void FINGERPRINT_Cmd_Img_To_Buffer2(void)
{
	unsigned char i;
	for (i = 0; i < 6; i++) { //发送包头
		Uart_Send_Byte(FPM10A_Pack_Head[i]);
	}
	for (i = 0; i < 7; i++) { //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
		Uart_Send_Byte(FPM10A_Img_To_Buffer2[i]);
	}
}
//搜索全部用户999枚
void FPM10A_Cmd_Search_Finger(void)
{
	unsigned char i;
	FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头
	for (i = 0; i < 11; i++) {
		Uart_Send_Byte(FPM10A_Search[i]);
	}
}

void FPM10A_Cmd_Reg_Model(void)
{
	unsigned char i;

	FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头

	for (i = 0; i < 6; i++) {
		Uart_Send_Byte(FPM10A_Reg_Model[i]);
	}


}
//删除指纹模块里的所有指纹模版
void FINGERPRINT_Cmd_Delete_All_Model(void)
{
	unsigned char i;
	for (i = 0; i < 6; i++) //包头
		Uart_Send_Byte(FPM10A_Pack_Head[i]);
	for (i = 0; i < 6; i++) { //命令合并指纹模版
		Uart_Send_Byte(FPM10A_Delete_All_Model[i]);
	}
}
//保存指纹
void FPM10A_Cmd_Save_Finger( unsigned int storeID )
{
	unsigned long temp = 0;
	unsigned char i;
	FPM10A_Save_Finger[5] = (storeID & 0xFF00) >> 8;
	FPM10A_Save_Finger[6] = (storeID & 0x00FF);
	for (i = 0; i < 7; i++) //计算校验和
		temp = temp + FPM10A_Save_Finger[i];
	FPM10A_Save_Finger[7] = (temp & 0x00FF00) >> 8; //存放校验数据
	FPM10A_Save_Finger[8] = temp & 0x0000FF;
	FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头
	for (i = 0; i < 9; i++)
		Uart_Send_Byte(FPM10A_Save_Finger[i]);      //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
}
//添加指纹
void FPM10A_Add_Fingerprint()
{
	unsigned char id_show[] = {0, 0, 0};
    lcd12864_clear();
    lcd12864_show_string(3,1,"0");
	while (1) {
	lcd12864_show_string(1,0,"添加指纹");	 //添加和删除指纹
 	lcd12864_show_string(1,1,"ID =");
		//按返回键直接回到主菜单
		if (KEY_CANCEL == 0) {
			delay_ms(5);
			if (KEY_CANCEL == 0) {
				while (KEY_CANCEL == 0);
				break;
			}
		}
        //按切换键指纹iD值减1
		if (KEY_UP == 0) {
			delay_ms(5);
			if (KEY_UP == 0) {
				while (KEY_UP == 0);
				if (finger_id == 0){
                    lcd12864_show_string(3,1,"299 ");
					finger_id = 299;
                }
				else{
					finger_id = finger_id - 1;
                }
			}
		}
        

		//按切换键指纹iD值加1
		if (KEY_DOWN == 0) {
			delay_ms(5);
			if (KEY_DOWN == 0) {
				while (KEY_DOWN == 0);
				if (finger_id == 299){
					finger_id = 0;
                }
				else
					finger_id = finger_id + 1;
			}
		}
        lcd12864_show_num(3,1,finger_id,3);
		//按确认键开始录入指纹信息
		if (KEY_OK == 0) {
			delay_ms(5);
			if (KEY_OK == 0) {
				while (KEY_OK == 0);
                lcd12864_clear();
                lcd12864_show_string(1,0,"请按压手指");

				while (KEY_CANCEL == 1) {
					//按下返回键退出录入返回fingerID调整状态
					if (KEY_CANCEL == 0) {
						delay_ms(5);
						if (KEY_CANCEL == 0) {
							while (KEY_CANCEL == 0);
							break;
						}
					}

					FPM10A_Cmd_Get_Img(); //获得指纹图像
					FPM10A_Receive_Data(12);
					//判断接收到的确认码,等于0指纹获取成功
					if (FPM10A_RECEICE_BUFFER[9] == 0) {
						delay_ms(100);
						FINGERPRINT_Cmd_Img_To_Buffer1();
						FPM10A_Receive_Data(12);
                        lcd12864_clear();
                        lcd12864_show_string(2,0,"成功进入");
						delay_ms(1000);
						lcd12864_show_string(2,0,"再按一次");
						while (1) {
							if (KEY_CANCEL == 0) {
								delay_ms(5);
								if (KEY_CANCEL == 0) {
									while (KEY_CANCEL == 0);
									break;
								}
							}

							FPM10A_Cmd_Get_Img(); //获得指纹图像
							FPM10A_Receive_Data(12);
							//判断接收到的确认码,等于0指纹获取成功
							if (FPM10A_RECEICE_BUFFER[9] == 0) {
								delay_ms(200);
                                lcd12864_clear();
                                lcd12864_show_string(1,0,"添加成功");
                                lcd12864_show_string(1,1,"ID =");
                                lcd12864_show_num(3,1,finger_id,3);
                                lcd12864_show_string(1,2,"是否继续添加");
								FINGERPRINT_Cmd_Img_To_Buffer2();
								FPM10A_Receive_Data(12);
								FPM10A_Cmd_Reg_Model();//转换成特征码
								FPM10A_Receive_Data(12);
								FPM10A_Cmd_Save_Finger(finger_id);
								FPM10A_Receive_Data(12);
								delay_ms(1000);
								finger_id = finger_id + 1;
                                if (finger_id == 300)
                                    finger_id = 0;
								break;
							}
						}
						break;
					}
				}
			}
		}
	}
    lcd12864_clear();
    lcd12864_show_string(2,0,"指纹测试");
    lcd12864_show_string(1,1,"搜索指纹");
	lcd12864_show_string(1,2,"添加指纹");	 //添加和删除指纹
 	lcd12864_show_string(1,3,"清空指纹");
}
//搜索指纹
void FPM10A_Find_Fingerprint()
{
	unsigned int find_fingerid = 0;
	unsigned char id_show[] = {0, 0, 0};
    lcd12864_clear();
	do {
        lcd12864_show_string(1,0,"请按压手指");
		FPM10A_Cmd_Get_Img(); //获得指纹图像
		FPM10A_Receive_Data(12);
		//判断接收到的确认码,等于0指纹获取成功
		if (FPM10A_RECEICE_BUFFER[9] == 0) {
			delay_ms(100);
			FINGERPRINT_Cmd_Img_To_Buffer1();
			FPM10A_Receive_Data(12);
			FPM10A_Cmd_Search_Finger();
			FPM10A_Receive_Data(16);
			if (FPM10A_RECEICE_BUFFER[9] == 0) { //搜索到
            lcd12864_clear();
            lcd12864_show_string(1,0,"搜索成功");
            lcd12864_show_string(1,1,"ID =");
				Buzz_Times(1);
				//拼接指纹ID数
				find_fingerid = FPM10A_RECEICE_BUFFER[10] * 256 + FPM10A_RECEICE_BUFFER[11];
				//指纹iD值显示处理
                lcd12864_show_num(3,1,find_fingerid,3);
				delay_ms(1000);
                lcd12864_clear();
			}
			else { //没有找到
                lcd12864_clear();
                lcd12864_show_string(2,0,"搜索失败");
				Buzz_Times(3);
			}
		}
	}
	while (KEY_CANCEL == 1);
    lcd12864_clear();
    lcd12864_show_string(2,0,"指纹测试");
    lcd12864_show_string(1,1,"搜索指纹");
	lcd12864_show_string(1,2,"添加指纹");	 //添加和删除指纹
 	lcd12864_show_string(1,3,"清空指纹");
}
//删除所有存贮的指纹库
void FPM10A_Delete_All_Fingerprint()
{
	unsigned char i = 0;
    lcd12864_clear();
    lcd12864_show_string(2,0,"清空全部？");
    lcd12864_show_string(1,1,"确定    取消");
	do {
		if (KEY_OK == 0) {
			delay_ms(5);
			if (KEY_OK == 0) {
				while (KEY_OK == 0);
                lcd12864_clear();
                lcd12864_show_string(2,0,"清空中……");
				delay_ms(300);
				for (i = 0; i < 8; i++) {
					lcd12864_show_string(i,1,"*");
					delay_ms(200);
				}
				FINGERPRINT_Cmd_Delete_All_Model();
				FPM10A_Receive_Data(12);
                lcd12864_clear();
                lcd12864_show_string(2,0,"清空完成");

				break;
			}
		}
	}
	while (KEY_CANCEL == 1);
    lcd12864_clear();
    lcd12864_show_string(2,0,"指纹测试");
    lcd12864_show_string(1,1,"搜索指纹");
	lcd12864_show_string(1,2,"添加指纹");	 //添加和删除指纹
 	lcd12864_show_string(1,3,"清空指纹");
}
void Device_Check(void)
{
	unsigned char i = 0;
	FPM10A_RECEICE_BUFFER[9] = 1;				         //串口数组第九位可判断是否通信正常
    lcd12864_clear();
    lcd12864_show_string(2,0,"加载中");	        //设备加载中界面
	for (i = 0; i < 8; i++) {					    //进度条式更新，看起来美观
        lcd12864_show_string(i,1,"*");                       //42对应ASIC码的 *
		delay_ms(200);						           //控制进度条速度
	}
    lcd12864_clear();
    lcd12864_show_string(2,0,"对接失败");  //液晶先显示对接失败，如果指纹模块插对的话会将其覆盖
    FPM10A_Cmd_Check();									//单片机向指纹模块发送校对命令
    FPM10A_Receive_Data(12);							//将串口接收到的数据转存
	if (FPM10A_RECEICE_BUFFER[9] == 0) {				//判断数据低第9位是否接收到0
        lcd12864_clear();
        lcd12864_show_string(2,0,"对接成功");  //符合成功条件则显示对接成功
	}
}





