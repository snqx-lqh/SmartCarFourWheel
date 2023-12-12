#ifndef _BSP_MOTOR_H
#define _BSP_MOTOR_H

/*
ENCODER:   TIM4     TIM2
           TIM5     TIM3
		   
PWM:       TIM8_3    TIM8_2
           TIM1_4    TIM8_1

*/
#include "main.h"

#define MAX_PWM_SET 7200

#define MOTORA_IN1         PBout(9)
#define MOTORA_IN2         PBout(8)
#define MOTORA_TIM         TIM8
#define MOTORA_PWM_SET     TIM_SetCompare3

#define MOTORB_IN1         PBout(15)
#define MOTORB_IN2         PAout(8)
#define MOTORB_TIM         TIM8
#define MOTORB_PWM_SET     TIM_SetCompare2

#define MOTORC_IN1         PBout(13)
#define MOTORC_IN2         PBout(14)
#define MOTORC_TIM         TIM8
#define MOTORC_PWM_SET     TIM_SetCompare1

#define MOTORD_IN1         PAout(11)
#define MOTORD_IN2         PAout(12)
#define MOTORD_TIM         TIM8
#define MOTORD_PWM_SET     TIM_SetCompare4

#define MOTORA_ENC    4
#define MOTORB_ENC    2
#define MOTORC_ENC    3
#define MOTORD_ENC    5

int  read_encoder(u8 TIMX);
void bsp_motor_dir_init(void);
void bsp_motor_pwm_init(u16 arr,u16 psc);
void bsp_encoder_init(void);
void bsp_motor_init(void);
void motor_pwm_set(int16_t motorAPwm,int16_t motorBPwm,int16_t motorCPwm,int16_t motorDPwm);



#endif
