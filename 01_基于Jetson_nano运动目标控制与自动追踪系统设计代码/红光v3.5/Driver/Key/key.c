#include "key.h"

//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//KEY2
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//KEY3
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能GPIOA时钟，GPIOA挂载在APB2时钟下，在STM32中使用IO口前都要使能对应时钟
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//KEY4
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC
}

//此函数为按键扫描函数
// return: 按键按下的结果，按键短按时返回KEYx_PRES,按下长按时间大于1S（近似）时返回KEYx_LONG_PRES
u8 KEY_Scan(void)
{	 
	static u8 key1_up=1,key2_up=1,key3_up=1,key4_up=1;//按键按松开标志，按下时为1，松开时为0
	static u16 key1timecount=0,key2timecount=0,key3timecount=0,key4timecount=0;	  
	if(key1_up&&(KEY1==0))//若按键按下且引脚被拉低
	{
		delay_ms(10);//去抖动 
		if(KEY1==0) key1_up=0;
	}
	else if(KEY1==1)//按键引脚仍为高电平（未按下）
	{
		if(key1_up==0)
		{
			key1_up=1; 			
			if(key1timecount<30)
			{
				key1timecount=0;
				return KEY1_PRES;
			}
			key1timecount=0;
		}
	}
	if(key1_up==0)//如果按键按下则按10ms时间计时
	{
		delay_ms(10);
		key1timecount++;
		if(key1timecount==30)//如果长按时间大于1s则返回按键长按
		{
			return KEY1_LONG_PRES;
		}	
	}
	if(key2_up&&(KEY2==0))//若按键按下且引脚被拉低
	{
		delay_ms(10);//去抖动 
		if(KEY2==0) key2_up=0;
	}
	else if(KEY2==1)//按键引脚仍为高电平（未按下）
	{
		if(key2_up==0)
		{
			key2_up=1; 			
			if(key2timecount<30)
			{
				key2timecount=0;
				return KEY2_PRES;
			}
			key2timecount=0;
		}
	}
	if(key2_up==0)//如果按键按下则按10ms时间计时
	{
		delay_ms(10);
		key2timecount++;
		if(key2timecount==30)//如果长按时间大于1s则返回按键长按
		{
			return KEY2_LONG_PRES;
		}	
	}
	if(key3_up&&(KEY3==0))//若按键按下且引脚被拉低
	{
		delay_ms(10);//去抖动 
		if(KEY3==0) key3_up=0;
	}
	else if(KEY3==1)//按键引脚仍为高电平（未按下）
	{
		if(key3_up==0)
		{
			key3_up=1; 			
			if(key3timecount<30)
			{
				key3timecount=0;
				return KEY3_PRES;
			}
			key3timecount=0;
		}
	}
	if(key3_up==0)//如果按键按下则按10ms时间计时
	{
		delay_ms(10);
		key3timecount++;
		if(key3timecount==30)//如果长按时间大于1s则返回按键长按
		{
			return KEY3_LONG_PRES;
		}	
	}
	if(key4_up&&(KEY4==0))//若按键按下且引脚被拉低
	{
		delay_ms(10);//去抖动 
		if(KEY4==0) key4_up=0;
	}
	else if(KEY4==1)//按键引脚仍为高电平（未按下）
	{
		if(key4_up==0)
		{
			key4_up=1; 			
			if(key4timecount<30)
			{
				key4timecount=0;
				return KEY4_PRES;
			}
			key4timecount=0;
		}
	}
	if(key4_up==0)//如果按键按下则按10ms时间计时
	{
		delay_ms(10);
		key4timecount++;
		if(key4timecount==30)//如果长按时间大于1s则返回按键长按
		{
			return KEY4_LONG_PRES;
		}	
	}
	return 0;// 无按键按下
}

void KeyCmd(void)
{
	int key=0;
	key=KEY_Scan();
	if(key==KEY1_PRES)
	{
		OpenmvModePick1;
	}
	else if(key==KEY2_PRES)
	{
		mode = 2; Flag2=1;
	}
	else if(key==KEY3_PRES)
	{
		mode = 4;Flag4=1;
		OpenmvModePick2;
	}
	else if(key==KEY4_PRES)
	{
		mode=5;OpenmvModePick3;
	}
	else if(key==KEY1_LONG_PRES)
	{
		mode=6;RedCx=LocX1,RedCy=LocY1;
	}		
	else if(key==KEY2_LONG_PRES)
	{
		mode=6;RedCx=LocX2,RedCy=LocY2;
	}
	else if(key==KEY3_LONG_PRES)
	{
		mode=6;RedCx=LocX3,RedCy=LocY3;
	}
	else if(key==KEY4_LONG_PRES)
	{
		mode=6;RedCx=LocX4,RedCy=LocY4;
	}
}
