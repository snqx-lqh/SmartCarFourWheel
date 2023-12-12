#include "bsp_usart.h"
#include "stdio.h"

#include "bluetooth_debugger.h"

void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
		u8 res;
		res = USART_ReceiveData(USART2);
		//USART_SendData(USART2,res);
		get_usart_data(res,usart_rx_buff);
		data_unpacket(&rx_pack_ptr,usart_rx_buff);
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}

//�ض���fputc����
int fputc(int ch, FILE *f)
{
    while((USART2->SR&0X40)==0);//ѭ������,ֱ���������
    USART2->DR = (u8) ch;
    return ch;
}

void usart2_send_byte(u8 Byte)
{
   USART_SendData(USART2,Byte);    //���ô��ڵ�SendDate()����
   while (USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET);
}

void usart2_send_array(u8 *Array,u16 Length)
{
    u16 i;
    for ( i = 0; i < Length; i++)
    {
        usart2_send_byte(Array[i]);
    }
}

void bsp_usart2_init(u32 bound)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,  ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,  ENABLE);	//ʹ��USART2��GPIOAʱ��
    //GPIO�˿�����
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        //USART2_TX   GPIOA.2
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        //USART2_RX	  GPIOA.3��ʼ��
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    //Usart2 NVIC ����
    {
        NVIC_InitTypeDef NVIC_InitStructure;

        NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
        NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���
    }
    //USART ��ʼ������
    {
        USART_InitTypeDef USART_InitStructure;
        USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
        USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
        USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

        USART_Init(USART2, &USART_InitStructure); //��ʼ������2
        USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
        USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���2
    }
}


