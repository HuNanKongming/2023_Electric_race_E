 /**
  ******************************************************************************
  * @�ļ��� ��control.c
  * @�ļ�˵�������ļ�Ϊ����PIDѭ����������غ�������̨��غ���
  ******************************************************************************
**/
#include "control.h"
#define pi 3.1415926
#define MID_PERIOD 75
float WheelOneCircleDis=WheelDiameter*pi;//����С����������һȦ�������

//����angle�Ķ���Ϊ-90��90�㣬Ϊ�������ת-90����90��
void Turn_level_Angle(double angle)
{
	if(angle<70){angle=70;}
	else if(angle>110){angle=110;}
		angle=angle-90;
		angle=-angle;
   double duty = MID_PERIOD + 100.0 * (angle / 180.0);
	 TIM4->CCR4=duty;    //GPIOB7,��۶��
}

void Turn_vertical_Angle(double angle)
{
	if(angle<70){angle=70;}
	else if(angle>110){angle=110;}
		angle=angle-90;
		angle=-angle;
   double duty = MID_PERIOD + 100.0 * (angle / 180.0);
	 TIM4->CCR3=duty;    //GPIOB7,��۶��
}

/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���,�����ж�ת��
��ڲ���������PWM������PWM
����  ֵ����
**************************************************************************/
void Set_Pwm(float velocity1,float velocity2)
{	
	Position1+=velocity1;		   //�ٶȵĻ��֣��õ������λ��
	Position2+=velocity2;
	//��ֵ��STM32�ļĴ���
	TIM4->CCR3=Position1;    //GPIOB6,��̨���
	TIM4->CCR4=Position2;    //GPIOB7,��۶��
}

/*************************************************************************
�������ܣ�λ��ʽPID������
��ڲ���������������λ����Ϣ��Ŀ��λ��
����  ֵ�����PWM����
**************************************************************************/
float Position_PID_1(float Position,float Target)
{ 	                                          //�������
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Target-Position;                                  //����ƫ��
	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	 Pwm=Position_KP*Bias/100+Position_KI*Integral_bias/100+Position_KD*(Bias-Last_Bias)/100;       //λ��ʽPID������
	 Last_Bias=Bias;                                       //������һ��ƫ�� 
	 return Pwm;  
}
/*************************************************************************
�������ܣ�λ��ʽPID������
��ڲ���������������λ����Ϣ��Ŀ��λ��
����  ֵ�����PWM����
**************************************************************************/
float Position_PID_2(float Position,float Target)
{ 	                                         //�������
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Target-Position;                                  //����ƫ��
	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	 Pwm=Position_KP*Bias/100+Position_KI*Integral_bias/100+Position_KD*(Bias-Last_Bias)/100;       //λ��ʽPID������
	 Last_Bias=Bias;                                       //������һ��ƫ�� 
	 return Pwm;  
}

/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  //���1������ֵ�������ƶ��ת��13.5��-256.5��
	  //���2������ֵ�������ƶ��ת��9��   -171��
	  //int Amplitude_H=1200, Amplitude_L=300;       
    int Amplitude_H=80, Amplitude_L=-80; 
		if(RedCx<Amplitude_L)  RedCx=Amplitude_L;	
		if(RedCx>Amplitude_H)  RedCx=Amplitude_H;	
	  if(RedCy<Amplitude_L)  RedCy=Amplitude_L;	
		if(RedCy>Amplitude_H)  RedCy=Amplitude_H;	
}
/**************************************************************************
�������ܣ������ٶ� 
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Velocity(float Velocity1,float Velocity2)
{	
	  int Amplitude_H=Speed, Amplitude_L=-Speed;  
    if(Velocity1<Amplitude_L)  Velocity1=Amplitude_L;	
		if(Velocity1>Amplitude_H)  Velocity1=Amplitude_H;	
	  if(Velocity2<Amplitude_L)  Velocity2=Amplitude_L;	
		if(Velocity2>Amplitude_H)  Velocity2=Amplitude_H;	
}

