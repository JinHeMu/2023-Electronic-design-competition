#ifndef _smotor_h
#define _smotor_h

#include "headfile.h"


extern float ARM_UP_CURRENT_ANGLE;
extern float ARM_LOW_CURRENT_ANGLE;

extern float ARM_UP_TAR_ANGLE;
extern float ARM_LOW_TAR_ANGLE;

void arm_init(void);
void ARM_UP_MOVE(float target);
void ARM_LOW_MOVE(float target);
void ARM_scan_rectangle(void);
void ARM_back(void);
void smooth_move(float x1, float y1, float x2, float y2);
void smooth_move_angle(float x1, float y1, float x2, float y2);
void ARM_UP_angle(float angle);
void ARM_LOW_angle(float angle);


#endif
