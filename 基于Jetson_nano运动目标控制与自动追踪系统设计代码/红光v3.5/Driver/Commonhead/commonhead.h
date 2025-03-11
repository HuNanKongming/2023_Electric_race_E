#ifndef _COMMONHEAD_H_
#define _COMMONHEAD_H_

#include "stm32f10x.h"
#include "stdio.h"
#include "stdlib.h"
#include <stdarg.h>
#include "misc.h"

#include "delay.h"
#include "sys.h"
#include "init.h"

#include "ExternPara.h"
#include "LED.h"
#include "Beep.h"
#include "OLED.h"
#include "key.h"
#include "nvic.h"

#include "usart1.h"
#include "usart2.h"
#include "usart3.h"

#include "encoder.h"
#include "Angle.h"
#include "control.h"
#include "left_control.h"
#include "right_control.h"
#include "timer.h"
#include "PID.h"
#include <math.h>

#include "i2c.h"
#include "mpu6050.h"
#include "i2c_mpu6050.h"
#include "SEGGER_RTT.h"

#define   OpenmvModePick0  {(USART_SendData(USART2,'0'));}
#define   OpenmvModePick1  {(USART_SendData(USART2,'1'));}
#define   OpenmvModePick2  {(USART_SendData(USART2,'2'));}
#define   OpenmvModePick3  {(USART_SendData(USART2,'3'));}
#define PI 3.14159265

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //输出 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //输入

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //输出 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //输入

#endif

