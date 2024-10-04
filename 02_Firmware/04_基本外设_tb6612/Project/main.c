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

int16_t motorAEncode=0,motorBEncode=0,motorCEncode,motorDEncode=0;
int16_t key1_value = 0,key2_value = 0,key3_value = 0,key4_value = 0,key5_value = 0;
int16_t sw1_value = 0, sw2_value = 0, sw3_value = 0;

void example()
{
	//LED≤‚ ‘
//	led_board_on();
//	delay_ms(1000);
//	led_board_off();
//	delay_ms(1000);
	//∞¥º¸≤‚ ‘
//	key1_value = KEY_1;
//	key2_value = KEY_2;
//	key3_value = KEY_3;
//	key4_value = KEY_4;
//	key5_value = KEY_5;
//	sw1_value  = SW_1;
//	sw2_value  = SW_2;
//	sw3_value  = SW_3;
	//Õ”¬›“«≤‚ ‘
//	MPU_Get_Gyro(&gyrox,&gyroy,&gyroz);
//	MPU_Get_Acc(&accx,&accy,&accz);
//	delay_ms(5);
	//OLED≤‚ ‘
//	OLED_ShowString(0,0,"hello",16,1);
//	OLED_Refresh();
//	delay_ms(5);
	//µÁª˙ ‰≥ˆ≤‚ ‘
//	motor_pwm_set(-3000,-3000,-3000,-3000);
//	delay_ms(1000);
	//¥Æø⁄≤‚ ‘
	printf("HELLO\r\n");
	delay_ms(1000);
//	//µÁª˙±‡¬Î∆˜∂¡»°
	
//	motorAEncode += read_encoder(MOTORA_ENC);
//	motorBEncode += (-read_encoder(MOTORB_ENC));
//	motorCEncode += (-read_encoder(MOTORC_ENC));
//	motorDEncode += read_encoder(MOTORD_ENC);
//	delay_ms(5);
}

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	bsp_usart1_init(115200);
	delay_init();
	bsp_led_init();
	bsp_timer6_init(5000,72);
	bsp_key_init();
	bsp_motor_init();
	MPU_Init();
	OLED_Init();

	
	while(1)
	{
		example();
	}
}



