#ifndef __USART3_H
#define	__USART3_H

#include "commonhead.h"



//���ڽ���DMA����
#define UART3_REC_NUM  	200  	//�����������ֽ��� 200
extern uint8_t Uart3_Rx[UART3_REC_NUM];
void USART3_Config(void);
void NVIC_Configurationusart3(void);
void Print3Char(char *s);
void UART3_Send_Char(char *s);
void USART3_Send_Byte(unsigned char byte);
void USART3_printf11(USART_TypeDef* USARTx, uint8_t *Data,...);

#endif 
