#include "control.h"


double  track_x_kp = 0.001, track_x_ki = 0 ,track_x_kd = 0.016;

//double  track_x_kp = 0, track_x_ki = 0 ,track_x_kd = 0;


double  track_y_kp = 0.0015, track_y_ki = 0, track_y_kd = 0.024;

rt_sem_t Tracking_point_sem;//识别坐标点后信号量
rt_thread_t Tracking_point_th;




int distance(float current_x, float current_y, float target_x, float target_y)
{

    float det_x;
    float det_y;
    float distance;

    det_x = target_x - current_x;
    det_y = target_y - current_y;
    distance = sqrt(det_x * det_x + det_y * det_y);

    return (int)distance;
}

int picture_x_pid(int16 now_x, int16 target_x)
{

    static float Bias, Speed_X, Integral_bias, Last_Bias;
    Bias = (float)(target_x - now_x);
    Integral_bias += Bias;
    Speed_X = track_x_kp* Bias + track_x_ki * Integral_bias + track_x_kd * (Bias - Last_Bias);
    Last_Bias = Bias;
		if(abs(now_x) < 3)
		{
			Speed_X = 0;
		}
		ARM_LOW_TAR_ANGLE += Speed_X;
	
    return ARM_LOW_TAR_ANGLE;
}

int picture_y_pid(int16 now_y, int16 target_y)
{
    static float Bias, Speed_Y, Integral_bias, Last_Bias;
    Bias = (float)(target_y - now_y);
    Integral_bias += Bias;
    Speed_Y = track_y_kp* Bias + track_y_ki * Integral_bias + track_y_kd * (Bias - Last_Bias);
    Last_Bias = Bias;
			if(abs(now_y) < 3)
		{
			Speed_Y = 0;
		}
		ARM_UP_TAR_ANGLE += Speed_Y;
    return ARM_UP_TAR_ANGLE;
}



void control_pid()
{
	
	
}


void Tracking_point_entry(void *param)
{

		rt_sem_take(Tracking_point_sem, RT_WAITING_FOREVER);
    while (1)
    {
			
//			rt_kprintf("dis%d\n", distance(ART1_POINT_X,ART1_POINT_Y ,0,0));


		}
		
		
}


void arm_start_init(void)
{

		Tracking_point_sem = rt_sem_create("Tracking_point_sem", 0, RT_IPC_FLAG_FIFO);

    Tracking_point_th = rt_thread_create("Tracking_point_th", Tracking_point_entry, RT_NULL, 1024, 28, 10);


    rt_thread_startup(Tracking_point_th);

}
