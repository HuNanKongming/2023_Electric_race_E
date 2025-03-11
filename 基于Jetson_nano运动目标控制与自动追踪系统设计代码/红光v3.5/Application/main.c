#include "commonhead.h"

 /**************************************************************************
 * 项目名称：基于Jetson_nano运动目标控制与自动追踪系统设计
 * 版本：V3.5
 * 作者：波动科技6688
 * QQ交流群：2500698745
 * 许可证：MIT License
 * 
 * Copyright (c) 2024 波动科技6688
 * 
 * 本软件根据 MIT 许可证发布，任何人可以自由使用、修改和分发，
 * 但必须包含本声明。
 * 
 * GitHub：https://github.com/HuNanKongming?tab=repositories/ 仓库地址
 **************************************************************************/


int i,j;
void display2()
{
		static int t_ms=1700;
		switch(Flag2)
    {
				case 1: 				//先到左上顶点
					RedCx=LocX1,RedCy=LocY1;
					Flag2=2;
					delay_ms(t_ms);
					break;
				case 2: 				//左上顶点追到右上顶点
					RedCx=LocX2,RedCy=LocY2;
					delay_ms(t_ms);
					Flag2=3;
					break;
				case 3: 				//右上顶点追到右下顶点
					RedCx=LocX3,RedCy=LocY3;
					delay_ms(t_ms);
					Flag2=4;
					break;
				case 4: 				//右下顶点追到左下顶点
					RedCx=LocX4,RedCy=LocY4;
					delay_ms(t_ms);
					Flag2=5;	
					break;
				case 5: 				//右下顶点追到左上顶点
					RedCx=LocX1,RedCy=LocY1;
					delay_ms(t_ms);
					Flag2=6;	
					break;
				case 6: 				//回到原点
					RedCx=ZeroX,RedCy=ZeroY;
					delay_ms(t_ms);
					break;
		}
}

void display3()
{
		static int t_ms=1300;
		switch(Flag3)
    {
				case 1: 				//先到左上顶点
					RedCx=PX1,RedCy=PY1;
					delay_ms(t_ms);
					Flag3=2;
					break;
				case 2: 				//左上顶点追到右上顶点
					RedCx=PX2,RedCy=PY2;
					delay_ms(t_ms);
					Flag3=3;
					break;
				case 3: 				//右上顶点追到右下顶点
					RedCx=PX3,RedCy=PY3;
					delay_ms(t_ms);
					Flag3=4;
					break;
				case 4: 				//右下顶点追到左下顶点
					RedCx=PX4,RedCy=PY4;
					delay_ms(t_ms);
					Flag3=5;	
					break;
				case 5: 				//右下顶点追到左上顶点
					RedCx=PX5,RedCy=PY1;
					delay_ms(t_ms);
					Flag3=6;	
					break;
				case 6: 				//回到原点
					RedCx=ZeroX,RedCy=ZeroY;
					Flag3=7;	
					break;
		}
}

//函数名称：Gotoxy_green
//函数作用：绿光追红光
void Gotoxy(uint8_t Cx, uint8_t Cy)
{
	TargetCxHope=Cx;
	TargetCyHope=Cy;
	TIM_Cmd(TIM1, ENABLE);
	while(1)
	{
		Led1_On();
		if(Cx >= (OpenmvRedCx-2) && Cx <= (OpenmvRedCx+2))
		{
			if(Cy >= (OpenmvRedCy-2) && Cy <= (OpenmvRedCy+2))
			{
				break;
			}				
		}
	}
	Led1_Off();
	TIM_Cmd(TIM1, DISABLE);
}

void display4()
{
		OpenmvModePick2;//openmv切换工作模式
		Ax=Pos[0][0];
		Ay=Pos[0][1];
		Bx=Pos[1][0];
		By=Pos[1][1];
		Cx=Pos[2][0];
		Cy=Pos[2][1]+3;
		Dx=Pos[3][0]+4;
		Dy=Pos[3][1];
		uint16_t i=0,k=15;
		Gotoxy(Ax, Ay);//以A为起始点；以最上点为起点顺时针走一圈
		for(i=0;i<k;i++) // A -> D
		{
			Gotoxy(Ax+((Dx-Ax)/(double)k*i), Ay+((Dy-Ay)/(double)k*i));
		}
		for(i=0;i<k;i++) //D -> C
		{
			Gotoxy(Dx+((Cx-Dx)/(double)k*i), Dy+((Cy-Dy)/(double)k*i));
		}
		for(i=0;i<k;i++) //C ->B
		{
			Gotoxy(Cx+((Bx-Cx)/(double)k*i), Cy+((By-Cy)/(double)k*i));
		}
		for(i=0;i<k;i++) //B->A
		{
			Gotoxy(Bx+((Ax-Bx)/(double)k*i), By+((Ay-By)/(double)k*i));
		}
			Gotoxy(Ax, Ay);
}

//函数名称：Gotoxy_green
//函数作用：红光追opencv坐标系中（Cx，Cy）点
void Gotoxy_green(uint8_t Cx, uint8_t Cy, uint16_t Interval)
{
	uint16_t i=0,k=15;
	TargetCxHope=Cx;
	TargetCyHope=Cy;
	TIM_Cmd(TIM1, ENABLE);
	while(1)
	{
		Beep_Off();
		Gotoxy(OpenmvGreenCx, OpenmvGreenCy);
		if(OpenmvRedCx >= (OpenmvGreenCx-Interval) && OpenmvRedCx <= (OpenmvGreenCx+Interval))
		{
			if(OpenmvRedCy >= (OpenmvGreenCy-Interval) && OpenmvRedCy <= (OpenmvGreenCy+Interval))
			{
				break;
			}				
		}
	}
	Beep_On();
	TIM_Cmd(TIM1, DISABLE);
}

void display()
{
		if(mode==0)//回归(0,0)
		{
			RedCx=0,RedCy=0;
		}
		else if(mode==1)//回归正方形中心
		{
			RedCx=ZeroX,RedCy=ZeroY;
		}
		else if(mode==2)//画50cm大框
		{
			display2();
		}
		else if(mode==3)//画A4纸黑框
		{
			display3();
		}
		else if(mode==4)//画A4纸斜黑框
		{
			display4();
		}
		else if(mode==5)//追绿色激光点
		{
			set_p_i_d(&pid_location_x2, 0.012, 0, 0);
			set_p_i_d(&pid_location_y2, 0.012, 0, 0);
			if(OpenmvGreenCx!=0 && OpenmvGreenCy!= 0)
			{
				Gotoxy_green(OpenmvGreenCx,OpenmvGreenCy,7);
			}
		}
}

int main(void)
{
	InitAll();
	set_p_i_d(&pid_location_x2, 0.018, 0, 0);
	set_p_i_d(&pid_location_y2, 0.018, 0, 0);
	SEGGER_RTT_SetTerminal(0);
	printf("_AllInit Complete_\r\n");
	OpenmvModePick0;
	while(1) 
	{
		display();
		KeyCmd();
		OLED_ShowString(1, 2, "mode:");OLED_ShowNum(1, 8, mode,1);
		OLED_ShowString(2, 2, "x0:");OLED_ShowNum(2, 8, Pos[3][0],3);
		OLED_ShowString(3, 2, "RedCx:");OLED_ShowSignedNum(3, 8, RedCx,4);
		OLED_ShowString(4, 2, "RedCy:");OLED_ShowSignedNum(4, 8, RedCy,4);
	}	
}
