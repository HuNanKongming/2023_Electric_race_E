#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "commonhead.h"

/***************外部函数声明***************/
void Turn_level_Angle(double angle);
void Turn_vertical_Angle(double angle);
void Xianfu_Pwm(void);
void Xianfu_Velocity(float Velocity1,float Velocity2);
int myabs(int a);
void Set_Pwm(float velocity1,float velocity2);
float Position_PID_1(float Position,float Target);
float Position_PID_2(float Position,float Target);
#endif

