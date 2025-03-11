#ifndef __USART2_H
#define	__USART2_H


#include "commonhead.h"

//串口接收DMA缓存

#define UART2_REC_NUM  	200  	//定义最大接收字节数 200
extern uint8_t Uart2_Rx[UART2_REC_NUM];
void USART2_Config(void);
void NVIC_Configurationusart2(void);

void PrintChar(char *s);	//输出字符串
void UART2_Send_Char(char *s);//发送字符
void USART2_Send_Byte(unsigned char byte);   //串口发送一个字节
void USART2_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
#endif /* __USART2_H */
