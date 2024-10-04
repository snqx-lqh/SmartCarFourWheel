#include "bsp_timer.h"




void bsp_timer6_init(uint16_t arr,uint16_t psc)
{
    //ʱ�ӳ�ʼ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //ʱ��ʹ��
    //��ʱ����ʼ��
    {
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

        TIM_TimeBaseStructure.TIM_Period    =   arr-1;                      //�����Զ���װ��ֵ
        TIM_TimeBaseStructure.TIM_Prescaler =   psc-1;                    //����Ԥ��Ƶֵ
        TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //����ʱ�ӷָ�:TDTS = Tck_tim
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ

        TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
    }
    //NVIC��ʼ��
    {
        NVIC_InitTypeDef NVIC_InitStructure;

        NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;              //TIM6�ж�
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;    //��ռ���ȼ�0��
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;           //�����ȼ�3��
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              //IRQͨ����ʹ��

        NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
    }
    //��ʱ��ʹ���Լ������ж�
    {
        TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM6�ж�,��������ж�
        TIM_Cmd(TIM6, ENABLE);                    //ʹ��TIMx
    }
}
