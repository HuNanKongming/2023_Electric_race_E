#ifndef __LEFT_H //�� #endif һ��ʹ�ã������ظ�����ͷ�ļ�����߱���Ч��
#define __LEFT_H //���û�����ù�ͷ�ļ�����������¶���

#include "timer.h"
#include "commonhead.h"
void Left_dianji_Init(void); //���庯��ԭ��(��������)��һ��ͷ�ļ�(.h�ļ�)�ڶ��Ǻ���ԭ�ͣ�
                     //.c�ļ��ڶ��Ǻ�������
										 //�ú���ΪLEDӲ����ʼ������
void Left_dianji_PWM(int pwmzkb);
void Left_dianji_zhenzhuan(int pwmzkb);
void Left_dianji_fanzhuan(int pwmzkb);
#endif //������ϣ��������ù�ͷ�ļ�������һ��
