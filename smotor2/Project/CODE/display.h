#ifndef _display_
#define _display_
#include "headfile.h"


extern rt_mailbox_t display_mailbox;
extern char taget_Big_category[10];



typedef struct
{
    uint8 current;	//当前状态索引号
    uint8 next; 		//向下一个
    uint8 enter; 	//确定
		uint8 back; 		//退出
    void (*current_operation)(void); //当前状态应该执行的操作
} Menu_table;


 

void  Menu_key_set(void);
 
void display_init(void);

#endif




