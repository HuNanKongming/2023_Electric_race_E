#ifndef __RIGHT_H //�� #endif һ��ʹ�ã������ظ�����ͷ�ļ�����߱���Ч��
#define __RIGHT_H //���û�����ù�ͷ�ļ�����������¶���

#include "timer.h"
void Right_dianji_Init(void); //���庯��ԭ��(��������)��һ��ͷ�ļ�(.h�ļ�)�ڶ��Ǻ���ԭ�ͣ�
                     //.c�ļ��ڶ��Ǻ�������
										 //�ú���ΪLEDӲ����ʼ������
void Right_dianji_zhenzhuan(int pwmzkb);
void Right_dianji_fanzhuan(int pwmzkb);
void Right_dianji_PWM(int pwmzkb);

#endif //������ϣ��������ù�ͷ�ļ�������һ��
