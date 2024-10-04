#include "user_task.h"

#include "bsp_usart.h"
#include "bsp_motor.h"

int16_t motorAEncode=0,motorBEncode=0,motorCEncode,motorDEncode=0;

void user_task(void *pvParameters)
{
	
	while(1)
	{
//		motorAEncode = read_encoder(MOTORA_ENC);
//		motorBEncode = (-read_encoder(MOTORB_ENC));
//		motorCEncode = (-read_encoder(MOTORC_ENC));
//		motorDEncode = read_encoder(MOTORD_ENC);
//		motor_pwm_set(4000,4000,4000,4000);
		//printf("HELLO WORLD\r\n");
		vTaskDelay(100);
	}
}
