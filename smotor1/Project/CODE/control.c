#include "control.h"

rt_sem_t uart_corrdinate_sem;//识别坐标点后信号量




rt_thread_t find_rectangle_th;




void find_rectangle_entry(void *param)
{

    while (1)
    {
			
			
			

			rt_sem_take(uart_corrdinate_sem, RT_WAITING_FOREVER);
			
					rt_kprintf("data_x:%d,%d\n", ART1_POINT_X[0],ART1_POINT_Y[0]);
					rt_kprintf("data_x:%d,%d\n", ART1_POINT_X[1],ART1_POINT_Y[1]);
					rt_kprintf("data_x:%d,%d\n", ART1_POINT_X[2],ART1_POINT_Y[2]);
					rt_kprintf("data_x:%d,%d\n", ART1_POINT_X[3],ART1_POINT_Y[3]);
			
			smooth_move(ART1_POINT_X[0], ART1_POINT_Y[0], ART1_POINT_X[1], ART1_POINT_Y[1]);
			smooth_move(ART1_POINT_X[1], ART1_POINT_Y[1], ART1_POINT_X[2], ART1_POINT_Y[2]);
			smooth_move(ART1_POINT_X[2], ART1_POINT_Y[2], ART1_POINT_X[3], ART1_POINT_Y[3]);
			smooth_move(ART1_POINT_X[3], ART1_POINT_Y[3], ART1_POINT_X[0], ART1_POINT_Y[0]);
			
			
		}
		
		
}


void arm_start_init(void)
{

	uart_corrdinate_sem = rt_sem_create("uart_corrdinate_sem", 0, RT_IPC_FLAG_FIFO);

    find_rectangle_th = rt_thread_create("find_rectangle_th", find_rectangle_entry, RT_NULL, 1024, 28, 10);


    rt_thread_startup(find_rectangle_th);

}
