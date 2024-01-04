#include "uart_web_proc.h"

uint8_t rx_air[50];
uint8_t rxBuffer[50];

uint8_t lockState = LOCKED;
uint8_t alarmState = DEVICE_OFF;
bool alarm_off_flag = false;

uint8_t lightState = DEVICE_OFF;

uint8_t fanState = DEVICE_OFF;
uint8_t autoState = DEVICE_OFF;

uint8_t people = 0;

uint8_t eCO2_l = 0;
uint8_t eCO2_h = 0;
uint8_t eCH2O_l = 0;
uint8_t eCH2O_h = 0;
uint8_t TVOC_l = 0;
uint8_t TVOC_h = 0;
uint8_t PM25_l = 0;
uint8_t PM25_h = 0;
uint8_t PM10_l = 0;
uint8_t PM10_h = 0;
uint8_t temperature = 0;
uint8_t temperature_dec = 0;
uint8_t humidity = 0;
uint8_t humidity_dec = 0;

void uart_web_rx_proc(void)
{
    if (rxBuffer[0] == 0xFF)
    {
      switch (rxBuffer[1])
      {
      case WEB_LOCK_CTRL:
        (rxBuffer[2] == WEB_MODE_ON) ? (lockState = UNLOCKED) : (lockState = LOCKED);
        break;
      case WEB_ALARM_CTRL:
        if (rxBuffer[2] == WEB_MODE_ON)
        {
          alarm_off_flag = true;
        }
        break;
      case WEB_LIGHT_CTRL:
        if (rxBuffer[2] == WEB_MODE_ON)
        {
          lightState = DEVICE_ON;          
        }
        else if (rxBuffer[2] == WEB_MODE_OFF)
        {
          lightState = DEVICE_OFF;
        }
        else if (rxBuffer[2] == WEB_MODE_LOW)
        {
          lightState = LOW;
        }
        else if (rxBuffer[2] == WEB_MODE_MID)
        {
          lightState = MID;
        }
        else if (rxBuffer[2] == WEB_MODE_HIGH)
        {
          lightState = HIGH;
        }
        break;
      case WEB_FAN_CTRL:
        if (rxBuffer[2] == WEB_MODE_ON)
        {
          fanState = DEVICE_ON;
        }
        else if (rxBuffer[2] == WEB_MODE_OFF)
        {
          fanState = DEVICE_OFF;
        }
        else if (rxBuffer[2] == WEB_MODE_LOW)
        {
          fanState = LOW;
        }
        else if (rxBuffer[2] == WEB_MODE_MID)
        {
          fanState = MID;
        }
        else if (rxBuffer[2] == WEB_MODE_HIGH)
        {
          fanState = HIGH;
        }
        break;
      case WEB_AUTO_CTRL:
        if (rxBuffer[2] == WEB_MODE_ON)
        {
          autoState = DEVICE_ON;
        }
        else if (rxBuffer[2] == WEB_MODE_OFF)
        {
          autoState = DEVICE_OFF;
        }
        break;
      default:
        break;
      }
    }
    memset(rxBuffer, 0, 50); 
}

void uart_air_rx_proc(void)
{
    if (rx_air[0] == 0x3C && rx_air[1] == 0x02)
    {
      eCO2_h = rx_air[2];
      eCO2_l = rx_air[3];
      eCH2O_h = rx_air[4];
      eCH2O_l = rx_air[5];
      TVOC_h = rx_air[6];
      TVOC_l = rx_air[7];
      PM25_h = rx_air[8];
      PM25_l = rx_air[9];
      PM10_h = rx_air[10];
      PM10_l = rx_air[11];
      temperature = rx_air[12];
      temperature_dec = rx_air[13];
      humidity = rx_air[14];
      humidity_dec = rx_air[15];
    }    
}

void uart_web_tx_proc(void)
{
  char txBuffer [17];
  txBuffer[0] = 0xFF;
  txBuffer[1] = 0x55;
  txBuffer[2] = 0x01;

  txBuffer[3] = lockState;
  txBuffer[4] = lightState;
  txBuffer[5] = fanState;
  txBuffer[6] = alarmState;
  txBuffer[7] = autoState;

  people = Counter;

  txBuffer[8] = people;

  vTaskDelay(20);
  HAL_UART_Transmit(&huart1, (uint8_t *)txBuffer, sizeof(txBuffer), 50);

  txBuffer[0] = 0xFF;
  txBuffer[1] = 0x55;
  txBuffer[2] = 0x00;
  txBuffer[3] = temperature;
  txBuffer[4] = temperature_dec;
  txBuffer[5] = humidity;
  txBuffer[6] = humidity_dec;
  txBuffer[7] = eCH2O_h;
  txBuffer[8] = eCH2O_l;
  txBuffer[9] = eCO2_h;
  txBuffer[10] = eCO2_l;
  txBuffer[11] = TVOC_h;
  txBuffer[12] = TVOC_l;
  txBuffer[13] = PM25_h;
  txBuffer[14] = PM25_l;
  txBuffer[15] = PM10_h;
  txBuffer[16] = PM10_l;

  vTaskDelay(20);
  HAL_UART_Transmit(&huart1, (uint8_t *)txBuffer, sizeof(txBuffer), 50);

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  if (huart->Instance == USART1)
  {
    osSemaphoreRelease(uartWebSemHandle);
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rxBuffer, sizeof(rxBuffer));
    __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
  }
  if (huart->Instance == UART4)
  {
    osSemaphoreRelease(uartAirSemHandle);
    HAL_UARTEx_ReceiveToIdle_DMA(&huart4, rx_air, sizeof(rx_air));
    __HAL_DMA_DISABLE_IT(&hdma_uart4_rx, DMA_IT_HT);
  }

  if (huart->Instance == USART3)
  {
    osSemaphoreRelease(uartAudioSemHandle);
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_audio, sizeof(rx_audio));
    __HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);
  }
  
}

