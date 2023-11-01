#include "user_task.h"

#include "bsp_usart.h"

void user_task(void *pvParameters)
{
	
	while(1)
	{
		printf("hello\r\n");
		vTaskDelay(500);
	}
}
