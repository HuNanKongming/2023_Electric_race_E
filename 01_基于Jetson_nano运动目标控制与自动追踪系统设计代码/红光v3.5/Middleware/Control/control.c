 /**
  ******************************************************************************
  * @文件名 ：control.c
  * @文件说明：此文件为关于PID循迹车控制相关函数和云台相关函数
  ******************************************************************************
**/
#include "control.h"
#define pi 3.1415926
#define MID_PERIOD 75
float WheelOneCircleDis=WheelDiameter*pi;//定义小车轮子行走一圈距离变量

//输入angle的度数为-90到90°，为舵机左右转-90——90°
void Turn_level_Angle(double angle)
{
	if(angle<70){angle=70;}
	else if(angle>110){angle=110;}
		angle=angle-90;
		angle=-angle;
   double duty = MID_PERIOD + 100.0 * (angle / 180.0);
	 TIM4->CCR4=duty;    //GPIOB7,外臂舵机
}

void Turn_vertical_Angle(double angle)
{
	if(angle<70){angle=70;}
	else if(angle>110){angle=110;}
		angle=angle-90;
		angle=-angle;
   double duty = MID_PERIOD + 100.0 * (angle / 180.0);
	 TIM4->CCR3=duty;    //GPIOB7,外臂舵机
}

/**************************************************************************
函数功能：赋值给PWM寄存器,并且判断转向
入口参数：左轮PWM、右轮PWM
返回  值：无
**************************************************************************/
void Set_Pwm(float velocity1,float velocity2)
{	
	Position1+=velocity1;		   //速度的积分，得到舵机的位置
	Position2+=velocity2;
	//赋值给STM32的寄存器
	TIM4->CCR3=Position1;    //GPIOB6,云台舵机
	TIM4->CCR4=Position2;    //GPIOB7,外臂舵机
}

/*************************************************************************
函数功能：位置式PID控制器
入口参数：编码器测量位置信息，目标位置
返回  值：电机PWM增量
**************************************************************************/
float Position_PID_1(float Position,float Target)
{ 	                                          //增量输出
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Target-Position;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 Pwm=Position_KP*Bias/100+Position_KI*Integral_bias/100+Position_KD*(Bias-Last_Bias)/100;       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;  
}
/*************************************************************************
函数功能：位置式PID控制器
入口参数：编码器测量位置信息，目标位置
返回  值：电机PWM增量
**************************************************************************/
float Position_PID_2(float Position,float Target)
{ 	                                         //增量输出
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Target-Position;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 Pwm=Position_KP*Bias/100+Position_KI*Integral_bias/100+Position_KD*(Bias-Last_Bias)/100;       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;  
}

/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  //舵机1脉宽极限值，即限制舵机转角13.5°-256.5°
	  //舵机2脉宽极限值，即限制舵机转角9°   -171°
	  //int Amplitude_H=1200, Amplitude_L=300;       
    int Amplitude_H=80, Amplitude_L=-80; 
		if(RedCx<Amplitude_L)  RedCx=Amplitude_L;	
		if(RedCx>Amplitude_H)  RedCx=Amplitude_H;	
	  if(RedCy<Amplitude_L)  RedCy=Amplitude_L;	
		if(RedCy>Amplitude_H)  RedCy=Amplitude_H;	
}
/**************************************************************************
函数功能：限制速度 
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Velocity(float Velocity1,float Velocity2)
{	
	  int Amplitude_H=Speed, Amplitude_L=-Speed;  
    if(Velocity1<Amplitude_L)  Velocity1=Amplitude_L;	
		if(Velocity1>Amplitude_H)  Velocity1=Amplitude_H;	
	  if(Velocity2<Amplitude_L)  Velocity2=Amplitude_L;	
		if(Velocity2>Amplitude_H)  Velocity2=Amplitude_H;	
}

