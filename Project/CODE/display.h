#ifndef _display_
#define _display_
#include "headfile.h"


extern rt_mailbox_t display_mailbox;
extern char taget_Big_category[10];



typedef struct
{
    uint8 current;	//��ǰ״̬������
    uint8 next; 		//����һ��
    uint8 enter; 	//ȷ��
		uint8 back; 		//�˳�
    void (*current_operation)(void); //��ǰ״̬Ӧ��ִ�еĲ���
} Menu_table;


 

void  Menu_key_set(void);
 
void display_init(void);

#endif




