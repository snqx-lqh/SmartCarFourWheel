#include "control.h"

void car_control()
{


}

void TIM6_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
    {
  
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );   //���TIMx�����жϱ�־
    }
}
