#ifndef _control_h
#define _control_h

#include "headfile.h"


extern double  track_x_kp, track_x_ki, track_x_kd;
extern double  track_y_kp, track_y_ki, track_y_kd;
extern rt_sem_t Tracking_point_sem;


void arm_start_init(void);
int distance(float current_x, float current_y, float target_x, float target_y);
int picture_x_pid(int16 now_x, int16 target_x);
int picture_y_pid(int16 now_y, int16 target_y);


#endif
