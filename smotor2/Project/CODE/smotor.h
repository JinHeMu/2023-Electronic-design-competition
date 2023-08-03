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
void smooth_move(int x1, int y1, int x2, int y2) ;
void ARM_UP_angle(float angle);
void ARM_LOW_angle(float angle);


#endif
