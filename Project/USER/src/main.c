#include "headfile.h"

void main()
{
	

	rt_thread_mdelay(800);					// ��ʱ150ms���ȴ��������������ϵ�ɹ�
	gpio_init(B9, GPO, 1, GPIO_PIN_CONFIG); // ��ʼ��B9��

	arm_init();
	timer_pit_init();

	display_init(); // ��ʾ����ʼ��


	buzzer_init(); // ��ʼ��������
	button_init(); // ��ʼ������
	
//	
//		smooth_move(178, 118, 170, 157);
//		smooth_move(170, 157, 226, 169);
//		smooth_move(226, 169, 237, 132);
//		smooth_move(237, 132, 178, 118);
//	
//		smooth_move(175, 118, 164, 157);
//		smooth_move(164, 157, 223, 172);
//		smooth_move(223, 172, 235, 133);
//		smooth_move(235, 133, 175, 118);
//	ARM_scan_rectangle();

	//ARM_UP_MOVE(10);
//	ARM_LOW_MOVE(150);
//	motor_init();

	ARM_UP_TAR_ANGLE = 50;
	ARM_LOW_TAR_ANGLE = 56;
	
	rt_thread_mdelay(1000);
	
	ARM_UP_TAR_ANGLE = 150;
	ARM_LOW_TAR_ANGLE = 150;

	while (1)
	{
		gpio_toggle(B9);
		rt_thread_mdelay(500);
	}
}
