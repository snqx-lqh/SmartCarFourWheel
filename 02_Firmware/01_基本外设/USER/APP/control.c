#include "control.h"

void car_control()
{


}

void TIM6_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
    {
  
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );   //清除TIMx更新中断标志
    }
}
