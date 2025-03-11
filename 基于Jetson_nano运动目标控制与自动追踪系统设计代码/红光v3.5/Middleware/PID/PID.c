#include "PID.h"

_pid pid_speed_left, pid_speed_right;    
// 结构体对象 location
_pid pid_location_x,pid_location_y,pid_location_x2,pid_location_y2;
_pid pid_location;

/**
  * @brief  PID参数初始化
	*	@note 	无
  * @retval 无
  */
void PID_param_init()
{
	/* 位置相关初始化参数 */
    pid_location_x.target_val=5.0;				
    pid_location_x.actual_val=0.0;
    pid_location_x.err=0.0;
    pid_location_x.err_last=0.0;
    pid_location_x.integral=0.0;
		pid_location_x.Kp = 1.24;
		pid_location_x.Ki = 1.0;
		pid_location_x.Kd = 1.0;
	
		pid_location_y.target_val=5.0;				
    pid_location_y.actual_val=0.0;
    pid_location_y.err=0.0;
    pid_location_y.err_last=0.0;
    pid_location_y.integral=0.0;
		pid_location_y.Kp = 1.0;
		pid_location_y.Ki = 0.0;
		pid_location_y.Kd = 0.0;
	
		pid_location_x2.target_val=0.0;				
    pid_location_x2.actual_val=0.0;
    pid_location_x2.err=0.0;
    pid_location_x2.err_last=0.0;
    pid_location_x2.integral=0.0;
		pid_location_x2.Kp = 0.0;
		pid_location_x2.Ki = 0.0;
		pid_location_x2.Kd = 0.0;
	
		pid_location_y2.target_val=5.0;				
    pid_location_y2.actual_val=0.0;
    pid_location_y2.err=0.0;
    pid_location_y2.err_last=0.0;
    pid_location_y2.integral=0.0;
		pid_location_y2.Kp = 1.0;
		pid_location_y2.Ki = 0.0;
		pid_location_y2.Kd = 0.0;
	
}

/**
  * @brief  设置目标值
  * @param  val		目标值
	*	@note 	无
  * @retval 无
  */
void set_pid_target(_pid *pid, float temp_val)
{
  pid->target_val = temp_val;    // 设置当前的目标值
}

/**
  * @brief  获取目标值
  * @param  无
	*	@note 	无
  * @retval 目标值
  */
float get_pid_target(_pid *pid)
{
  return pid->target_val;    // 设置当前的目标值
}

void set_p_i_d(_pid *pid, float p, float i, float d)
{
  	pid->Kp = p;    // 设置比例系数 P
		pid->Ki = i;    // 设置积分系数 I
		pid->Kd = d;    // 设置微分系数 D
}

/**
  * @brief  位置PID算法实现
  * @param  actual_val:实际值
	*	@note 	无
  * @retval 通过PID计算后的输出
  */
float location_pid_realize(_pid *pid, float actual_val)  //位置环光个Kp好像也可以
{
		/*传入实际值*/
		pid->actual_val = actual_val;

		/*计算目标值与实际值的误差*/
    pid->err=pid->target_val-pid->actual_val;
  
    pid->integral += pid->err;    // 误差累积

		/*PID算法实现*/
    pid->actual_val = pid->Kp*pid->err
		                  +pid->Ki*pid->integral
		                  +pid->Kd*(pid->err-pid->err_last);
  
		/*误差传递*/
    pid->err_last=pid->err;
    
		/*返回当前实际值*/
    return pid->actual_val;
}

/**
  * @brief  速度PID算法实现
  * @param  actual_val:实际值
	*	@note 	无
  * @retval 通过PID计算后的输出
  */
float speed_pid_realize(_pid *pid, float actual_val)
{
		/*计算目标值与实际值的误差*/
    pid->err=pid->target_val-actual_val;

    if((pid->err<2 ) && (pid->err>-2))  //差1这么多可以吗？运行1分钟，位置差为1个轮子的周长 
		{
      pid->err = 0.0f;
			pid->integral = 0;
		}
	
    pid->integral += pid->err;    // 误差累积

	  /*积分限幅*/
	   	 if (pid->integral >= 500) {pid->integral =500;}
      else if (pid->integral < -500)  {pid->integral = -200;}

		/*PID算法实现*/
    pid->actual_val = pid->Kp*pid->err
		                  +pid->Ki*pid->integral
		                   +pid->Kd*(pid->err-pid->err_last);
  
		/*误差传递*/
    pid->err_last=pid->err;
    
		/*返回当前实际值*/
    return pid->actual_val;
}


