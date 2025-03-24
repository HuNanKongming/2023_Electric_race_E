#include "Beep.h"

void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //引脚输入输出模式为推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化引脚
	GPIO_ResetBits(GPIOB, GPIO_Pin_15); //初始化设置引脚PB15为高电平
}

void Beep_On(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_15);
}

void Beep_Off(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_15);
}