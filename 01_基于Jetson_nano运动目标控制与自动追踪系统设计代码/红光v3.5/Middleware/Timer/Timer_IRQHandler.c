#include "Timer_IRQHandler.h"

void TIM1_UP_IRQHandler(void)//中断最小时间单位：10ms
{	
	time1count++;
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //检查TIM1更新中断发生与否
	{
			if(mode >= 4 && mode < 6)
			{
				Xianfu_Pwm(); 
				set_pid_target(&pid_location_x2,TargetCxHope);
				set_pid_target(&pid_location_y2,TargetCyHope);
				result_x=location_pid_realize(&pid_location_x2, OpenmvRedCx);
				result_y=location_pid_realize(&pid_location_y2, OpenmvRedCy);
				Xianfu_Velocity(result_x,result_y);	
				Set_Pwm(-result_x,-result_y);    //赋值给PWM寄存器
			}
			else if(mode < 4 || mode == 6)
			{
				Xianfu_Pwm();   
				Target1=750-RedCx;
				Target2=RedCy+750;
				Velocity1=Position_PID_1(Position1,Target1); //舵机PID控制，可以根据目标位置进行速度调整，离目标位置越远速度越快
				Velocity2=Position_PID_2(Position2,Target2); //舵机PID控制，可以根据目标位置进行速度调整，离目标位置越远速度越快
				Xianfu_Velocity(Velocity1,Velocity2);	
				Set_Pwm(Velocity1,Velocity2);    //赋值给PWM寄存器
			}
			TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //清除TIM1更新中断标志
	}
}
/*@brief: 定时器2中断更新函数
 * @param:None
 * @return: None
 */
void TIM2_IRQHandler()
{
  if(TIM_GetITStatus(TIM2, TIM_IT_Update)==1) //当发生中断时状态寄存器(TIMx_SR)的bit0会被硬件置1
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //状态寄存器(TIMx_SR)的bit0置0
	}
}

/*@brief: 定时器3中断更新函数
 * @param:None
 * @return: None
 */
void TIM3_IRQHandler(void)
{ 		    		  			    
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx更新中断标志
	}
}

/*@brief: 定时器4中断更新函数，1ms进入一次中断
 * @param:None
 * @return: None
 */
void TIM4_IRQHandler(void)   //TIM4中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM4更新中断发生与否
	{	
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIMx更新中断标志
	}
}

