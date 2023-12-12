#include "bsp_timer.h"




void bsp_timer6_init(uint16_t arr,uint16_t psc)
{
    //时钟初始化
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //时钟使能
    //定时器初始化
    {
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

        TIM_TimeBaseStructure.TIM_Period    =   arr-1;                      //设置自动重装载值
        TIM_TimeBaseStructure.TIM_Prescaler =   psc-1;                    //设置预分频值
        TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS = Tck_tim
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式

        TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
    }
    //NVIC初始化
    {
        NVIC_InitTypeDef NVIC_InitStructure;

        NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;              //TIM6中断
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;    //先占优先级0级
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;           //从优先级3级
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              //IRQ通道被使能

        NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
    }
    //定时器使能以及开启中断
    {
        TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE ); //使能指定的TIM6中断,允许更新中断
        TIM_Cmd(TIM6, ENABLE);                    //使能TIMx
    }
}
