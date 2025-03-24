#include "left_control.h" 
#include "stm32f10x_gpio.h" 

//LED硬件初始化函数定义
void Left_dianji_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义一个引脚初始化的结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能GPIOA时钟，GPIOA挂载在APB2时钟下，在STM32中使用IO口前都要使能对应时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4 | GPIO_Pin_5; //引脚4
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //引脚输入输出模式为推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //引脚输出速度为50MHZ
	GPIO_Init(GPIOB, &GPIO_InitStructure); //根据上面设置好的GPIO_InitStructure参数，初始化引脚GPIOA_PIN4
	GPIO_ResetBits(GPIOB, GPIO_Pin_4); //初始化设置引脚GPIOA4为高电平
	GPIO_ResetBits(GPIOB, GPIO_Pin_5); //初始化设置引脚GPIOA4为高电平
}

void Left_dianji_PWM(int pwmzkb)
{
	if(pwmzkb > 0)
	{
		Left_dianji_zhenzhuan(pwmzkb);
	}
	else
	{
		Left_dianji_fanzhuan(-pwmzkb);
	}
}

void Left_dianji_zhenzhuan(int pwmzkb)
{
 	GPIO_ResetBits(GPIOB, GPIO_Pin_4); //初始化设置引脚GPIOA4为高电平
	GPIO_SetBits(GPIOB, GPIO_Pin_5); //初始化设置引脚GPIOA4为高电平
	TIM_SetCompare2(TIM4,pwmzkb);
}

void Left_dianji_fanzhuan(int pwmzkb)
{
 	GPIO_SetBits(GPIOB, GPIO_Pin_4); //初始化设置引脚GPIOA4为高电平
	GPIO_ResetBits(GPIOB, GPIO_Pin_5); //初始化设置引脚GPIOA4为高电平
	TIM_SetCompare2(TIM4,pwmzkb);
}



