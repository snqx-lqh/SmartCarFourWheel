#include "bsp_usart.h"
#include "stdio.h"

void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {

        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}

//重定义fputc函数
int fputc(int ch, FILE *f)
{
    while((USART2->SR&0X40)==0);//循环发送,直到发送完毕
    USART2->DR = (u8) ch;
    return ch;
}


void bsp_usart2_init(u32 bound)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,  ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,  ENABLE);	//使能USART2，GPIOA时钟
    //GPIO端口设置
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        //USART2_TX   GPIOA.2
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        //USART2_RX	  GPIOA.3初始化
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    //Usart2 NVIC 配置
    {
        NVIC_InitTypeDef NVIC_InitStructure;

        NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
        NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器
    }
    //USART 初始化设置
    {
        USART_InitTypeDef USART_InitStructure;
        USART_InitStructure.USART_BaudRate = bound;//串口波特率
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
        USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
        USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

        USART_Init(USART2, &USART_InitStructure); //初始化串口1
        USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
        USART_Cmd(USART2, ENABLE);                    //使能串口1
    }
}


