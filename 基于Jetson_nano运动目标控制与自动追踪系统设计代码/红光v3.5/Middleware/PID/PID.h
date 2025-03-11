#ifndef __PID_H
#define	__PID_H
#include "commonhead.h"
//#include "usart.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    float target_val;           //Ŀ��ֵ
    float actual_val;        		//ʵ��ֵ
    float err;             			//����ƫ��ֵ
    float err_last;          		//������һ��ƫ��ֵ
    float Kp,Ki,Kd;          		//������������֡�΢��ϵ��
    float integral;          		//�������ֵ
}_pid;

//extern _pid pid_speed, pid_speed2;    
extern _pid pid_location_x,pid_location_y,pid_location_x2,pid_location_y2;
extern _pid pid_speed_left,pid_speed_right;
extern _pid pid_location;
void PID_param_init(void);
void set_pid_target(_pid *pid, float temp_val);
float get_pid_target(_pid *pid);
void set_p_i_d(_pid *pid, float p, float i, float d);

float location_pid_realize(_pid *pid, float actual_val);
float speed_pid_realize(_pid *pid, float actual_val);
#endif
