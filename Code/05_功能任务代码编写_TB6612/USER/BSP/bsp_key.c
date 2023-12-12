#include "bsp_key.h"

void bsp_key_init()
{
    //打开时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    //初始化IO口
    {
        GPIO_InitTypeDef GPIO_InitStruct;

        GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_2;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;

        GPIO_Init(GPIOD,&GPIO_InitStruct);
		
		GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
		
		GPIO_Init(GPIOC,&GPIO_InitStruct);
		
		GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_12;
		
		GPIO_Init(GPIOB,&GPIO_InitStruct);
    }
}

