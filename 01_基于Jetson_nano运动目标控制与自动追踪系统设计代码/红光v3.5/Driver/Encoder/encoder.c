/**
  ******************************************************************************
  * @�ļ��� servor.c
  * @�ļ�˵�������ļ�Ϊ���ڱ�����������غ����ļ�
  ******************************************************************************/
#include "encoder.h"

/*@brief: ��������ʼ������
 * @param: None
 * @return: None
 */
void Encoder_Init(void)
{
	Encoder_Init_TIM2();//������ʼ������
	Encoder_Init_TIM3();//�ҵ����ʼ������
}
/* @brief: ��λʱ���ȡ����������
 * @param: 
 *			[in] TIMX ��ȡ����������ֵ��λ����ţ���Χ2-3
 * @return: ��ȡ�ı���������ֵ���붨ʱ����ȡʱ���й�
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




