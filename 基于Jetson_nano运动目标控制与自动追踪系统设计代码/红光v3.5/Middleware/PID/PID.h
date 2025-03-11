#ifndef __PID_H
#define	__PID_H
#include "commonhead.h"
//#include "usart.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    float target_val;           //目标值
    float actual_val;        		//实际值
    float err;             			//定义偏差值
    float err_last;          		//定义上一个偏差值
    float Kp,Ki,Kd;          		//定义比例、积分、微分系数
    float integral;          		//定义积分值
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
