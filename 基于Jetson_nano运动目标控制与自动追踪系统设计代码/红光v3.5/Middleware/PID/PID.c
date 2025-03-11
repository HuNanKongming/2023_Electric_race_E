#include "PID.h"

_pid pid_speed_left, pid_speed_right;    
// �ṹ����� location
_pid pid_location_x,pid_location_y,pid_location_x2,pid_location_y2;
_pid pid_location;

/**
  * @brief  PID������ʼ��
	*	@note 	��
  * @retval ��
  */
void PID_param_init()
{
	/* λ����س�ʼ������ */
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
  * @brief  ����Ŀ��ֵ
  * @param  val		Ŀ��ֵ
	*	@note 	��
  * @retval ��
  */
void set_pid_target(_pid *pid, float temp_val)
{
  pid->target_val = temp_val;    // ���õ�ǰ��Ŀ��ֵ
}

/**
  * @brief  ��ȡĿ��ֵ
  * @param  ��
	*	@note 	��
  * @retval Ŀ��ֵ
  */
float get_pid_target(_pid *pid)
{
  return pid->target_val;    // ���õ�ǰ��Ŀ��ֵ
}

void set_p_i_d(_pid *pid, float p, float i, float d)
{
  	pid->Kp = p;    // ���ñ���ϵ�� P
		pid->Ki = i;    // ���û���ϵ�� I
		pid->Kd = d;    // ����΢��ϵ�� D
}

/**
  * @brief  λ��PID�㷨ʵ��
  * @param  actual_val:ʵ��ֵ
	*	@note 	��
  * @retval ͨ��PID���������
  */
float location_pid_realize(_pid *pid, float actual_val)  //λ�û����Kp����Ҳ����
{
		/*����ʵ��ֵ*/
		pid->actual_val = actual_val;

		/*����Ŀ��ֵ��ʵ��ֵ�����*/
    pid->err=pid->target_val-pid->actual_val;
  
    pid->integral += pid->err;    // ����ۻ�

		/*PID�㷨ʵ��*/
    pid->actual_val = pid->Kp*pid->err
		                  +pid->Ki*pid->integral
		                  +pid->Kd*(pid->err-pid->err_last);
  
		/*����*/
    pid->err_last=pid->err;
    
		/*���ص�ǰʵ��ֵ*/
    return pid->actual_val;
}

/**
  * @brief  �ٶ�PID�㷨ʵ��
  * @param  actual_val:ʵ��ֵ
	*	@note 	��
  * @retval ͨ��PID���������
  */
float speed_pid_realize(_pid *pid, float actual_val)
{
		/*����Ŀ��ֵ��ʵ��ֵ�����*/
    pid->err=pid->target_val-actual_val;

    if((pid->err<2 ) && (pid->err>-2))  //��1��ô�����������1���ӣ�λ�ò�Ϊ1�����ӵ��ܳ� 
		{
      pid->err = 0.0f;
			pid->integral = 0;
		}
	
    pid->integral += pid->err;    // ����ۻ�

	  /*�����޷�*/
	   	 if (pid->integral >= 500) {pid->integral =500;}
      else if (pid->integral < -500)  {pid->integral = -200;}

		/*PID�㷨ʵ��*/
    pid->actual_val = pid->Kp*pid->err
		                  +pid->Ki*pid->integral
		                   +pid->Kd*(pid->err-pid->err_last);
  
		/*����*/
    pid->err_last=pid->err;
    
		/*���ص�ǰʵ��ֵ*/
    return pid->actual_val;
}


