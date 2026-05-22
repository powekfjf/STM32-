#include "Infrared.h"
#include "tim.h"
#include "string.h"

extern uint8_t InfraredDat[5];
uint8_t InfraredFalg;
uint16_t Count=0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  static uint8_t i=0,k=0;
  if(InfraredFalg==0)
  {
    __HAL_TIM_SET_COUNTER(&htim2,0);
    HAL_TIM_Base_Start(&htim2);
    InfraredFalg++;
  }
  else if(InfraredFalg==1)
  {
    HAL_TIM_Base_Stop(&htim2);
    if(__HAL_TIM_GET_COUNTER(&htim2)>=13500)
    {
      InfraredFalg++;
    }
    else if(__HAL_TIM_GET_COUNTER(&htim2)>=11250&&__HAL_TIM_GET_COUNTER(&htim2)<13500)
    {
      InfraredFalg=0;
      InfraredDat[4]=0x55;
      return;
    }
    else
    {
      InfraredFalg=0;
      return;
    }
    __HAL_TIM_SET_COUNTER(&htim2,0);
    HAL_TIM_Base_Start(&htim2);
  }
  else if(InfraredFalg==2)
  {
    HAL_TIM_Base_Stop(&htim2);
    if(__HAL_TIM_GET_COUNTER(&htim2)>=2000)
    {
      InfraredDat[k]|=(0x01<<i);
    }
    i++;
    if(i==8)
    {
      k++;
      i=0;
    }
    if(k==4)
    {
      if(InfraredDat[0]==(uint8_t)~InfraredDat[1]&&InfraredDat[2]==(uint8_t)~InfraredDat[3])
      {
        InfraredDat[4]=0xAA;
      }
      else
      {
        //HAL_NVIC_SystemReset();
        Count++;
        InfraredDat[4]=0xFF;
        //memset(InfraredDat,0,sizeof(InfraredDat));
      }
      InfraredFalg=0;
      k=0;
      return;
    }
    __HAL_TIM_SET_COUNTER(&htim2,0);
    HAL_TIM_Base_Start(&htim2);
  }
}
