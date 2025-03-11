#ifndef _EXTERNPARA_H_
#define _EXTERNPARA_H_
#include "commonhead.h"

#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//��ȡ����2
#define KEY3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//��ȡ����3
#define KEY4  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)//��ȡ����4
#define KEY1_PRES 	1		//KEY1����
#define KEY1_LONG_PRES 	10	//KEY1����������ʱ�����1s��ע�⣺�˴�Ϊ����1s��
#define KEY2_PRES 	2		//KEY1����
#define KEY2_LONG_PRES 	20	//KEY1����������ʱ�����1s
#define KEY3_PRES 	3		//KEY1����
#define KEY3_LONG_PRES 	30	//KEY1����������ʱ�����1s
#define KEY4_PRES 	4		//KEY1����
#define KEY4_LONG_PRES 	40	//KEY1����������ʱ�����1s
#define ENCODER_TIM_PERIOD (u16)(65535)   //���ɴ���65535 ��ΪF103�Ķ�ʱ����16λ�ġ�
/***********************��������������**************************/
#define ACircleLeftEncode 1000	//һȦ1320
#define ACircleRightEncode 1000	//һȦ1320
#define ACircleEncoder ACircleLeftEncode 
#define WheelDiameter 0.064f //����С������ֱ��,6.4cm
#define LED PCout(13);
#define MAX_MOTOR_PWM 800//����������ٶ�ռ�ձ�
extern int mode;
extern int MotorL_PWM;
extern int MotorR_PWM;
extern int num;
extern float	Position_KP,Position_KI,Position_KD;  //λ�ÿ���PID����
extern float Target1, Target2;
extern float Velocity1,Velocity2;     //���PWM����
extern int cursor_x,cursor_y;
extern int Encode_Left;			//�������ֱ�������ȡֵ���������Ļᵼ�´���
extern int Encode_Right;			//�������ֱ�������ȡֵ���������Ļᵼ�´���
extern int Encode_Left_ALL;		//�������ֱ������ۼ�ֵ
extern int Encode_Right_ALL;		//�������ֱ������ۼ�ֵ
extern int	Encode_Speed;			//����ͨ����������ȡ��С��ǰ���ٶ�,����0ǰ���ٶȣ�С��0�����ٶ�
extern int	Encode_Spin_Speed;	//ͨ����������ȡ��С����ת�ٶȣ�������ת�ٶȣ�С��0��ת�ٶ�
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
//================״̬������==========================//
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
extern int delay_50,delay_flag,Bi_zhang,PID_Send,Flash_Send; //��ʱ�͵��εȱ���   
extern float time_t2;
extern float PwmUpx,PwmUpy;
extern int time1count,time2count;
extern float Speed;
extern float Pos[12][2];						//�ڿ��ĸ��������ֵ
extern float ZeroX,ZeroY;
extern float RedCx,RedCy;
extern int OpenmvRedCx,OpenmvRedCy;
extern int OpenmvGreenCx,OpenmvGreenCy;
extern float TargetCxHope,TargetCyHope;
extern float result_x,result_y;
extern double LocX1,LocY1,LocX2,LocY2,LocX3,LocY3,LocX4,LocY4;			//�������ĸ����������ֵ
extern double PX1,PY1,PX2,PY2,PX3,PY3,PX4,PY4,PX5,PY5,PX6,PY6;			//A4ֽ�ĸ����������ֵ
extern double Dx,Dy,Cx,Cy,Bx,By,Ax,Ay;	
#endif


