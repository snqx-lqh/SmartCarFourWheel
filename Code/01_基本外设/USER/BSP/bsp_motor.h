#ifndef _BSP_MOTOR_H
#define _BSP_MOTOR_H

#include "main.h"

#define MAX_PWM_SET 7200

#define MOTORA_TIM         TIM1
#define MOTORA_PWMA_SET    TIM_SetCompare1
#define MOTORA_PWMB_SET    TIM_SetCompare2

#define MOTORB_TIM         TIM1
#define MOTORB_PWMA_SET    TIM_SetCompare3
#define MOTORB_PWMB_SET    TIM_SetCompare4

#define MOTORC_TIM         TIM8
#define MOTORC_PWMA_SET    TIM_SetCompare1
#define MOTORC_PWMB_SET    TIM_SetCompare2

#define MOTORD_TIM         TIM8
#define MOTORD_PWMA_SET    TIM_SetCompare3
#define MOTORD_PWMB_SET    TIM_SetCompare4


int  read_encoder(u8 TIMX);
void bsp_motor_pwm_init(u16 arr,u16 psc);
void bsp_encoder_init(void);
void bsp_motor_init(void);
void motor_pwm_set(int16_t motorAPwm,int16_t motorBPwm,int16_t motorCPwm,int16_t motorDPwm);



#endif
