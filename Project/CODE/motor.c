#include "motor.h"

#define PWM_LIMIT 10000// 限幅，必须注意安全

#define DIR_1 D0
#define DIR_2 D1
#define PWM_1 PWM2_MODULE3_CHA_D2
#define PWM_2 PWM2_MODULE3_CHB_D3


int32 duty1 = 0, duty2 = 0; // 电机PWM值


float Incremental_kp[4] = {0, 0, 0, 0};
float Incremental_ki[4] = {1, 1 , 1, 1};
float Incremental_kd[4] = {0,0,0,0}; 



float Angel_kp = 7, Angel_ki = 0, Angel_kd = 60; // 角度环





// 电机目标速度
double speed_tar_1 = 0;
double speed_tar_2 = 0;


double speed_tar = 0; // 单位m 目标速度 0.0086*encoder encoder = speed * 116.279 cm/s

void motor_init(void)
{
    gpio_init(DIR_1, GPO, 0, GPIO_PIN_CONFIG); // 单片机端口D0 初始化DIR_1			GPIO
    gpio_init(DIR_2, GPO, 0, GPIO_PIN_CONFIG); // 单片机端口D1 初始化DIR_2			GPIO
    pwm_init(PWM_1, 17000, 0);                 // 单片机端口D2 初始化PWM_1周期10K 占空比0
    pwm_init(PWM_2, 17000, 0);                 // 单片机端口D3 初始化PWM_2周期10K 占空比0


}





void car_stop()
{
    speed_tar_1 = 0;
    speed_tar_2 = 0;

}


int Incremental_pid1(int Target, int Encoder)
{
    static float Bias1, Pwm1, Last_Bias1;
    Bias1 = (float)(Target - Encoder);
    Pwm1 += Incremental_kp[0] * (Bias1 - Last_Bias1)  + Incremental_ki[0] * Bias1;
    Last_Bias1 = Bias1;
    return (int)Pwm1;
}

int Incremental_pid2(int Target, int Encoder)
{
    static float Bias2, Pwm2, Last_Bias2;
    Bias2 = (float)(Target - Encoder);
    Pwm2 += Incremental_kp[1] * (Bias2 - Last_Bias2 )+ Incremental_ki[1] * Bias2;
    Last_Bias2 = Bias2;
    return (int)Pwm2;
}



int angel_pid(int NowAngel, int TargetAngel)
{
    if (NowAngel <= 0)
    {
        if (NowAngel - TargetAngel <= -180)
        {
            NowAngel += 180;
            TargetAngel -= 180;
        }
    }
    else if (NowAngel > 0)
    {
        if (NowAngel - TargetAngel >= 180)
        {
            NowAngel -= 180;
            TargetAngel += 180;
        }
    }
    static float current_error, Speed_Z, Integral_current_error, Last_current_error;
    current_error = (float)(TargetAngel - NowAngel);
    Integral_current_error += current_error;
    Speed_Z = Angel_kp * current_error + Angel_ki * Integral_current_error + Angel_kd * (current_error - Last_current_error);
    Last_current_error = current_error;
    //     rt_kprintf("%d\n",(int)(Speed_Z*1000));

    if (Speed_Z >= 200)
        Speed_Z = 200;
    if (Speed_Z <= -200)
        Speed_Z = -200;
    return (int)Speed_Z;
}




void pid_calculate(void)
{

//	duty1 = Incremental_pid1(speed_tar_1, RC_encoder1); // 计算得到每个电机输出目标值
//	duty2 = Incremental_pid2(speed_tar_2, RC_encoder2);

	duty1 = -Incremental_pid1(100, RC_encoder1); // 计算得到每个电机输出目标值
	duty2 = -Incremental_pid2(100, RC_encoder2);
	
//	duty1 = 3000; // 计算得到每个电机输出目标值
//	duty2 = 3000;


	duty1 = limit(duty1, PWM_LIMIT);
	duty2 = limit(duty2, PWM_LIMIT);

}

//void pid_calculate(void)
//{
//    static float previous_duty1 = 0.0;
//    static float previous_duty2 = 0.0;
//    static float previous_duty3 = 0.0;
//    static float previous_duty4 = 0.0;
//    float acceleration_factor = 0.1; // 缓慢加速的因子

//    float target_duty1 = Incremental_pid1(speed_tar_1, RC_encoder1);
//    float target_duty2 = Incremental_pid2(speed_tar_2, RC_encoder2);
//    float target_duty3 = Incremental_pid3(speed_tar_3, RC_encoder3);
//    float target_duty4 = Incremental_pid4(speed_tar_4, RC_encoder4);

//    duty1 = previous_duty1 + (target_duty1 - previous_duty1) * acceleration_factor;
//    duty2 = previous_duty2 + (target_duty2 - previous_duty2) * acceleration_factor;
//    duty3 = previous_duty3 + (target_duty3 - previous_duty3) * acceleration_factor;
//    duty4 = previous_duty4 + (target_duty4 - previous_duty4) * acceleration_factor;

//    duty1 = limit(duty1, PWM_LIMIT);
//    duty2 = limit(duty2, PWM_LIMIT);
//    duty3 = limit(duty3, PWM_LIMIT);
//    duty4 = limit(duty4, PWM_LIMIT);

//    previous_duty1 = duty1;
//    previous_duty2 = duty2;
//    previous_duty3 = duty3;
//    previous_duty4 = duty4;
//}


void motor_control(bool run)
{
    if (run)
    {
        pid_calculate();
    }
    else
    {
        duty1 = 0;
        duty2 = 0;
    }

    if (duty1 >= 0)
    {
        gpio_set(DIR_1, 0);
        pwm_duty(PWM_1, duty1);
    }
    else
    {
        gpio_set(DIR_1, 1);
        pwm_duty(PWM_1, -duty1);
    }
    if (duty2 >= 0)
    {
        gpio_set(DIR_2, 0);
        pwm_duty(PWM_2, duty2);
    }
    else
    {
        gpio_set(DIR_2, 1);
        pwm_duty(PWM_2, -duty2);
    }
}