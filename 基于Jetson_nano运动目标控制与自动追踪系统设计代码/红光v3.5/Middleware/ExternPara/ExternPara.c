#include "ExternPara.h"
//此文件用于外部变量定义
//头文件用于外部变量声明

//===============小车题目变量=========================//
int num=0;
//=============电机驱动相关参数=============//
int MotorL_PWM=500;
int MotorR_PWM=500;
int mode=1;
int leftcount;
int rightcount;
int cursor_x,cursor_y;
//==============循线相关参数================//
int LocationTarget=160;
int LocationReal = 0;
//==================PID========================//
float	Position_KP=6,Position_KI=0,Position_KD=3;  //位置控制PID参数
float Position1=750,Position2=750; 
float Target1=750.0f,Target2=750.0f;     //电机目标值
float Velocity1=0.0,Velocity2=0.0;     //电机PWM变量
int LocationTarget_left=4850; //4860 4850
int LocationTarget_right=4850; 
int SpeedTarget_left=20; 
int SpeedTarget_right=20;
int LocationReal;
int circle = 0;
int Encode_Left=0;			//定义左轮编码器读取值变量，更改会导致错误
int Encode_Right=0;			//定义右轮编码器读取值变量，更改会导致错误
int Encode_Left_ALL=0;		//定义左轮编码器累加值：可实现固定距离移动
int Encode_Right_ALL=0;		//定义右轮编码器累加值
int	Encode_Speed=0;			//定义通过编码器获取的小车前进速度,大于0前进速度，小于0后退速度
int	Encode_Spin_Speed=0;	//通过编码器获取的小车旋转速度，大于右转速度，小于0左转速度
double x_coordinate;
double y_coordinate;
int delay_50,delay_flag,Bi_zhang,PID_Send,Flash_Send; //延时和调参等变量   
double angel_vertical;
double angel_level;

//===============激光题目变量=========================//
char Flag1=0;				//第一问状态机变量
char Flag2=0;				//第二问状态机变量
char Flag3=0;				//第三问状态机变量
char Flag4=0;				//第四问状态机变量
char Flag5=0;				//第五问状态机变量
char Flag6=0;				//第六问状态机变量
char Flag_youxia=0;				
char Flag_zuoshang=0;
char Flag_youshang=0;	
char Flag_zuoxia=0;	
double angle_level=90,angle_vertical=90;
float Speed=1;                   //运动速度设置
int time1count=0,time2count=0;
float time_t2=2000.0f;
float PwmUpx=0.0f,PwmUpy=0.0f;
float Pos[12][2]={0};			//斜黑框四个点的坐标值
float RedCx=0.0F,RedCy=0.0F;
int OpenmvRedCx=0,OpenmvRedCy=0;
int OpenmvGreenCx=0,OpenmvGreenCy=0;
float TargetCxHope,TargetCyHope;
float result_x=0.0f,result_y=0.0f;
float ZeroX=-13.0f,ZeroY=-2.0f;
double LocX1=-63.0f,LocY1=60.0f,LocX2=39.0f,LocY2=58.0f,LocX3=32.0f,LocY3=-74.0f,LocX4=-65.0f,LocY4=-74.0f;			//正方形四个顶点的坐标值X0原点，x1,x2,x3,x4,x5依次为左上，右上，右下，左下，中心
double PX1=-47.0f,PY1=66.0f,PX2=1.0f,PY2=67.0f,PX3=-5.0f,PY3=-9.0f,PX4=-48.0f,PY4=-7.0f,PX5=-43.0f,PY5=66.0f;			//A4纸四个顶点的坐标值
double Dx=0.0f,Dy=0.0f,Cx=0.0f,Cy=0.0f,Bx=0.0f,By=0.0f,Ax=0.0f,Ay=0.0f;	

