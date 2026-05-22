/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "tim.h"
#include "cmsis_os.h"
#include "OLED.H"
#include "string.h"
#include "MyLED.H"

uint8_t InfraredDat[5];
uint8_t MyLEDControl=0;
extern uint8_t Count;

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t MyRTOSID;
const osThreadAttr_t MyRTOSConfig1=
{
  .name="MyRTOSTask1",
  .stack_size=128,
  .priority=(osPriority_t) osPriorityLow2,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void MyRTOSTask1(void *p);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  MyRTOSID=osThreadNew(MyRTOSTask1,NULL,&MyRTOSConfig1);
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */
  
  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    OLED_ShowNum(2,8,Count,5);
    OLED_ShowNum(4,8,__HAL_TIM_GET_COUNTER(&htim2),5);
    if(InfraredDat[4]==0xAA)
    {
      OLED_ShowString(1,8,"        ");
      OLED_ShowHexNum(2,1,InfraredDat[2],2);
      OLED_ShowHexNum(4,1,InfraredDat[4],2);
      MyLEDControl=InfraredDat[2];
      memset(InfraredDat,0,sizeof(InfraredDat));
    }
    else if(InfraredDat[4]==0x55)
    {
      OLED_ShowString(1,8,"Repeat");
      OLED_ShowHexNum(4,1,InfraredDat[4],2);
    }
    else if(InfraredDat[4]==0xFF)
    {
      OLED_ShowString(1,8,"ERR     ");
      memset(InfraredDat,0,sizeof(InfraredDat));
    }
    osDelay(10);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
  void MyRTOSTask1(void *p)
  {
    while(1)
    {
      if(MyLEDControl==0x45)
      {
        HAL_GPIO_Write(GPIOA,0xFF);
      }
      else if(MyLEDControl==0x44)
      {
        MyLED_FlashingPoliceLight();
      }
      osDelay(30);
    }
  }
/* USER CODE END Application */

