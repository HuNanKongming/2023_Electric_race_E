#ifndef __USART2_H
#define	__USART2_H


#include "commonhead.h"

//���ڽ���DMA����

#define UART2_REC_NUM  	200  	//�����������ֽ��� 200
extern uint8_t Uart2_Rx[UART2_REC_NUM];
void USART2_Config(void);
void NVIC_Configurationusart2(void);

void PrintChar(char *s);	//����ַ���
void UART2_Send_Char(char *s);//�����ַ�
void USART2_Send_Byte(unsigned char byte);   //���ڷ���һ���ֽ�
void USART2_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
#endif /* __USART2_H */
