#include "user_task.h"

#include "bsp_usart.h"
#include "bsp_motor.h"

void user_task(void *pvParameters)
{
	
	while(1)
	{
		motor_pwm_set(5000,5000,5000,5000);
		vTaskDelay(500);
	}
}
