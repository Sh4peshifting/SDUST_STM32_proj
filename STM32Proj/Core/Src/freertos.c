/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor.h"
#include "fire_detect.h"
#include "uart_web_proc.h"
#include "light_control.h"
#include "uart_audio_proc.h"
#include "uart_visual_proc.h"
#include "oled.h"
#include "key_matrix.h"
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
extern uint8_t lockState;
extern uint8_t alarmState;
extern bool alarm_off_flag;

extern uint8_t lightState;
extern uint8_t people;
extern uint8_t fanState;
extern uint8_t autoState;

extern uint8_t temperature;

extern unsigned char rx_pointer;

extern uint16_t Password;
extern uint16_t Count;
extern unsigned char KeyNum;
/* USER CODE END Variables */
osThreadId uart_webHandle;
osThreadId device_ctrlHandle;
osThreadId detect_ctrlHandle;
osThreadId uart_audioHandle;
osThreadId uart_visualHandle;
osSemaphoreId uartWebSemHandle;
osSemaphoreId uartAirSemHandle;
osSemaphoreId uartAudioSemHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartUartWeb(void const * argument);
void StartDeviceCtrl(void const * argument);
void StartDetectCtrl(void const * argument);
void StartUartAudio(void const * argument);
void StartUartVisual(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

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

  /* Create the semaphores(s) */
  /* definition and creation of uartWebSem */
  osSemaphoreDef(uartWebSem);
  uartWebSemHandle = osSemaphoreCreate(osSemaphore(uartWebSem), 1);

  /* definition and creation of uartAirSem */
  osSemaphoreDef(uartAirSem);
  uartAirSemHandle = osSemaphoreCreate(osSemaphore(uartAirSem), 1);

  /* definition and creation of uartAudioSem */
  osSemaphoreDef(uartAudioSem);
  uartAudioSemHandle = osSemaphoreCreate(osSemaphore(uartAudioSem), 1);

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
  /* definition and creation of uart_web */
  osThreadDef(uart_web, StartUartWeb, osPriorityHigh, 0, 128);
  uart_webHandle = osThreadCreate(osThread(uart_web), NULL);

  /* definition and creation of device_ctrl */
  osThreadDef(device_ctrl, StartDeviceCtrl, osPriorityNormal, 0, 128);
  device_ctrlHandle = osThreadCreate(osThread(device_ctrl), NULL);

  /* definition and creation of detect_ctrl */
  osThreadDef(detect_ctrl, StartDetectCtrl, osPriorityNormal, 0, 128);
  detect_ctrlHandle = osThreadCreate(osThread(detect_ctrl), NULL);

  /* definition and creation of uart_audio */
  osThreadDef(uart_audio, StartUartAudio, osPriorityHigh, 0, 128);
  uart_audioHandle = osThreadCreate(osThread(uart_audio), NULL);

  /* definition and creation of uart_visual */
  osThreadDef(uart_visual, StartUartVisual, osPriorityAboveNormal, 0, 128);
  uart_visualHandle = osThreadCreate(osThread(uart_visual), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartUartWeb */
/**
 * @brief  Function implementing the uart_web thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartUartWeb */
void StartUartWeb(void const * argument)
{
  /* USER CODE BEGIN StartUartWeb */
  /* Infinite loop */
  for (;;)
  {
    if (osSemaphoreWait(uartAirSemHandle, 1) == osOK)
      uart_air_rx_proc();

    uart_web_tx_proc();

    if (osSemaphoreWait(uartWebSemHandle, 1) == osOK)
      uart_web_rx_proc();
    osDelay(1);
  }
  /* USER CODE END StartUartWeb */
}

/* USER CODE BEGIN Header_StartDeviceCtrl */
/**
 * @brief Function implementing the device_ctrl thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDeviceCtrl */
void StartDeviceCtrl(void const * argument)
{
  /* USER CODE BEGIN StartDeviceCtrl */
  /* Infinite loop */
  for (;;)
  {
    if (fanState == DEVICE_OFF)
      Close_fan();
    else
      Open_fan(fanState);

    led_ctrl(lightState);

    Door_Lock_system(lockState);

    char str[15];
    if (lockState == LOCKED)
    {
      sprintf(str, "Enter Password");
      OLED_ShowString(0, 0, str, 12, 0);
      sprintf(str, "To Unlock   ");
      OLED_ShowString(0, 1, str, 12, 0);
      sprintf(str, "Password:");
      OLED_ShowString(0, 3, str, 16, 0);
      if (Password == 0)
        sprintf(str, "    ");
      else
        sprintf(str, "%d   ", Password);
      OLED_ShowString(2, 5, str, 16, 0);
    }
    else
    {
      sprintf(str, "Door Unlocked ");
      OLED_ShowString(0, 0, str, 12, 0);
      sprintf(str, "Welcome Home");
      OLED_ShowString(0, 1, str, 12, 0);
      sprintf(str, "         ");
      OLED_ShowString(0, 3, str, 16, 0);
      sprintf(str, "    ");
      OLED_ShowString(2, 5, str, 16, 0);
    }
    osDelay(1);
  }
  /* USER CODE END StartDeviceCtrl */
}

/* USER CODE BEGIN Header_StartDetectCtrl */
/**
 * @brief Function implementing the detect_ctrl thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDetectCtrl */
void StartDetectCtrl(void const * argument)
{
  /* USER CODE BEGIN StartDetectCtrl */
  /* Infinite loop */
  for (;;)
  {
    if (Fire_Human_System(temperature) == 0x00 || alarm_off_flag == true)
    {
      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, GPIO_PIN_RESET);
      alarmState = DEVICE_OFF;
    }
    else
    {
      uint8_t last_state = alarmState;
      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, GPIO_PIN_SET);
      if (Fire_Human_System(temperature) == 0x01)
      {
        alarmState = 0x03;
        if (last_state != alarmState)
          HAL_UART_Transmit(&huart2, (uint8_t *)&"Fire happen!\r\n", 15, 50);
      }
      if (Fire_Human_System(temperature) == 0x02)
      {
        alarmState = 0x01;
        if (last_state != alarmState)
          HAL_UART_Transmit(&huart2, (uint8_t *)&"Unknow human enter!\r\n", 22, 50);
      }
      if (Fire_Human_System(temperature) == 0x03)
      {
        alarmState = 0x04;
        if (last_state != alarmState)
          HAL_UART_Transmit(&huart2, (uint8_t *)&"Fire happen and unknow human enter!\r\n", 38, 50);
      }
    }

    if (autoState == DEVICE_ON)
    {
      if (people == 0)
        lightState = DEVICE_OFF;
      if (people)
      {
        light_sensor();
        light_control();
      }
    }

    KeyNum = MatrixKey();
    password_check();

    osDelay(1);
  }
  /* USER CODE END StartDetectCtrl */
}

/* USER CODE BEGIN Header_StartUartAudio */
/**
 * @brief Function implementing the uart_audio thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartUartAudio */
void StartUartAudio(void const * argument)
{
  /* USER CODE BEGIN StartUartAudio */
  /* Infinite loop */
  for (;;)
  {
    if (osSemaphoreWait(uartAudioSemHandle, 1) == osOK)
      uart_audio_proc();
    osDelay(1);
  }
  /* USER CODE END StartUartAudio */
}

/* USER CODE BEGIN Header_StartUartVisual */
/**
 * @brief Function implementing the uart_visual thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartUartVisual */
void StartUartVisual(void const * argument)
{
  /* USER CODE BEGIN StartUartVisual */
  /* Infinite loop */
  for (;;)
  {
    if (rx_pointer != 0)
    {
      int temp = rx_pointer;
      vTaskDelay(1);
      if (temp == rx_pointer)
        uart_visual_proc();
    }

    osDelay(1);
  }
  /* USER CODE END StartUartVisual */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

