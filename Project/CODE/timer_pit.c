#include "encoder.h"
#include "motor.h"
#include "timer_pit.h"

void timer1_pit_entry(void *parameter)//һ��ʱ�ӽ���һ����
{
    static uint32 time;
    time++;

   
		if(0 == (time%20))//ÿ0.02s�ɼ�һ��
    {
		
			encoder_get();
			motor_control(1);
				
    }
		
		
		

    if(0 == (time%5))//0.005s�ɼ�һ��
    {
			
			Mahony_computeAngles();//�ɼ�����������

    }
		
}


void timer_pit_init(void)
{
    rt_timer_t timer;
    
    //����һ����ʱ�� ��������
    timer = rt_timer_create("timer1", timer1_pit_entry, RT_NULL, 1, RT_TIMER_FLAG_PERIODIC);
    
    //������ʱ��
    if(RT_NULL != timer)
    {
        rt_timer_start(timer);
    }


    
}