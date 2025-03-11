/**
  ******************************************************************************
  * @文件名 servor.c
  * @文件说明：本文件为关于编码器控制相关函数文件
  ******************************************************************************/
#include "encoder.h"

/*@brief: 编码器初始化函数
 * @param: None
 * @return: None
 */
void Encoder_Init(void)
{
	Encoder_Init_TIM2();//左电机初始化函数
	Encoder_Init_TIM3();//右电机初始化函数
}
/* @brief: 单位时间读取编码器计数
 * @param: 
 *			[in] TIMX 读取编码器计数值定位器编号，范围2-3
 * @return: 读取的编码器计数值，与定时器读取时间有关
 */
int Read_Encoder(u8 TIMX)
{
	int Encoder_TIM;    
	switch(TIMX)
	{
		case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
		case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		default:  Encoder_TIM=0;
	}
	return Encoder_TIM;
}




