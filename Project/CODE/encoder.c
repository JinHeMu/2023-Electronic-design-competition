#include "encoder.h"

//---------------------�ṹ��---------------------//
struct RC_Para Encoder1_Para = {0, 0, 0.25}; // ��ͨ�˲�
struct RC_Para Encoder2_Para = {0, 0, 0.25};
struct RC_Para Encoder3_Para = {0, 0, 0.25};
struct RC_Para Encoder4_Para = {0, 0, 0.25};

RC_Filter_pt RC_Encoder1 = &Encoder1_Para;
RC_Filter_pt RC_Encoder2 = &Encoder2_Para;



int16 encoder1=0,encoder2=0,encoder3=0,encoder4=0;//��������ֵ
int16 RC_encoder1, RC_encoder2, RC_encoder3, RC_encoder4; // �˲�֮��encoder��ֵ

void encoder_init(void)
{
  // ��ʼ�� QTIMER_1 A��ʹ��QTIMER1_TIMER2_C2 B��ʹ��QTIMER1_TIMER3_C24
  qtimer_quad_init(QTIMER_1, QTIMER1_TIMER0_C0, QTIMER1_TIMER1_C1);
  qtimer_quad_init(QTIMER_1, QTIMER1_TIMER2_C2, QTIMER1_TIMER3_C24);
}


void encoder_get(void)
{

  encoder1 = -qtimer_quad_get(QTIMER_1, QTIMER1_TIMER0_C0); // ������Ҫע��ڶ������������дA������
  encoder2 = qtimer_quad_get(QTIMER_1, QTIMER1_TIMER2_C2);

  RC_encoder1 = (int16_t)RCFilter(encoder1, RC_Encoder1); // ��ͨ�˲�
  RC_encoder2 = (int16_t)RCFilter(encoder2, RC_Encoder2);

  qtimer_quad_clear(QTIMER_1, QTIMER1_TIMER0_C0);
  qtimer_quad_clear(QTIMER_1, QTIMER1_TIMER2_C2);

}