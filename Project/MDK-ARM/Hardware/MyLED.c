#include "main.h"
#include "MyLED.H"
#include "Delay.h"

void HAL_GPIO_Write(GPIO_TypeDef *GPIOx,uint16_t Dat)
{
  GPIOx->ODR=Dat;
}

void MyLED_FlowingLights(void)
{
  
}

void MyLED_DelayFlowingLights(uint32_t Time,uint8_t Kind)
{
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
  switch(Kind)
  {
    case 0:; Delay_us(Time);break;
    case 1:; Delay_ms(Time);break;
    case 2:; Delay_s(Time);break;
    default:; Delay_s(Time);break;
  }
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
  switch(Kind)
  {
    case 0:; Delay_us(Time);break;
    case 1:; Delay_ms(Time);break;
    case 2:; Delay_s(Time);break;
    default:; Delay_s(Time);break;
  }
}

void MyLED_FlashingPoliceLight(void)
{
  static uint8_t count=0;
  count++;
  if(count<20)
  {
    if(count%2)
    {
      HAL_GPIO_Write(GPIOA,0xF0);
    }
    else
    {
      HAL_GPIO_Write(GPIOA,0xFF);
    }
  }
  else
  {
    if(count%2)
    {
      HAL_GPIO_Write(GPIOA,0x0F);
    }
    else
    {
      HAL_GPIO_Write(GPIOA,0xFF);
    }
  }
  count%=40;
}
