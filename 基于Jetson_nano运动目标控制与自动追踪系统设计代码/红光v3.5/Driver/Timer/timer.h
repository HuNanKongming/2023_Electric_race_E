#ifndef __TIMER_H
#define __TIMER_H	


#include "commonhead.h"


void Timer1_Init(u16 arr, u16 psc);//定时器1初始化
void Encoder_Init_TIM2(void);//定时器2初始化+编码器
void Encoder_Init_TIM3(void);//定时器3初始化+编码器
void TIM4_PWM_Init(u16 arr, u16 psc);
void TIM2_Int_Init(u16 arr, u16 psc);
#endif
