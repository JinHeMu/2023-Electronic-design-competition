#include "display.h"

rt_mailbox_t display_mailbox; // 定义一个接受信息的邮箱

int angle1;
int angle2;

char taget_Big_category[10];

void (*current_operation_index)();


//// 多级菜单界面
//Menu_table table[30] =
//	{
//		{0, 1, 1, 0, (*home)}, // 一级界面（主页面） 索引，向下一个，确定，退出

//		{1, 2, 6, 0, (*GUI_motor)},	 // 二级界面 电机相关参数
//		{2, 3, 7, 0, (*GUI_pid)},	 // 二级界面 pid值
//		{3, 4, 8, 0, (*GUI_imu_ra)}, // 二级界面 陀螺仪值
//		{4, 5, 9, 0, (*GUI_route)},
//		{5, 1, 10, 0, (*GUI_arm)},

//		{6, 1, 1, 1, (*GUI_motor_value)},  // 三级界面：motor_value
//		{7, 2, 2, 2, (*GUI_pid_value)},	   // 三级界面：pid_value
//		{8, 3, 3, 3, (*GUI_imu_ra_value)}, // 三级界面
//		{9, 4, 4, 4, (*GUI_route_value)}, // 三级界面
//		{10, 5, 5, 5, (*GUI_arm_value)}, // 三级界面：
//		


//};

uint8_t func_index = 0; // 主程序此时所在程序的索引值

void Menu_key_set(void)
{

	rt_ubase_t mb_data; // 储存邮箱的数据

	rt_mb_recv(display_mailbox, &mb_data, RT_WAITING_NO); // 接受按键发送过来的邮件	

	if ((mb_data == 1)) // 按下按键1
	{
		

			angle1 ++;
			ARM_UP_angle(angle1);
		ips114_showint16(70, 0, angle1);
			
			
		mb_data = 0; // 邮箱数据清除
	}


	if ((mb_data == 2)) // 按下按键1
	{

					angle1 --;
			ARM_UP_angle(angle1);
		ips114_showint16(70, 0, angle1);
		
		mb_data = 0; // 邮箱数据清除
	}


	if ((mb_data == 3))
	{

		mb_data = 0; // 邮箱数据清除
	}

	if (mb_data == 4)
	{

		
		mb_data = 0; // 邮箱数据清除
	}

}


void GUI_motor_value() // 显示电机状态，和路程状态
{

	ips114_showstr(0, 0, "ENCODER1:");
	ips114_showstr(0, 1, "ENCODER2:");


	ips114_showint16(70, 0, RC_encoder1);
	ips114_showint16(70, 1, RC_encoder2);
	
	ips114_showstr(0, 2, "gyro_z:");
	ips114_showfloat(60, 3, angle_z, 3, 2);

}


void display_entry(void *parameter)
{
	while(1)
{
	Menu_key_set();
	//GUI_motor_value();
//	GUI_imu_ra_value();
}
	
}




//}

void display_init(void)
{

	rt_thread_t display_th;

	// 初始化屏幕
	ips114_init();

	// 创建显示线程 优先级设置为31
	display_th = rt_thread_create("display", display_entry, RT_NULL, 1024, 31, 1000);

	display_mailbox = rt_mb_create("display", 5, RT_IPC_FLAG_FIFO);

	// 启动显示线程
	if (RT_NULL != display_th)
	{
		rt_thread_startup(display_th);
	}
}