#include "key.h"

//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTAʱ��
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//KEY2
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//KEY3
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //ʹ��GPIOAʱ�ӣ�GPIOA������APB2ʱ���£���STM32��ʹ��IO��ǰ��Ҫʹ�ܶ�Ӧʱ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//KEY4
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC
}

//�˺���Ϊ����ɨ�躯��
// return: �������µĽ���������̰�ʱ����KEYx_PRES,���³���ʱ�����1S�����ƣ�ʱ����KEYx_LONG_PRES
u8 KEY_Scan(void)
{	 
	static u8 key1_up=1,key2_up=1,key3_up=1,key4_up=1;//�������ɿ���־������ʱΪ1���ɿ�ʱΪ0
	static u16 key1timecount=0,key2timecount=0,key3timecount=0,key4timecount=0;	  
	if(key1_up&&(KEY1==0))//���������������ű�����
	{
		delay_ms(10);//ȥ���� 
		if(KEY1==0) key1_up=0;
	}
	else if(KEY1==1)//����������Ϊ�ߵ�ƽ��δ���£�
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
	if(key1_up==0)//�������������10msʱ���ʱ
	{
		delay_ms(10);
		key1timecount++;
		if(key1timecount==30)//�������ʱ�����1s�򷵻ذ�������
		{
			return KEY1_LONG_PRES;
		}	
	}
	if(key2_up&&(KEY2==0))//���������������ű�����
	{
		delay_ms(10);//ȥ���� 
		if(KEY2==0) key2_up=0;
	}
	else if(KEY2==1)//����������Ϊ�ߵ�ƽ��δ���£�
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
	if(key2_up==0)//�������������10msʱ���ʱ
	{
		delay_ms(10);
		key2timecount++;
		if(key2timecount==30)//�������ʱ�����1s�򷵻ذ�������
		{
			return KEY2_LONG_PRES;
		}	
	}
	if(key3_up&&(KEY3==0))//���������������ű�����
	{
		delay_ms(10);//ȥ���� 
		if(KEY3==0) key3_up=0;
	}
	else if(KEY3==1)//����������Ϊ�ߵ�ƽ��δ���£�
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
	if(key3_up==0)//�������������10msʱ���ʱ
	{
		delay_ms(10);
		key3timecount++;
		if(key3timecount==30)//�������ʱ�����1s�򷵻ذ�������
		{
			return KEY3_LONG_PRES;
		}	
	}
	if(key4_up&&(KEY4==0))//���������������ű�����
	{
		delay_ms(10);//ȥ���� 
		if(KEY4==0) key4_up=0;
	}
	else if(KEY4==1)//����������Ϊ�ߵ�ƽ��δ���£�
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
	if(key4_up==0)//�������������10msʱ���ʱ
	{
		delay_ms(10);
		key4timecount++;
		if(key4timecount==30)//�������ʱ�����1s�򷵻ذ�������
		{
			return KEY4_LONG_PRES;
		}	
	}
	return 0;// �ް�������
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
