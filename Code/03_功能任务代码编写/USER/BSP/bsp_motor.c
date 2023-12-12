/*
参考：https://blog.csdn.net/wangyang666__/article/details/120802967
*/

#include "bsp_motor.h"

int16_t read_encoder(u8 TIMX)
{
    int Encoder_TIM;
    switch(TIMX)
    {
    case 2:
        Encoder_TIM= (short)TIM2 -> CNT;
        TIM2 -> CNT=0;
        break;
    case 3:
        Encoder_TIM= (short)TIM3 -> CNT;
        TIM3 -> CNT=0;
        break;
    case 4:
        Encoder_TIM= (short)TIM4 -> CNT;
        TIM4 -> CNT=0;
        break;
	case 5:
        Encoder_TIM= (short)TIM5 -> CNT;
        TIM5 -> CNT=0;
        break;
    default:
        Encoder_TIM=0;
    }
    return Encoder_TIM;
}

void motor_pwm_limit(int16_t *motor_pwm)
{
	if(*motor_pwm > MAX_PWM_SET*0.9)       *motor_pwm = MAX_PWM_SET*0.9;
	else if(*motor_pwm < -MAX_PWM_SET*0.9) *motor_pwm = -MAX_PWM_SET*0.9;
}

void motor_pwm_set(int16_t motorAPwm,int16_t motorBPwm,int16_t motorCPwm,int16_t motorDPwm)
{
	motor_pwm_limit(&motorAPwm);
	motor_pwm_limit(&motorBPwm);
	motor_pwm_limit(&motorCPwm);
	motor_pwm_limit(&motorDPwm);
	
	if(motorAPwm>0)
	{
		MOTORA_PWMA_SET(MOTORA_TIM,motorAPwm);
		MOTORA_PWMB_SET(MOTORA_TIM,0);
	}else 
	{
		MOTORA_PWMA_SET(MOTORA_TIM,0);
		MOTORA_PWMB_SET(MOTORA_TIM,-motorAPwm);
	}
	
	if(motorBPwm>0)
	{
		MOTORB_PWMA_SET(MOTORB_TIM,motorBPwm);
		MOTORB_PWMB_SET(MOTORB_TIM,0);
	}else 
	{
		MOTORB_PWMA_SET(MOTORB_TIM,0);
		MOTORB_PWMB_SET(MOTORB_TIM,-motorBPwm);
	}
	
	if(motorCPwm>0)
	{
		MOTORC_PWMA_SET(MOTORC_TIM,motorCPwm);
		MOTORC_PWMB_SET(MOTORC_TIM,0);
	}else 
	{
		MOTORC_PWMA_SET(MOTORC_TIM,0);
		MOTORC_PWMB_SET(MOTORC_TIM,-motorCPwm);
	}
	
	if(motorDPwm>0)
	{
		MOTORD_PWMA_SET(MOTORD_TIM,motorDPwm);
		MOTORD_PWMB_SET(MOTORD_TIM,0);
	}else 
	{
		MOTORD_PWMA_SET(MOTORD_TIM,0);
		MOTORD_PWMB_SET(MOTORD_TIM,-motorDPwm);
	}
	
}

void bsp_motor_init(void)
{
	bsp_motor_pwm_init(7200,10); //10K
	bsp_encoder_init();
}

void bsp_motor_pwm_init(u16 arr,u16 psc)
{
	//TIM1
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;	
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIO外设时钟使能
		
		//设置该引脚为复用输出功能,输出TIM1 CH1 CH2 CH3 CH4的PWM脉冲波形
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
		TIM_TimeBaseStructure.TIM_Period = arr-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 
		TIM_TimeBaseStructure.TIM_Prescaler =psc-1; //设置用来作为TIMx时钟频率除数的预分频值  不分频
		TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_Pulse = 0;                            //设置待装入捕获比较寄存器的脉冲值
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //输出极性:TIM输出比较极性高
		TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
		TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
		TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
		TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

		TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	

		TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能	 
		TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH2预装载使能	
		TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH3预装载使能	
		TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH4预装载使能	 
		
		TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
		
		TIM_Cmd(TIM1, ENABLE);  //使能TIM1
	}
	//TIM8
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;	
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);// 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);  //使能GPIO外设时钟使能
		
		//设置该引脚为复用输出功能,输出TIM8 CH1 CH2 CH3 CH4的PWM脉冲波形
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		
		TIM_TimeBaseStructure.TIM_Period = arr-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 
		TIM_TimeBaseStructure.TIM_Prescaler =psc-1; //设置用来作为TIMx时钟频率除数的预分频值  不分频
		TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		//TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
		TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_Pulse = 0;                            //设置待装入捕获比较寄存器的脉冲值
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //输出极性:TIM输出比较极性高
		TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
		TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
		TIM_OC3Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
		TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

		TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE 主输出使能	

		TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1预装载使能	 
		TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH2预装载使能	
		TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH3预装载使能	
		TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH4预装载使能	 
		
		TIM_ARRPreloadConfig(TIM8, ENABLE); //使能TIMx在ARR上的预装载寄存器
		
		TIM_Cmd(TIM8, ENABLE);  //使能TIM8
	}
}

void bsp_encoder_init()
{
    //TIM2
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//使能定时器2的时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能PA端口时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能PB端口时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO ,ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
        {
            GPIO_InitTypeDef GPIO_InitStructure;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	//端口配置
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
            GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA
			
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	//端口配置
			GPIO_Init(GPIOB, &GPIO_InitStructure);	
			
			GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
        }
        {
            TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
            TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
            TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器
            TIM_TimeBaseStructure.TIM_Period = (u16)(65535); //设定计数器自动重装值
            TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数
            TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

        }
        {
            TIM_ICInitTypeDef TIM_ICInitStructure;
            TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
            TIM_ICStructInit(&TIM_ICInitStructure);
            TIM_ICInitStructure.TIM_ICFilter = 10;
            TIM_ICInit(TIM2, &TIM_ICInitStructure);
        }
        TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM的更新标志位
        TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
        //Reset counter
        TIM_SetCounter(TIM2,0);
        TIM_Cmd(TIM2, ENABLE);
    }
	//TIM3
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//使能定时器3的时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能PB端口时钟
        {
            GPIO_InitTypeDef GPIO_InitStructure;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;	//端口配置
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
            GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB
			GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

        }
        {
            TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
            TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
            TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器
            TIM_TimeBaseStructure.TIM_Period = (u16)(65535); //设定计数器自动重装值
            TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数
            TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

        }
        {
            TIM_ICInitTypeDef TIM_ICInitStructure;
            TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
            TIM_ICStructInit(&TIM_ICInitStructure);
            TIM_ICInitStructure.TIM_ICFilter = 10;
            TIM_ICInit(TIM3, &TIM_ICInitStructure);
        }
        TIM_ClearFlag(TIM3, TIM_FLAG_Update);//清除TIM的更新标志位
        TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
        //Reset counter
        TIM_SetCounter(TIM3,0);
        TIM_Cmd(TIM3, ENABLE);
    }
	//TIM4
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器4的时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能PB端口时钟
        {
            GPIO_InitTypeDef GPIO_InitStructure;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//端口配置
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
			GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB
        }
        {
            TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
            TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
            TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器
            TIM_TimeBaseStructure.TIM_Period = (u16)(65535); //设定计数器自动重装值
            TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数
            TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

        }
        {
            TIM_ICInitTypeDef TIM_ICInitStructure;
            TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
			TIM_ICStructInit(&TIM_ICInitStructure);
			TIM_ICInitStructure.TIM_ICFilter = 10;
			TIM_ICInit(TIM4, &TIM_ICInitStructure);
        }
        TIM_ClearFlag(TIM4, TIM_FLAG_Update);//清除TIM的更新标志位
		TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
		//Reset counter
		TIM_SetCounter(TIM4,0);
		TIM_Cmd(TIM4, ENABLE);
    }
	//TIM5
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//使能定时器5的时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能PA端口时钟
        {
            GPIO_InitTypeDef GPIO_InitStructure;
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//端口配置
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
			GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB
        }
        {
            TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
            TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
            TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器
            TIM_TimeBaseStructure.TIM_Period = (u16)(65535); //设定计数器自动重装值
            TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数
            TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

        }
        {
            TIM_ICInitTypeDef TIM_ICInitStructure;
            TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
			TIM_ICStructInit(&TIM_ICInitStructure);
			TIM_ICInitStructure.TIM_ICFilter = 10;
			TIM_ICInit(TIM5, &TIM_ICInitStructure);
        }
        TIM_ClearFlag(TIM5, TIM_FLAG_Update);//清除TIM的更新标志位
		TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
		//Reset counter
		TIM_SetCounter(TIM5,0);
		TIM_Cmd(TIM5, ENABLE);
    }
}

/**************************************************************************
函数功能：TIM5中断服务函数
入口参数：无
返回  值：无
**************************************************************************/
void TIM5_IRQHandler(void)
{
    if(TIM5->SR&0X0001)//溢出中断
    {
    }
    TIM5->SR&=~(1<<0);//清除中断标志位
}
/**************************************************************************
函数功能：TIM4中断服务函数
入口参数：无
返回  值：无
**************************************************************************/
void TIM4_IRQHandler(void)
{
    if(TIM4->SR&0X0001)//溢出中断
    {
    }
    TIM4->SR&=~(1<<0);//清除中断标志位
}
/**************************************************************************
函数功能：TIM3中断服务函数
入口参数：无
返回  值：无
**************************************************************************/
void TIM3_IRQHandler(void)
{
    if(TIM3->SR&0X0001)//溢出中断
    {
    }
    TIM3->SR&=~(1<<0);//清除中断标志位
}
/**************************************************************************
函数功能：TIM2中断服务函数
入口参数：无
返回  值：无
**************************************************************************/
void TIM2_IRQHandler(void)
{
    if(TIM2->SR&0X0001)//溢出中断
    {
    }
    TIM2->SR&=~(1<<0);//清除中断标志位
}
