#ifndef __ENCODER_H_
#define __ENCODER_H_

#include "commonhead.h"






/*************************�ⲿ��������**************************/

//extern int Encode_Left;			//�������ֱ�������ȡֵ���������Ļᵼ�´���
//extern int Encode_Right;		//�������ֱ�������ȡֵ���������Ļᵼ�´���
//extern int Encode_Left_ALL;		//�������ֱ������ۼ�ֵ
//extern int Encode_Right_ALL;	//�������ֱ������ۼ�ֵ
//extern int	Encode_Speed;		//����ͨ����������ȡ��С��ǰ���ٶ�
//extern int	Encode_Spin_Speed;	//ͨ����������ȡ��С����ת�ٶ�

/*************************�ⲿ��������**************************/
void Encoder_Init(void);		//��������ʼ������
int Read_Encoder(u8 TIMX);   //����������ֵ



#endif





