#include "ExternPara.h"
//���ļ������ⲿ��������
//ͷ�ļ������ⲿ��������

//===============С����Ŀ����=========================//
int num=0;
//=============���������ز���=============//
int MotorL_PWM=500;
int MotorR_PWM=500;
int mode=1;
int leftcount;
int rightcount;
int cursor_x,cursor_y;
//==============ѭ����ز���================//
int LocationTarget=160;
int LocationReal = 0;
//==================PID========================//
float	Position_KP=6,Position_KI=0,Position_KD=3;  //λ�ÿ���PID����
float Position1=750,Position2=750; 
float Target1=750.0f,Target2=750.0f;     //���Ŀ��ֵ
float Velocity1=0.0,Velocity2=0.0;     //���PWM����
int LocationTarget_left=4850; //4860 4850
int LocationTarget_right=4850; 
int SpeedTarget_left=20; 
int SpeedTarget_right=20;
int LocationReal;
int circle = 0;
int Encode_Left=0;			//�������ֱ�������ȡֵ���������Ļᵼ�´���
int Encode_Right=0;			//�������ֱ�������ȡֵ���������Ļᵼ�´���
int Encode_Left_ALL=0;		//�������ֱ������ۼ�ֵ����ʵ�̶ֹ������ƶ�
int Encode_Right_ALL=0;		//�������ֱ������ۼ�ֵ
int	Encode_Speed=0;			//����ͨ����������ȡ��С��ǰ���ٶ�,����0ǰ���ٶȣ�С��0�����ٶ�
int	Encode_Spin_Speed=0;	//ͨ����������ȡ��С����ת�ٶȣ�������ת�ٶȣ�С��0��ת�ٶ�
double x_coordinate;
double y_coordinate;
int delay_50,delay_flag,Bi_zhang,PID_Send,Flash_Send; //��ʱ�͵��εȱ���   
double angel_vertical;
double angel_level;

//===============������Ŀ����=========================//
char Flag1=0;				//��һ��״̬������
char Flag2=0;				//�ڶ���״̬������
char Flag3=0;				//������״̬������
char Flag4=0;				//������״̬������
char Flag5=0;				//������״̬������
char Flag6=0;				//������״̬������
char Flag_youxia=0;				
char Flag_zuoshang=0;
char Flag_youshang=0;	
char Flag_zuoxia=0;	
double angle_level=90,angle_vertical=90;
float Speed=1;                   //�˶��ٶ�����
int time1count=0,time2count=0;
float time_t2=2000.0f;
float PwmUpx=0.0f,PwmUpy=0.0f;
float Pos[12][2]={0};			//б�ڿ��ĸ��������ֵ
float RedCx=0.0F,RedCy=0.0F;
int OpenmvRedCx=0,OpenmvRedCy=0;
int OpenmvGreenCx=0,OpenmvGreenCy=0;
float TargetCxHope,TargetCyHope;
float result_x=0.0f,result_y=0.0f;
float ZeroX=-13.0f,ZeroY=-2.0f;
double LocX1=-63.0f,LocY1=60.0f,LocX2=39.0f,LocY2=58.0f,LocX3=32.0f,LocY3=-74.0f,LocX4=-65.0f,LocY4=-74.0f;			//�������ĸ����������ֵX0ԭ�㣬x1,x2,x3,x4,x5����Ϊ���ϣ����ϣ����£����£�����
double PX1=-47.0f,PY1=66.0f,PX2=1.0f,PY2=67.0f,PX3=-5.0f,PY3=-9.0f,PX4=-48.0f,PY4=-7.0f,PX5=-43.0f,PY5=66.0f;			//A4ֽ�ĸ����������ֵ
double Dx=0.0f,Dy=0.0f,Cx=0.0f,Cy=0.0f,Bx=0.0f,By=0.0f,Ax=0.0f,Ay=0.0f;	

