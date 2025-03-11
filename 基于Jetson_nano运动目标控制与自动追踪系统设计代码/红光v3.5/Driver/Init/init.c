#include "init.h"
#include "vl53l0x.h"
#include "vl53l0x_gen.h"

extern VL53L0X_Dev_t vl53l0x_dev;//�豸I2C���ݲ���TOF
VL53L0X_Error Status=VL53L0X_ERROR_NONE;//����״̬

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
	TIM2_Int_Init(999,3599);  //arr:�Զ���װ��ֵ��psc:Ԥ��Ƶϵ��5HZ
	RedCx=0,RedCy=0;
	Timer1_Init(999,89);				   //��ʱ��TIM1 9Mhz ��ʱ10msһ���ж�
	PID_param_init();
}

