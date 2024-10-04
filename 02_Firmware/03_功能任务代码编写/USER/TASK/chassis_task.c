#include "chassis_task.h"

#include "bsp_motor.h"
#include "bluetooth_debugger.h"
#include "bsp_key.h"

chassis_move_t chassis;

void chassis_task(void *pvParameters)
{
	chassis_init(&chassis);
	while(1)
	{
		chassis_date_get(&chassis);
		chassis_date_update(&chassis);
		chassis_set_control(&chassis);
		chassis_pid_calc(&chassis);
		
		chassis_current_give(&chassis);

		vTaskDelay(5);
	}
	
}

void chassis_init(chassis_move_t *chassis)
{
	fp32 pid_value0[3] ={400,2,0};
	fp32 pid_value1[3] ={400,2,0};
	fp32 pid_value2[3] ={400,2,0};
	fp32 pid_value3[3] ={400,2,0};
	
	PID_Init(&chassis->speed_pid[0],PID_POSITION,pid_value0,7000,400);//电机i的pid参数、位置式、Kp,Ki,Kd、最大PID输出、最大I积分输出
	PID_Init(&chassis->speed_pid[1],PID_POSITION,pid_value1,7000,400);
	PID_Init(&chassis->speed_pid[2],PID_POSITION,pid_value2,7000,400);
	PID_Init(&chassis->speed_pid[3],PID_POSITION,pid_value3,7000,400);
	
	chassis->chassis_mode = CHASSIS_NORMAL;
}

void chassis_date_get(chassis_move_t *chassis)
{
	int16_t i;	
	
	for(i=0;i<4;i++)
	{
		
	}	
}

void chassis_date_update(chassis_move_t *chassis)
{
	int16_t i;

	chassis->chassis_motor[0].speed = read_encoder(MOTORA_ENC);//获取电机数据
	chassis->chassis_motor[1].speed = (-read_encoder(MOTORB_ENC));//获取电机数据
	chassis->chassis_motor[2].speed = (-read_encoder(MOTORC_ENC));//获取电机数据
	chassis->chassis_motor[3].speed = read_encoder(MOTORD_ENC);//获取电机数据

	if(SW_1 == 0 && SW_2 == 0 && SW_3 == 0)
	{
		chassis->chassis_mode = CHASSIS_RUN;
	}else if(SW_1 == 1 && SW_2 == 0 && SW_3 == 0)
	{
		chassis->chassis_mode = CHASSIS_NORMAL;
	}else if(SW_1 == 0 && SW_2 == 1 && SW_3 == 0)
	{
		chassis->chassis_mode = CHASSIS_TEST;
	}
	
	if(chassis->chassis_mode==CHASSIS_RUN)  
	{
	    chassis->move_vx = rx_pack_ptr.shorts[1];
		chassis->move_vy = rx_pack_ptr.shorts[0];
		chassis->move_vz = 0;
	}else if(chassis->chassis_mode==CHASSIS_NORMAL)  
	{
	    chassis->move_vx = 0;
		chassis->move_vy = 20;
		chassis->move_vz = 0;
	}else if(chassis->chassis_mode==CHASSIS_TEST)  
	{
	    chassis->move_vx = 20;
		chassis->move_vy = 0;
		chassis->move_vz = 0;
	}
}

void chassis_set_control(chassis_move_t *chassis)
{
	if(chassis->chassis_mode == CHASSIS_NORMAL)
	{
		#if 0
		chassis->chassis_motor[0].speed_set =  -chassis->move_vy +chassis->move_vx -chassis->move_vz;
		chassis->chassis_motor[1].speed_set =  -chassis->move_vy -chassis->move_vx -chassis->move_vz;
		chassis->chassis_motor[2].speed_set =  chassis->move_vy  -chassis->move_vx -chassis->move_vz;
		chassis->chassis_motor[3].speed_set =  chassis->move_vy  +chassis->move_vx -chassis->move_vz;
		#endif
		
		#if 0
		chassis->chassis_motor[0].speed_set =  chassis->move_vx;
		chassis->chassis_motor[1].speed_set =  chassis->move_vx;
		chassis->chassis_motor[2].speed_set =  chassis->move_vx;
		chassis->chassis_motor[3].speed_set =  chassis->move_vx;
		#endif
		
		#if 1
		chassis->chassis_motor[0].speed_set =  chassis->move_vx + chassis->move_vy;
		chassis->chassis_motor[1].speed_set =  chassis->move_vx - chassis->move_vy;
		chassis->chassis_motor[2].speed_set =  chassis->move_vx - chassis->move_vy;
		chassis->chassis_motor[3].speed_set =  chassis->move_vx + chassis->move_vy;
		#endif
		
		#if 0
		chassis->chassis_motor[0].speed_set =  chassis->move_vx;
		chassis->chassis_motor[1].speed_set =  -chassis->move_vx;
		chassis->chassis_motor[2].speed_set =  -chassis->move_vx;
		chassis->chassis_motor[3].speed_set =  chassis->move_vx;
		#endif
	}	
}

void chassis_pid_calc(chassis_move_t *chassis)
{
	int16_t i;
	for(i=0;i<4;i++)                   //依次计算四个电机的pid电流值
	{
		chassis->chassis_motor[i].give_current = PID_Calc(&chassis->speed_pid[i], 
			     chassis->chassis_motor[i].speed,chassis->chassis_motor[i].speed_set);
	}
}


void chassis_current_give(chassis_move_t *chassis)
{
	motor_pwm_set  (chassis->chassis_motor[0].give_current,chassis->chassis_motor[1].give_current, 
	                chassis->chassis_motor[2].give_current,chassis->chassis_motor[3].give_current);
}
