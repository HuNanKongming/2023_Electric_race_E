#ifndef __RIGHT_H //与 #endif 一起使用，避免重复引用头文件，提高编译效率
#define __RIGHT_H //如果没有引用过头文件，则进入以下定义

#include "timer.h"
void Right_dianji_Init(void); //定义函数原型(函数声明)，一般头文件(.h文件)内都是函数原型，
                     //.c文件内都是函数定义
										 //该函数为LED硬件初始化函数
void Right_dianji_zhenzhuan(int pwmzkb);
void Right_dianji_fanzhuan(int pwmzkb);
void Right_dianji_PWM(int pwmzkb);

#endif //定义完毕，或者引用过头文件到达这一步
