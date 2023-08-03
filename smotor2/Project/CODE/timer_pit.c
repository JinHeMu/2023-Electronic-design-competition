#include "timer_pit.h"

void timer1_pit_entry(void *parameter)//一个时钟节拍一毫秒
{
    static uint32 time;
    time++;
    
    //采集陀螺仪数据
    
    
		
		if(0 == (time%1))//每0.02s采集一次
    {

				ARM_UP_MOVE(ARM_UP_TAR_ANGLE);ARM_LOW_MOVE(ARM_LOW_TAR_ANGLE);
				picture_x_pid(ART1_POINT_X, 0);
				//picture_y_pid(ART1_POINT_Y, 0);
							
				
    }
		
		if(0 == (time%20))//每0.02s采集一次
    {

			rt_kprintf("dis:%d\n", distance(ART1_POINT_X,ART1_POINT_Y ,0,0));

				
    }
						
				
    
		
		
}


void timer_pit_init(void)
{
    rt_timer_t timer;
    
    //创建一个定时器 周期运行
    timer = rt_timer_create("timer1", timer1_pit_entry, RT_NULL, 1, RT_TIMER_FLAG_PERIODIC);
    
    //启动定时器
    if(RT_NULL != timer)
    {
        rt_timer_start(timer);
    }


    
}