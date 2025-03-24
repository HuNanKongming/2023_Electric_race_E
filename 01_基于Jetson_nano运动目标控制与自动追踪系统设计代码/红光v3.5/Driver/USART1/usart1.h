#ifndef __USART1_H
#define	__USART1_H
#include "commonhead.h"
#include <stdarg.h>
#include "stdio.h"
#include "misc.h"
//串口接收DMA缓存
#define UART_RX_LEN		128
#define UART1_REC_NUM  	200  	//定义最大接收字节数 200
extern uint8_t Uart_Rx[UART_RX_LEN];
void USART1_Config(void);
void NVIC_Configurationusart1(void);
//int  fputc(int ch, FILE *f);
void USART1_Send_Byte(unsigned char byte);

void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
void Print1Char(char *s);
void UART1_Send_Char(char *s);


#endif /* __USART1_H */
