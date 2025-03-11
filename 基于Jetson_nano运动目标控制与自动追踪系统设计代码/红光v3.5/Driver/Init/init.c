#include "init.h"
#include "vl53l0x.h"
#include "vl53l0x_gen.h"

extern VL53L0X_Dev_t vl53l0x_dev;//设备I2C数据参数TOF
VL53L0X_Error Status=VL53L0X_ERROR_NONE;//工作状态

void InitAll(void)
{
	delay_init();
	LED_Init();
	Beep_Init();
	KEY_Init();
	USART1_Config();
	USART2_Config();
	NVIC_Config();
	OLED_Init();
	TIM4_PWM_Init(9999,71);
	TIM2_Int_Init(999,3599);  //arr:自动重装载值，psc:预分频系数5HZ
	RedCx=0,RedCy=0;
	Timer1_Init(999,89);				   //定时器TIM1 9Mhz 定时10ms一次中断
	PID_param_init();
}

