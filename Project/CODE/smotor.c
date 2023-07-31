#include "smotor.h"

/* BOX
1 - 0°
2 - 90°
3 - 180°
4 - 270°*/

uint8 cur_angle = 1;
uint32 prime = 1;

// 定义机械臂的PWM IO口
#define ARM_UP_PIN PWM1_MODULE0_CHB_D13

#define ARM_CENTER (1.5 * 50000 / 20)





// 设置机械臂角度

void ARM_UP_angle(int angle)
{
	if(angle > 3)
	{
		angle = 3;
	}else if(angle < -3)
	{
		angle = -3;
	}
	pwm_duty(ARM_UP_PIN, 3700-angle * 100);
}


	void arm_init(void)
	{
		pwm_init(ARM_UP_PIN, 50, ARM_CENTER);


		ARM_UP_angle(0); // 收回，防止目标检测识别到

		rt_thread_mdelay(200);
	}
