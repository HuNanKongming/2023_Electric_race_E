#ifndef _EXTERNPARA_H_
#define _EXTERNPARA_H_
#include "commonhead.h"

#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//读取按键2
#define KEY3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//读取按键3
#define KEY4  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)//读取按键4
#define KEY1_PRES 	1		//KEY1按下
#define KEY1_LONG_PRES 	10	//KEY1长按，长按时间大于1s（注意：此处为近似1s）
#define KEY2_PRES 	2		//KEY1按下
#define KEY2_LONG_PRES 	20	//KEY1长按，长按时间大于1s
#define KEY3_PRES 	3		//KEY1按下
#define KEY3_LONG_PRES 	30	//KEY1长按，长按时间大于1s
#define KEY4_PRES 	4		//KEY1按下
#define KEY4_LONG_PRES 	40	//KEY1长按，长按时间大于1s
#define ENCODER_TIM_PERIOD (u16)(65535)   //不可大于65535 因为F103的定时器是16位的。
/***********************编码器参数定义**************************/
#define ACircleLeftEncode 1000	//一圈1320
#define ACircleRightEncode 1000	//一圈1320
#define ACircleEncoder ACircleLeftEncode 
#define WheelDiameter 0.064f //定义小车轮子直径,6.4cm
#define LED PCout(13);
#define MAX_MOTOR_PWM 800//定义电机最大速度占空比
extern int mode;
extern int MotorL_PWM;
extern int MotorR_PWM;
extern int num;
extern float	Position_KP,Position_KI,Position_KD;  //位置控制PID参数
extern float Target1, Target2;
extern float Velocity1,Velocity2;     //电机PWM变量
extern int cursor_x,cursor_y;
extern int Encode_Left;			//定义左轮编码器读取值变量，更改会导致错误
extern int Encode_Right;			//定义右轮编码器读取值变量，更改会导致错误
extern int Encode_Left_ALL;		//定义左轮编码器累加值
extern int Encode_Right_ALL;		//定义右轮编码器累加值
extern int	Encode_Speed;			//定义通过编码器获取的小车前进速度,大于0前进速度，小于0后退速度
extern int	Encode_Spin_Speed;	//通过编码器获取的小车旋转速度，大于右转速度，小于0左转速度
extern int LocationTarget;
extern int LocationReal;
extern int circle;
extern int LocationReal;
extern int LocationTarget_left; //4860 4850
extern int LocationTarget_right; //4860 4850
extern int SpeedTarget_left; 
extern int SpeedTarget_right; 
extern double x_coordinate;
extern double y_coordinate;
extern float Position1,Position2;   
extern double angel_vertical;
extern double angel_level;
//================状态机变量==========================//
extern char Flag1;
extern char Flag2;
extern char Flag3;
extern char Flag4;
extern char Flag5;
extern char Flag6;
extern char Flag_youxia;				
extern char Flag_zuoshang;
extern char Flag_youshang;	
extern char Flag_zuoxia;	
extern double angle_level,angle_vertical;
extern int delay_50,delay_flag,Bi_zhang,PID_Send,Flash_Send; //延时和调参等变量   
extern float time_t2;
extern float PwmUpx,PwmUpy;
extern int time1count,time2count;
extern float Speed;
extern float Pos[12][2];						//黑框四个点的坐标值
extern float ZeroX,ZeroY;
extern float RedCx,RedCy;
extern int OpenmvRedCx,OpenmvRedCy;
extern int OpenmvGreenCx,OpenmvGreenCy;
extern float TargetCxHope,TargetCyHope;
extern float result_x,result_y;
extern double LocX1,LocY1,LocX2,LocY2,LocX3,LocY3,LocX4,LocY4;			//正方形四个顶点的坐标值
extern double PX1,PY1,PX2,PY2,PX3,PY3,PX4,PY4,PX5,PY5,PX6,PY6;			//A4纸四个顶点的坐标值
extern double Dx,Dy,Cx,Cy,Bx,By,Ax,Ay;	
#endif


