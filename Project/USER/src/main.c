#include "headfile.h"

void main()
{
	

	rt_thread_mdelay(800);					// ��ʱ150ms���ȴ��������������ϵ�ɹ�
	gpio_init(B9, GPO, 1, GPIO_PIN_CONFIG); // ��ʼ��B9��

	arm_init();

	display_init(); // ��ʾ����ʼ��

//	ART1_UART_Init();
//	ART2_UART_Init();

	encoder_init();	  // ��ʼ��������
	icm20602_init_spi();  // ��ʼ��������
	icm_zeroBias();
	timer_pit_init(); // ���ڶ�ʱ��

	buzzer_init(); // ��ʼ��������
	button_init(); // ��ʼ������

//	motor_init();

	while (1)
	{
		gpio_toggle(B9);
		rt_thread_mdelay(500);
	}
}
