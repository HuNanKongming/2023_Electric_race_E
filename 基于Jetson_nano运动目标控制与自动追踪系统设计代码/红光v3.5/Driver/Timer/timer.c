#include "timer.h"

void Timer1_Init(u16 arr,u16 psc)
{   
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //TIM1ʱ��ʹ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM1�ж�
		TIM1, //TIM1
		TIM_IT_Update  |  //TIM1 �ж�Դ
		TIM_IT_Trigger,   //TIM1 �����ж�Դ ����
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM1�ж�  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���						 
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1	
}

//ͨ�ö�ʱ��2��ʼ��������arr:�Զ���װ��ֵ��psc:Ԥ��Ƶϵ����Ĭ�϶�ʱʱ��Ϊ72MHZʱ�����߹�ͬ������ʱ�ж�ʱ��
void TIM2_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue; //����һ����ʱ�жϵĽṹ��
	NVIC_InitTypeDef NVIC_InitStrue; //����һ���ж����ȼ���ʼ���Ľṹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʹ��ͨ�ö�ʱ��2ʱ��
	TIM_TimeBaseInitStrue.TIM_Period=arr; //����ģʽΪ���ϼ���ʱ����ʱ����0��ʼ����������������arrʱ������ʱ�жϷ�����
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //Ԥ��Ƶϵ��������ÿһ��������ʱ��
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //����ģʽ�����ϼ���
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //һ�㲻ʹ�ã�Ĭ��TIM_CKD_DIV1
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStrue); //����TIM_TimeBaseInitStrue�Ĳ�����ʼ����ʱ��TIM2
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //ʹ��TIM2�жϣ��ж�ģʽΪ�����жϣ�TIM_IT_Update
	NVIC_InitStrue.NVIC_IRQChannel=TIM2_IRQn; //����TIM2�ж�
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE; //�ж�ʹ��
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�Ϊ1����ֵԽС���ȼ�Խ�ߣ�0�����ȼ����
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2; //��Ӧ���ȼ�Ϊ1����ֵԽС���ȼ�Խ�ߣ�0�����ȼ����
	NVIC_Init(&NVIC_InitStrue); //����NVIC_InitStrue�Ĳ�����ʼ��VIC�Ĵ���������TIM2�ж�
	TIM_Cmd(TIM2, ENABLE); //ʹ�ܶ�ʱ��TIM2
}

void Encoder_Init_TIM2(void)//���ֱ�������ʼ��
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;//*
  /* Encoder unit connected to TIM2, 4X mode */    
  GPIO_InitTypeDef GPIO_InitStructure;
  //NVIC_InitTypeDef NVIC_InitStructure;
  /* TIM2 clock source enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  /* Enable GPIOA, clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PA.06,07 as encoder input */
	//PA0��PA1�Ƕ�ʱ��2��ͨ��1��ͨ��2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Enable the TIM2 Update Interrupt */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //���ȼ����
//  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
  /* Timer configuration in Encoder mode */
//  TIM_DeInit(TIM2);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
//  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;  
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ 
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  //TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling); //TIM_ICPolarity_Rising�����ز���
  //TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge); //TIM_ICPolarity_Rising�����ز���
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); //TIM_ICPolarity_Rising�����ز���
  TIM_ICStructInit(&TIM_ICInitStructure);
//  TIM_ICInitStructure.TIM_ICFilter = 6; //���˲���
	TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
 // Clear all pending interrupts
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	  //ʹ���ж�
  //Reset counter
	TIM_SetCounter(TIM2,0);
//  TIM2->CNT = 32768;
  //TIM2->CNT = 0;
//  ENC_Clear_Speed_Buffer();
  TIM_Cmd(TIM2, ENABLE);  	   //ʹ�ܶ�ʱ��3
}

void Encoder_Init_TIM3(void)//���ֱ�������ʼ��
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
//  NVIC_InitTypeDef NVIC_InitStructure;
/* Encoder unit connected to TIM3, 4X mode */    
  GPIO_InitTypeDef GPIO_InitStructure;
  //NVIC_InitTypeDef NVIC_InitStructure;
  /* TIM3 clock source enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  /* Enable GPIOA, clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
	//PA6��PA7�Ƕ�ʱ��4��ͨ��1��ͨ��2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Enable the TIM3 Update Interrupt */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //���ȼ����
//  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
  /* Timer configuration in Encoder mode */
//  TIM_DeInit(TIM3);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
//  TIM_TimeBaseStructure.TIM_Period = 0xffff;  
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ 
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
//  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge); //TIM_ICPolarity_Rising�����ز���
 TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
 TIM_ICStructInit(&TIM_ICInitStructure);
//  TIM_ICInitStructure.TIM_ICFilter = 6; //���˲���
	TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
 // Clear all pending interrupts
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);	  //ʹ���ж�
  //Reset counter
  //TIM3->CNT = 0;
//  TIM3->CNT = 64215;
	TIM_SetCounter(TIM3,0);
//  ENC_Clear_Speed_Buffer();
	TIM_Cmd(TIM3, ENABLE);  	   //ʹ�ܶ�ʱ��3
}

void TIM4_PWM_Init(u16 arr, u16 psc)//δ��
{
	GPIO_InitTypeDef GPIO_InitStructure; //����һ�����ų�ʼ���Ľṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue; //����һ����ʱ�жϵĽṹ��	
	TIM_OCInitTypeDef TIM_OCInitTypeStrue; //����һ��PWM����Ľṹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��GPIOAʱ�ӣ���STM32��ʹ��IO��ǰ��Ҫʹ�ܶ�Ӧʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ��ͨ�ö�ʱ��2ʱ�ӣ�A0���Ŷ�ӦTIM2CHN1
//	TIM_DeInit(TIM4);
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_8 | GPIO_Pin_9;//����1
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; //�����������ģʽ����ʱ������ΪA0���Ÿ��ù���
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //�������������ٶ�Ϊ50MHZ
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ������GPIOA0
	TIM_TimeBaseInitStrue.TIM_Period=arr; //����ģʽΪ���ϼ���ʱ����ʱ����0��ʼ����������������arrʱ������ʱ�жϷ�����
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //Ԥ��Ƶϵ��������ÿһ��������ʱ��
//	TIM_TimeBaseInitStrue.TIM_ClockDivision = 0; 
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //����ģʽ�����ϼ���
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //һ�㲻ʹ�ã�Ĭ��TIM_CKD_DIV1
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStrue); //����TIM_TimeBaseInitStrue�Ĳ�����ʼ����ʱ��TIM2	
	TIM_OCInitTypeStrue.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitTypeStrue.TIM_OCPolarity = TIM_OCPolarity_Low;
 	TIM_OCInitTypeStrue.TIM_OutputState = TIM_OutputState_Enable;
 	TIM_OCInitTypeStrue.TIM_Pulse = 0; 
	TIM_OC1Init(TIM4, &TIM_OCInitTypeStrue);  
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Disable); 
	TIM_OCInitTypeStrue.TIM_Pulse = 500; 
	TIM_OCInitTypeStrue.TIM_OCMode = TIM_OCMode_PWM2; 
 	TIM_OCInitTypeStrue.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitTypeStrue.TIM_OCPolarity = TIM_OCPolarity_Low; 
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  
	TIM_OC3Init(TIM4, &TIM_OCInitTypeStrue);  
	TIM_OCInitTypeStrue.TIM_Pulse = 500; 
	TIM_OCInitTypeStrue.TIM_OCMode = TIM_OCMode_PWM2; 
 	TIM_OCInitTypeStrue.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitTypeStrue.TIM_OCPolarity = TIM_OCPolarity_Low; 
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  
	TIM_OC4Init(TIM4, &TIM_OCInitTypeStrue);  
 	TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	TIM_SetCompare1(TIM4,0);
	TIM_SetCompare2(TIM4,0);  
	TIM_SetCompare3(TIM4,0);
	TIM_SetCompare4(TIM4,0);
}



