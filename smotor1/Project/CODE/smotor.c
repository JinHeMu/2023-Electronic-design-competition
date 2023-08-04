#include "smotor.h"

/* BOX
1 - 0°
2 - 90°
3 - 180°
4 - 270°*/

uint8 cur_angle = 1;
uint32 prime = 1;

// 定义机械臂的PWM IO口
#define ARM_UP_PIN PWM2_MODULE0_CHB_C7
#define ARM_LOW_PIN PWM2_MODULE1_CHA_C8

#define ARM_CENTER (1.5 * 50000 / 20)

float ARM_UP_CURRENT_ANGLE = 88;
float ARM_LOW_CURRENT_ANGLE = 90;

float ARM_UP_TAR_ANGLE = 88;
float ARM_LOW_TAR_ANGLE = 90;

float ANGLE_INCREMENT = 0.01;





// 设置机械臂角度
void ARM_UP_angle(float angle)
{
	pwm_duty(ARM_UP_PIN, 5650.0000 + 108.3333 * angle);
	ARM_UP_CURRENT_ANGLE = angle;
}

void ARM_LOW_angle(float angle)
{
	pwm_duty(ARM_LOW_PIN, 5650.0000 + 108.3333 * angle);
	ARM_LOW_CURRENT_ANGLE = angle;
}


void ARM_UP_MOVE(float target) {
    if (ARM_UP_CURRENT_ANGLE < target) {
        ARM_UP_CURRENT_ANGLE += ANGLE_INCREMENT;
        ARM_UP_angle(ARM_UP_CURRENT_ANGLE);
    } else if (ARM_UP_CURRENT_ANGLE > target) {
        ARM_UP_CURRENT_ANGLE -= ANGLE_INCREMENT;
        ARM_UP_angle(ARM_UP_CURRENT_ANGLE);
    }
    // 如果当前角度等于目标角度，我们不需要做任何事情
}

void ARM_LOW_MOVE(float target) {
    if (ARM_LOW_CURRENT_ANGLE < target) {
        ARM_LOW_CURRENT_ANGLE += ANGLE_INCREMENT;
        ARM_LOW_angle(ARM_LOW_CURRENT_ANGLE);
    } else if (ARM_LOW_CURRENT_ANGLE > target) {
        ARM_LOW_CURRENT_ANGLE -= ANGLE_INCREMENT;
        ARM_LOW_angle(ARM_LOW_CURRENT_ANGLE);
    }
    // 如果当前角度等于目标角度，我们不需要做任何事情
}


void ARM_scan_rectangle(void) 
	{
		ARM_UP_TAR_ANGLE = 101;
		ARM_LOW_TAR_ANGLE = 103;
		rt_thread_mdelay(3000);
		
		ARM_UP_TAR_ANGLE = 101;
		ARM_LOW_TAR_ANGLE = 76;
		rt_thread_mdelay(3000);
		
		ARM_UP_TAR_ANGLE = 75;
		ARM_LOW_TAR_ANGLE = 76;
		rt_thread_mdelay(3000);
		
		ARM_UP_TAR_ANGLE = 75;
		ARM_LOW_TAR_ANGLE = 103;
		rt_thread_mdelay(3000);
		
		ARM_UP_TAR_ANGLE = 101;
		ARM_LOW_TAR_ANGLE = 103;
		rt_thread_mdelay(3000);
    // 如果当前角度等于目标角度，我们不需要做任何事情
}


void ARM_back(void)
{
	ARM_UP_TAR_ANGLE = 88;
	ARM_LOW_TAR_ANGLE = 90;
}

void smooth_move(int x1, int y1, int x2, int y2) {
    int num_steps = 5000; // 可以调整这个数值以改变平滑度
    float dx = (float)(x2 - x1) / num_steps;
    float dy = (float)(y2 - y1) / num_steps;

    for (int i = 0; i <= num_steps; i++) 
	{
        float x = x1 + dx * i;
        float y = y1 + dy * i;
				float angle_low = 139.5739 -0.2598*x; // d=218.75
        float angle_up  = 126.4130  -0.2850 * y; // 使用之前计算的映射关系
        
				// float angle_up = atan(x / 218.75);
				// float angle_low = atan(y / 218.75);
        // 使用你的函数来调整舵机的角度
        ARM_LOW_TAR_ANGLE = angle_low;
        ARM_UP_TAR_ANGLE = angle_up;
        rt_thread_mdelay(1); // 等待一小段时间以便舵机可以移动到新的位置
    }
}






	void arm_init(void)
	{
		pwm_init(ARM_UP_PIN, 200, ARM_CENTER);
		pwm_init(ARM_LOW_PIN, 200, ARM_CENTER);

		ARM_UP_angle(88); // 收回，防止目标检测识别到
		ARM_LOW_angle(90);


		rt_thread_mdelay(2000);
	}
