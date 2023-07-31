#include "display.h"

rt_mailbox_t display_mailbox; // ����һ��������Ϣ������

int angle1;
int angle2;

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
		

			angle1 ++;
			ARM_UP_angle(angle1);
		ips114_showint16(70, 0, angle1);
			
			
		mb_data = 0; // �����������
	}


	if ((mb_data == 2)) // ���°���1
	{

					angle1 --;
			ARM_UP_angle(angle1);
		ips114_showint16(70, 0, angle1);
		
		mb_data = 0; // �����������
	}


	if ((mb_data == 3))
	{

		mb_data = 0; // �����������
	}

	if (mb_data == 4)
	{

		
		mb_data = 0; // �����������
	}

}


void GUI_motor_value() // ��ʾ���״̬����·��״̬
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

	// ��ʼ����Ļ
	ips114_init();

	// ������ʾ�߳� ���ȼ�����Ϊ31
	display_th = rt_thread_create("display", display_entry, RT_NULL, 1024, 31, 1000);

	display_mailbox = rt_mb_create("display", 5, RT_IPC_FLAG_FIFO);

	// ������ʾ�߳�
	if (RT_NULL != display_th)
	{
		rt_thread_startup(display_th);
	}
}