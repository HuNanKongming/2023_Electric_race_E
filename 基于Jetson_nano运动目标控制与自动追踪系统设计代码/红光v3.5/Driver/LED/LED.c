#include "LED.h" 

//LEDӲ����ʼ����������
//��PA11 PA12 PB3 ��Ϊ�ߵ�ƽLED����
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //�����������ģʽΪ�������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_11|GPIO_Pin_12); //��ʼ����������PA11��PA12Ϊ�ߵ�ƽ
	GPIO_ResetBits(GPIOB, GPIO_Pin_3); //��ʼ����������PB3Ϊ�ߵ�ƽ
}

void Led0_On(void)
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}

void Led0_Off(void)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

void Led1_On(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_11);
}

void Led1_Off(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_11); 
}

void Led2_On(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_12);
}

void Led2_Off(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
}

void Led3_On(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
}

void Led3_Off(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_3);
}
