#include "uart_visual_proc.h"

uint8_t rx_visual[20];
uint8_t rxdat;
unsigned char rx_pointer;

void uart_visual_proc(void)
{
    if (rx_pointer > 0)
    {
        if (rx_pointer == 2)
        {
            if (rx_visual[0] == 0x0F)
                if (rx_visual[1] == 0x01)
                {
                    if (lockState == LOCKED)
                    {
                        lockState = UNLOCKED;
                        HAL_UART_Transmit(&huart3, (uint8_t *)&"U", 1, 50);
                    }
                }
        }
    }

    rx_pointer = 0;
    memset(rx_visual, 0, 20);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *hurat)
{
    if (hurat->Instance == UART5)
    {
        rx_visual[rx_pointer++] = rxdat;
        HAL_UART_Receive_IT(&huart5, &rxdat, 1);
    }
}
