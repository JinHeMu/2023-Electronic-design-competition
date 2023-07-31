#ifndef _motor_h
#define _motor_h

#include "headfile.h"





extern double speed_tar;
extern int32 duty1,duty2;//电机PWM值


extern float Incremental_kp[4], Incremental_ki[4], Incremental_kd[4];//增量式PID，控制电机输出值
extern float Angel_kp, Angel_ki, Angel_kd;//角度环

void motor_init(void);
void motor_control(bool run);



int angel_pid(int NowAngel,int TargetAngel);


#endif