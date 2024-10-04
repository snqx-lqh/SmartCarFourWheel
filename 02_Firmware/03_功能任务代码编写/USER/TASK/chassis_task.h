#ifndef _CHASSIS_TASK_H
#define _CHASSIS_TASK_H

#include "main.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#include "pid.h"

typedef enum{
	CHASSIS_NORMAL = 0,
	CHASSIS_STOP   = 1,
	CHASSIS_RUN    = 2,	
	CHASSIS_TEST   = 3,	
}chassis_mode_t;

typedef struct{
	int16_t     		  speed;
    int16_t     		  speed_set;
    int16_t               give_current;
}chassis_motor_t;

typedef struct{ 
	PidTypeDef      speed_pid[4];
	int16_t         move_vx;
	int16_t         move_vy;
	int16_t         move_vz;
	chassis_motor_t chassis_motor[4];
	chassis_mode_t  chassis_mode;
}chassis_move_t;

void chassis_init(chassis_move_t *chassis_move);
void chassis_date_get(chassis_move_t *chassis_move);
void chassis_date_update(chassis_move_t *chassis_move);
void chassis_set_control(chassis_move_t *chassis_move);
void chassis_pid_calc(chassis_move_t *chassis_move);
void chassis_power_ctr(chassis_move_t *chassis_move);
void chassis_current_give(chassis_move_t *chassis_move);


void chassis_task(void *pvParameters);



#endif
