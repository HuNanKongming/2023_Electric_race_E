#include "Timer_IRQHandler.h"

void TIM1_UP_IRQHandler(void)//�ж���Сʱ�䵥λ��10ms
{	
	time1count++;
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //���TIM1�����жϷ������
	{
			if(mode >= 4 && mode < 6)
			{
				Xianfu_Pwm(); 
				set_pid_target(&pid_location_x2,TargetCxHope);
				set_pid_target(&pid_location_y2,TargetCyHope);
				result_x=location_pid_realize(&pid_location_x2, OpenmvRedCx);
				result_y=location_pid_realize(&pid_location_y2, OpenmvRedCy);
				Xianfu_Velocity(result_x,result_y);	
				Set_Pwm(-result_x,-result_y);    //��ֵ��PWM�Ĵ���
			}
			else if(mode < 4 || mode == 6)
			{
				Xianfu_Pwm();   
				Target1=750-RedCx;
				Target2=RedCy+750;
				Velocity1=Position_PID_1(Position1,Target1); //���PID���ƣ����Ը���Ŀ��λ�ý����ٶȵ�������Ŀ��λ��ԽԶ�ٶ�Խ��
				Velocity2=Position_PID_2(Position2,Target2); //���PID���ƣ����Ը���Ŀ��λ�ý����ٶȵ�������Ŀ��λ��ԽԶ�ٶ�Խ��
				Xianfu_Velocity(Velocity1,Velocity2);	
				Set_Pwm(Velocity1,Velocity2);    //��ֵ��PWM�Ĵ���
			}
			TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //���TIM1�����жϱ�־
	}
}
/*@brief: ��ʱ��2�жϸ��º���
 * @param:None
 * @return: None
 */
void TIM2_IRQHandler()
{
  if(TIM_GetITStatus(TIM2, TIM_IT_Update)==1) //�������ж�ʱ״̬�Ĵ���(TIMx_SR)��bit0�ᱻӲ����1
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //״̬�Ĵ���(TIMx_SR)��bit0��0
	}
}

/*@brief: ��ʱ��3�жϸ��º���
 * @param:None
 * @return: None
 */
void TIM3_IRQHandler(void)
{ 		    		  			    
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx�����жϱ�־
	}
}

/*@brief: ��ʱ��4�жϸ��º�����1ms����һ���ж�
 * @param:None
 * @return: None
 */
void TIM4_IRQHandler(void)   //TIM4�ж�
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //���TIM4�����жϷ������
	{	
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //���TIMx�����жϱ�־
	}
}

