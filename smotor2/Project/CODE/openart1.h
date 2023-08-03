#ifndef __OPENART1_H__
#define __OPENART1_H__

#include "headfile.h"



extern char classified[10];

extern int16 ART1_POINT_X,ART1_POINT_Y;
extern uint8 coordinate_num;
extern uint8 ART1_mode;
extern uint8 point_num; // 数据个数
extern uint8 ART1_CLASS_Flag;

extern uint8 ART1_dat[20];

void ART1_UART_Init(void);



#endif