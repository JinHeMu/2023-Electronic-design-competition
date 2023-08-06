#include "display.h"

rt_mailbox_t display_mailbox; // ����һ��������Ϣ������

int angle_y = 95;
int angle_x = 95;

char taget_Big_category[10];

void (*current_operation_index)();


//// �༶�˵�����
//Menu_table table[30] =
//	{
//		{0, 1, 1, 0, (*home)}, // һ�����棨��ҳ�棩 ����������һ����ȷ�����˳�

//		{1, 2, 6, 0, (*GUI_motor)},	 // �������� �����ز���
//		{2, 3, 7, 0, (*GUI_pid)},	 // �������� pidֵ
//		{3, 4, 8, 0, (*GUI_imu_ra)}, // �������� ������ֵ
//		{4, 5, 9, 0, (*GUI_route)},
//		{5, 1, 10, 0, (*GUI_arm)},

//		{6, 1, 1, 1, (*GUI_motor_value)},  // �������棺motor_value
//		{7, 2, 2, 2, (*GUI_pid_value)},	   // �������棺pid_value
//		{8, 3, 3, 3, (*GUI_imu_ra_value)}, // ��������
//		{9, 4, 4, 4, (*GUI_route_value)}, // ��������
//		{10, 5, 5, 5, (*GUI_arm_value)}, // �������棺
//		


//};

uint8_t func_index = 0; // �������ʱ���ڳ��������ֵ

void Menu_key_set(void)
{

	rt_ubase_t mb_data; // �������������

	rt_mb_recv(display_mailbox, &mb_data, RT_WAITING_NO); // ���ܰ������͹������ʼ�	

	if ((mb_data == 1)) // ���°���1
	{
		

//			ARM_UP_angle(angle_y);
//			ips114_showint16(70, 0, angle_y);
		
		
//		ARM_UP_MOVE(angle_y*20);
//		ARM_UP_MOVE(angle_y*10);
//		ARM_back();
//		angle_y++;
//		ARM_UP_TAR_ANGLE = angle_y;
////		
//		rt_kprintf("angle_x:%d angle_y:%d\n",angle_x,angle_y);
		
		
//		ARM_UP_TAR_ANGLE = 127.0545  -0.2443 * 118;
//		ARM_LOW_TAR_ANGLE = 142.4687  -0.2376 * 175;
//		rt_thread_mdelay(1000);
//			ARM_UP_TAR_ANGLE = 127.0545  -0.2443 * 157;
//		ARM_LOW_TAR_ANGLE = 142.4687  -0.2376 * 166;
//			rt_thread_mdelay(1000);
//		ARM_UP_TAR_ANGLE = 127.0545  -0.2443 * 171;
//		ARM_LOW_TAR_ANGLE = 142.4687  -0.2376 * 223;
//		rt_thread_mdelay(1000);		
//		ARM_UP_TAR_ANGLE = 127.0545  -0.2443 * 132;
//		ARM_LOW_TAR_ANGLE = 142.4687  -0.2376 * 235;
//		rt_thread_mdelay(1000);
//	smooth_move(175, 118, 164, 157);
//	smooth_move(164, 157, 223, 172);
//	smooth_move(223, 172, 235, 133);
//	smooth_move(235, 133, 175, 118);

		


//		smooth_move(175, 118, 175, 98);
//		smooth_move(175, 98, 223, 98);
//		smooth_move(223, 98, 223, 118);
//		smooth_move(223, 118, 175, 118);



		
		mb_data = 0; // �����������
	}


	if ((mb_data == 2)) // ���°���1
	{

//					angle_y --;
//			ARM_UP_angle(angle_y);
//		ips114_showint16(70, 0, angle_y);
//		angle_x++;
//		ARM_LOW_TAR_ANGLE = angle_x*10;
//		ARM_LOW_MOVE(angle_x*10);
//		angle_y--;
//		ARM_UP_TAR_ANGLE = angle_y;

//		track_ki += 0.0000001;
	track_x_kd += 0.0001;
		
		rt_kprintf("angle_x:%d angle_y:%d\n",angle_x,angle_y);
		
		
		
		mb_data = 0; // �����������
	}


	if ((mb_data == 3))
	{
//					angle_x ++;
//			ARM_LOW_angle(angle_x);
//			ips114_showint16(70, 0, angle_y);
//			
//			angle_x++;
//		
//			ARM_LOW_TAR_ANGLE = angle_x;
//		
//		track_kd += 0.0000001;

track_y_kd += 0.001;
		rt_kprintf("angle_x:%d angle_y:%d\n",angle_x,angle_y);
			
//ARM_UP_TAR_ANGLE = 90;
		mb_data = 0; // �����������
	}

	if (mb_data == 4)
	{

		
//					angle_x --;
//			ARM_LOW_angle(angle_x);
//			ips114_showint16(70, 0, angle_y);
		angle_x--;
						ARM_LOW_TAR_ANGLE = angle_x;
		
		
		

			
		rt_kprintf("angle_x:%d angle_y:%d\n",angle_x,angle_y);
//			ARM_UP_TAR_ANGLE = 150;
		mb_data = 0; // �����������
	}

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


//void display_entry(void *parameter)
//{
//	while(1)
//{
//	
//}
//	
//}


//}

void display_init(void)
{

	rt_thread_t display_th;
	
//	rt_thread_t key1_th;
//	rt_thread_t key2_th;
//	rt_thread_t key3_th;
//	rt_thread_t key4_th;

	// ��ʼ����Ļ
	ips114_init();

	// ������ʾ�߳� ���ȼ�����Ϊ31
	display_th = rt_thread_create("display", display_entry, RT_NULL, 1024, 30, 10);
	
//	key1_th = rt_thread_create("key1_th", key1_entry, RT_NULL, 1024, 29, 10);
//	key2_th = rt_thread_create("key2_th", key2_entry, RT_NULL, 1024, 28, 10);
//	key3_th = rt_thread_create("key3_th", key3_entry, RT_NULL, 1024, 27, 10);
//	key4_th = rt_thread_create("key4_th", key4_entry, RT_NULL, 1024, 26, 10);

	display_mailbox = rt_mb_create("display", 5, RT_IPC_FLAG_FIFO);

	// ������ʾ�߳�

	rt_thread_startup(display_th);
//	rt_thread_startup(key1_th);
//	rt_thread_startup(key2_th);
//	rt_thread_startup(key3_th);
//	rt_thread_startup(key4_th);
//	
}