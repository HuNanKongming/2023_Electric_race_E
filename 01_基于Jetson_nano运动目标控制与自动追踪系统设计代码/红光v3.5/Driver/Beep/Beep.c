#include "Beep.h"

void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //�����������ģʽΪ�������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ������
	GPIO_ResetBits(GPIOB, GPIO_Pin_15); //��ʼ����������PB15Ϊ�ߵ�ƽ
}

void Beep_On(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_15);
}

void Beep_Off(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_15);
}