#ifndef __TIMER_H
#define __TIMER_H	


#include "commonhead.h"


void Timer1_Init(u16 arr, u16 psc);//��ʱ��1��ʼ��
void Encoder_Init_TIM2(void);//��ʱ��2��ʼ��+������
void Encoder_Init_TIM3(void);//��ʱ��3��ʼ��+������
void TIM4_PWM_Init(u16 arr, u16 psc);
void TIM2_Int_Init(u16 arr, u16 psc);
#endif
