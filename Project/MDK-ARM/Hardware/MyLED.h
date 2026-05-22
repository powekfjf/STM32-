#ifndef __MyLED_H__
#define __MyLED_H__

void MyLED_FlowingLights(void);
void MyLED_DelayFlowingLights(uint32_t Time,uint8_t Kind);
void MyLED_FlashingPoliceLight(void);
void HAL_GPIO_Write(GPIO_TypeDef *GPIOx,uint16_t Dat);

#endif

