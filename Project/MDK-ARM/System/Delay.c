#include "stm32f1xx_hal.h"
#include "Delay.h"

void Delay_us(uint32_t ui)
{
  SysTick->LOAD=72*ui;
  SysTick->VAL=0;
  SysTick->CTRL=5;
  //while(SysTick->VAL);
  while(!(SysTick->CTRL & 0x00010000));
  SysTick->CTRL=4;
}

void Delay_ms(uint32_t mi)
{
  while(mi--)
  {
    Delay_us(1000);
  }
  
}

void Delay_s(uint32_t si)
{
  while(si--)
  {
    Delay_ms(1000);
  }
}
