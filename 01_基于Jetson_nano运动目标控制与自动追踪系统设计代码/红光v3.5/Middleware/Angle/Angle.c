#include "Angle.h"
double anglex[25]={0};
double angley[25]={0};
double anglebox=0;
#define PI 3.14159
void GetAngle(int x,int y)
{
	double thyta;
	int i,j;
	if(x>=0)
	{
		for(i=0;i<x;i++)
		{
			thyta=atan(i/100.0)*180/PI;
			anglex[i]=thyta;
		}
	}
	else if(x<0)
	{
		x=-x;
		for(i=0;i<x;i++)
		{
			thyta=atan(i/100.0)*180/PI;
			anglex[i]=-thyta;
		}
	}
	if(y>=0)
	{
		for(j=0;j<y;j++)
		{
			thyta=atan(j/100.0)*180/PI;
			angley[j]=thyta;
		}
	}
	else if(y<0)
	{
		y=-y;
		for(j=0;j<y;j++)
		{
			thyta=atan(j/100.0)*180/PI;
			angley[j]=-thyta;
		}
	}
}
//(0,0,25,25)->(25,25,25,-25)->(25,-25,-25,-25)
void DrawLine(void)
{
	int num=10;
	GetAngle(-25,25);
	for(int i=0;i<25;i++)
	{
		Turn_level_Angle(90+anglex[i]);
		Turn_vertical_Angle(90+angley[i]);
		delay_ms(20);
	}
	while(num--)
	{
		anglebox=anglex[24];
		GetAngle(25,25);
		for(int i=0;i<25;i++)
		{
			Turn_level_Angle(90+anglex[i]+anglebox);
			delay_ms(20);
		}
		for(int i=0;i<25;i++)
		{
			Turn_level_Angle(90+anglex[i]);
			delay_ms(20);
		}
		anglebox=angley[24];
		GetAngle(25,-25);
		for(int i=0;i<25;i++)
		{
			Turn_vertical_Angle(90+angley[i]+anglebox);
			delay_ms(20);
		}
		for(int i=0;i<25;i++)
		{
			Turn_vertical_Angle(90+angley[i]);
			delay_ms(20);
		}
		anglebox=anglex[24];
		GetAngle(-25,-25);
		for(int i=0;i<25;i++)
		{
			Turn_level_Angle(90+anglex[i]+anglebox);
			delay_ms(20);
		}
		for(int i=0;i<25;i++)
		{
			Turn_level_Angle(90+anglex[i]);
			delay_ms(20);
		}
		anglebox=angley[24];
		GetAngle(-25,25);
		for(int i=0;i<25;i++)
		{
			Turn_vertical_Angle(90+angley[i]+anglebox);
			delay_ms(20);
		}
		for(int i=0;i<25;i++)
		{
			Turn_vertical_Angle(90+angley[i]);
			delay_ms(20);
		}
	}
}

void DirectLine(int x1,int y1,int x2,int y2)
{
	double dx,dy,boxx,boxy,thyta;
	int nx,ny;									//份数
	dx=abs(x1-x2);
	dy=abs(y1-y2);
	
	GetAngle(x1,y1);						//从原点定位向量起点,假如=25，25
	for(int i=0;i<x1;i++)
	{
		Turn_level_Angle(90+anglex[i]);
		Turn_vertical_Angle(90+angley[i]);
		delay_ms(20);
	}
	
	boxx=anglex[x1-1];
	boxy=angley[y1-1];
	
	//25,25->25,-25
	for(int j=0;j<dy;j++)
	{
		//Turn_level_Angle(90+anglex[i]);
		ny=y1+j;
		if(ny>=0)
		{
			thyta=atan(j/100.0)*180/PI;
		}
		else if(ny<0)
		{
			ny=-ny;
			thyta=-atan(j/100.0)*180/PI;
		}
		Turn_vertical_Angle(90+boxy+thyta);
		delay_ms(20);
	}
	
}