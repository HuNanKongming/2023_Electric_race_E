#include "right_control.h" 
#include "stm32f10x_gpio.h" 

//LEDӲ����ʼ����������
void Right_dianji_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //����һ�����ų�ʼ���Ľṹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��GPIOAʱ�ӣ�GPIOA������APB2ʱ���£���STM32��ʹ��IO��ǰ��Ҫʹ�ܶ�Ӧʱ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5 | GPIO_Pin_4; //����4
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //�����������ģʽΪ�������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //��������ٶ�Ϊ50MHZ
	GPIO_Init(GPIOA, &GPIO_InitStructure); //�����������úõ�GPIO_InitStructure��������ʼ������GPIOA_PIN4
	GPIO_ResetBits(GPIOA, GPIO_Pin_5); //��ʼ����������GPIOA1Ϊ�ߵ�ƽ
	GPIO_ResetBits(GPIOA, GPIO_Pin_4); //��ʼ����������GPIOA2Ϊ�ߵ�ƽ
}

void Right_dianji_PWM(int pwmzkb)
{
	if(pwmzkb > 0)
	{
		Right_dianji_zhenzhuan(pwmzkb);
	}
	else
	{
		Right_dianji_fanzhuan(-pwmzkb);
	}
}

void Right_dianji_zhenzhuan(int pwmzkb)
{
 	GPIO_ResetBits(GPIOA, GPIO_Pin_4); //��ʼ����������GPIOA4Ϊ�ߵ�ƽ
	GPIO_SetBits(GPIOA, GPIO_Pin_5); //��ʼ����������GPIOA4Ϊ�ߵ�ƽ
	TIM_SetCompare1(TIM4,pwmzkb);	 // �޸�ռ�ձ� 
}

void Right_dianji_fanzhuan(int pwmzkb)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_4); //��ʼ����������GPIOA4Ϊ�ߵ�ƽ
	GPIO_ResetBits(GPIOA, GPIO_Pin_5); //��ʼ����������GPIOA4Ϊ�ߵ�ƽ
	TIM_SetCompare1(TIM4,pwmzkb);	 // �޸�ռ�ձ� 
}


