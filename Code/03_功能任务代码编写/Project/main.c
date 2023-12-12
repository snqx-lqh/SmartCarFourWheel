#include "main.h"

#include "bsp_delay.h"
#include "bsp_usart.h"
#include "bsp_sys.h"

#include "bsp_led.h"
#include "bsp_exti.h"
#include "bsp_timer.h"
#include "bsp_adc.h"
#include "bsp_key.h"
#include "bsp_motor.h"

#include "mpu6050.h"
#include "oled.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#include "start_task.h"

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	bsp_usart2_init(115200);
	delay_init();
	bsp_led_init();
	bsp_timer6_init(5000,72);
	bsp_key_init();
	bsp_motor_init();
	
	MPU_Init();
	OLED_Init();
	
 	startTask();
    vTaskStartScheduler();
	
	while(1)
	{
		
	}
}



