#include "usart.h"

//����1�жϷ������
u8 uart_byte_count1=0;
int n1 = 0,n2 = 0;
void USART1_IRQHandler(void)
{  
u8 rec_data;
	char* Receive;	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж� 
		{
				rec_data =(u8)USART_ReceiveData(USART1);         //(USART1->DR) ��ȡ���յ�������			
			if(rec_data=='#')		  	                         //�����S����ʾ��������Ϣ����ʼλ
			{
				uart_byte_count1=0x01; 
			}
			else if(rec_data=='@')		                         //���E����ʾ��������Ϣ���͵Ľ���λ
			{
				//���¿�д��֡�����ݵ�ת�����жϺʹ���
				if(strcmp("1",(char *)Uart_Rx)==0){	mode=1;	}  //Target1ΪY��Target2Ϊx
				else if(strcmp("2",(char *)Uart_Rx)==0){mode=2; Flag2=1;}
				else if(strcmp("Flag_youxia++",(char *)Uart_Rx)==0){Flag_youxia++;}
				else if(strcmp("Flag2--",(char *)Uart_Rx)==0){Flag2--;}
				else if(strcmp("3",(char *)Uart_Rx)==0){mode=4;Flag4=1;OpenmvModePick1;delay_ms(1500);OpenmvModePick2;}		
				else if(strcmp("Flag3++",(char *)Uart_Rx)==0){Flag3++;}
				else if(strcmp("Flag3--",(char *)Uart_Rx)==0){Flag3--;}
				else if(strcmp("4",(char *)Uart_Rx)==0){mode=5;OpenmvModePick3;}
				else if(strcmp("Flag4++",(char *)Uart_Rx)==0){Flag4+=1;}
				else if(strcmp("Flag4--",(char *)Uart_Rx)==0){Flag4--;}
				else if(strcmp("5",(char *)Uart_Rx)==0){mode=5;Flag5=1;OpenmvModePick2;}
				else if(strcmp("Flag5++",(char *)Uart_Rx)==0){Flag5++;}
				else if(strcmp("Flag5--",(char *)Uart_Rx)==0){Flag5--;}
				else if(strcmp("6",(char *)Uart_Rx)==0){mode=6;Flag6=1;}
				else if(strcmp("7",(char *)Uart_Rx)==0){mode=7;Flag6=1;}
				else if(strcmp("Flag6++",(char *)Uart_Rx)==0){Flag6++;}
				else if(strcmp("Flag6--",(char *)Uart_Rx)==0){Flag6--;}
				
				else if(strcmp("Y+1",(char *)Uart_Rx)==0){mode=6,RedCy=RedCy+1;}  //Target1ΪY��Target2Ϊx
				else if(strcmp("Y-1",(char *)Uart_Rx)==0){mode=6,RedCy=RedCy-1;}
				else if(strcmp("X+1",(char *)Uart_Rx)==0){mode=6,RedCx=RedCx+1;}
				else if(strcmp("X-1",(char *)Uart_Rx)==0){mode=6,RedCx=RedCx-1;}
				else if(strcmp("ZS",(char *)Uart_Rx)==0){mode=6;RedCx=LocX1,RedCy=LocY1;}
				else if(strcmp("YS",(char *)Uart_Rx)==0){mode=6;RedCx=LocX2,RedCy=LocY2;}
				else if(strcmp("YX",(char *)Uart_Rx)==0){mode=6;RedCx=LocX3,RedCy=LocY3;}
				else if(strcmp("ZX",(char *)Uart_Rx)==0){mode=6;RedCx=LocX4,RedCy=LocY4;}
				else if(strcmp("ZS2",(char *)Uart_Rx)==0){mode=6;RedCx=PX1,RedCy=PY1;}
				else if(strcmp("YS2",(char *)Uart_Rx)==0){mode=6;RedCx=PX2,RedCy=PY2;}
				else if(strcmp("YX2",(char *)Uart_Rx)==0){mode=6;RedCx=PX3,RedCy=PY3;}
				else if(strcmp("ZX2",(char *)Uart_Rx)==0){mode=6;RedCx=PX4,RedCy=PY4;}
				else if(strcmp("RES",(char *)Uart_Rx)==0){mode=6;RedCy=ZeroX,RedCx=ZeroY;}
				//����Ϊ֡���������ͷ��������
				for(uart_byte_count1=0;uart_byte_count1<32;uart_byte_count1++)
					{
						Uart_Rx[uart_byte_count1]=0x00;
					}
					uart_byte_count1=0;
			}	
			else if(rec_data=='&')				
						{
							Receive=(char*)Uart_Rx;
							sscanf(Receive,"%d,%d",&n1,&n2);
							Target1=n2;
							Target2=n1;							
							printf("Target1=%f,Target1=%f\r\n",Target1,Target2);							
							//����Ϊ֡���������ͷ��������
							for(uart_byte_count1=0;uart_byte_count1<32;uart_byte_count1++)
							{
								Uart_Rx[uart_byte_count1]=0x00;
							}
								uart_byte_count1=0;
						}				
			else if((uart_byte_count1>0)&&(uart_byte_count1<=UART1_REC_NUM))
			{
				   Uart_Rx[uart_byte_count1-1]=rec_data;
				   uart_byte_count1++;
			}
		}
}

//����2�����жϷ�����
u8 uart2_byte_count=0;        //���յ������ݳ���
int x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6,x7,y7,x8,y8,x9,y9,x10,y10,x11,y11,x12,y12;
void USART2_IRQHandler(void)
{
	u8 rec_data;	   
	char* Receive;	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//���յ�����
	{	 	
				rec_data =(u8)USART_ReceiveData(USART2);         //(USART2->DR) ��ȡ���յ�������
        if(rec_data=='#')		  	                         //�����S����ʾ��������Ϣ����ʼλ
				{
					uart2_byte_count=0x01; 
				}
				else if(rec_data=='$')		                         //���E����ʾ��������Ϣ���͵Ľ���λ
				{
//				printf("\r\n�����͵���ϢΪ:\r\n\r\n");
//				printf("BUF:%s\r\n\r\n",Uart2_Rx);
					sscanf((char *)Uart2_Rx,"%d,%d,%d,%d,%d,%d,%d,%d,",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
					Pos[0][0]=x1;
					Pos[0][1]=y1;		
					Pos[1][0]=x2;
					Pos[1][1]=y2;
					Pos[2][0]=x3;
					Pos[2][1]=y3;
					Pos[3][0]=x4;
					Pos[3][1]=y4;
					for(uart2_byte_count=0;uart2_byte_count<32;uart2_byte_count++) Uart2_Rx[uart2_byte_count]=0x00;
					uart2_byte_count=0;    
				}
			else if(rec_data==')')				
			{
				sscanf((char *)Uart2_Rx,"%d,%d,",&OpenmvRedCx,&OpenmvRedCy);
//				Receive=(char*)Uart2_Rx;
//				printf("\r\n�����͵���ϢΪ2:\r\n\r\n");
//				printf("x=BUF:%s\r\n\r\n",Receive);
//				cursor_y = atoi((char*)Receive);
//			printf("num��ֵΪ:%d\r\n",distant);
				//����Ϊ֡���������ͷ��������
				for(uart2_byte_count=0;uart2_byte_count<32;uart2_byte_count++)
				{
					Uart2_Rx[uart2_byte_count]=0x00;
				}
					uart2_byte_count=0;
			}		
			else if(rec_data=='G')				
			{
				sscanf((char *)Uart2_Rx,"%d,%d,",&OpenmvGreenCx,&OpenmvGreenCy);
				//����Ϊ֡���������ͷ��������
				for(uart2_byte_count=0;uart2_byte_count<32;uart2_byte_count++)
				{
					Uart2_Rx[uart2_byte_count]=0x00;
				}
					uart2_byte_count=0;
			}
			else if((uart2_byte_count>0)&&(uart2_byte_count<=128))
				{
				   Uart2_Rx[uart2_byte_count-1]=rec_data;
				   uart2_byte_count++;
				}
	}  											 
}

int n3 = 0;
//����3�жϷ������
u8 uart_byte_count=0;//����������±�ָ��
void USART3_IRQHandler(void)
{  
	u8 rec_data;
	char* Receive;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж� 
	{
		rec_data =(u8)USART_ReceiveData(USART3);         //(USART1->DR) ��ȡ���յ�������		
		if(rec_data=='#')		  	                         //�����S����ʾ��������Ϣ����ʼλ
		{
			uart_byte_count=0x01; 
		}
		else if(rec_data=='@')		                         //���E����ʾ��������Ϣ���͵Ľ���λ
		{	
			printf("\r\n�����͵���ϢΪ1:\r\n\r\n");
			printf("BUF:%s\r\n\r\n",Uart3_Rx);
//======���¿�д��֡�����ݵ�ת�����жϺʹ���=========

//======����Ϊ֡���������ͷ��������================
//			printf("num��ֵΪ:%d\r\n",distant);
			for(uart_byte_count=0;uart_byte_count<32;uart_byte_count++)
			{
				Uart3_Rx[uart_byte_count]=0x00;
			}
			uart_byte_count=0;
		}
		else if(rec_data=='S')		    //���$����ʾ��ʶ��ʮ��·�ڵ�������Ϣ���͵Ľ���λ
		{	  
			Receive=(char*)Uart3_Rx;
			printf("%c\r\n",&Receive);	
			for(uart_byte_count=0;uart_byte_count<32;uart_byte_count++)
			{
				Uart3_Rx[uart_byte_count]=0x00;
			}
			uart_byte_count=0;
		}		
		else if((uart_byte_count>0)&&(uart_byte_count<=UART3_REC_NUM))//�洢����
		{
				 Uart3_Rx[uart_byte_count-1]=rec_data;
				 uart_byte_count++;
		}   
	}
}		

char *itoa(int value, char *string, int radix)
{
	int     i, d;
	int     flag = 0;
	char    *ptr = string;
	
	/* This implementation only works for decimal numbers. */
	if (radix != 10)
	{
	    *ptr = 0;
	    return string;
	}
	
	if (!value)
	{
	    *ptr++ = 0x30;
	    *ptr = 0;
	    return string;
	}
	
	/* if this is a negative value insert the minus sign. */
	if (value < 0)
	{
	    *ptr++ = '-';
	
	    /* Make the value positive. */
	    value *= -1;
	}
	
	for (i = 10000; i > 0; i /= 10)
	{
	    d = value / i;
	
	    if (d || flag)
	    {
	        *ptr++ = (char)(d + 0x30);
	        value -= (d * i);
	        flag = 1;
	    }
	}
	
	/* Null terminate the string. */
	*ptr = 0;
	
	return string;

} /* NCL_Itoa */

