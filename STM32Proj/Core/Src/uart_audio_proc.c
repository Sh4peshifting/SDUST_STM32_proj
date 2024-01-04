#include "uart_audio_proc.h"

uint8_t rx_audio[50];

void uart_audio_proc(void)
{
    if (rx_audio[0] == 0xAF)
    {
        switch (rx_audio[1])
        {
        case AUDIO_LOCK_CTRL:
            (rx_audio[2] == AUDIO_MODE_ON) ? (lockState = UNLOCKED) : (lockState = LOCKED);
            break;
        case AUDIO_ALARM_CTRL:
            if (rx_audio[2] == AUDIO_MODE_ON)
            {
                alarm_off_flag = true;
            }
            break;
        case AUDIO_LIGHT_CTRL:
            if (rx_audio[2] == AUDIO_MODE_ON)
            {
                lightState = DEVICE_ON;
            }
            else if (rx_audio[2] == AUDIO_MODE_OFF)
            {
                lightState = DEVICE_OFF;
            }
            else if (rx_audio[2] == AUDIO_MODE_LOW)
            {
                lightState = LOW;
            }
            else if (rx_audio[2] == AUDIO_MODE_MID)
            {
                lightState = MID;
            }
            else if (rx_audio[2] == AUDIO_MODE_HIGH)
            {
                lightState = HIGH;
            }
            break;
        case AUDIO_FAN_CTRL:
            if (rx_audio[2] == AUDIO_MODE_ON)
            {
                fanState = DEVICE_ON;
            }
            else if (rx_audio[2] == AUDIO_MODE_OFF)
            {
                fanState = DEVICE_OFF;
            }
            else if (rx_audio[2] == AUDIO_MODE_LOW)
            {
                fanState = LOW;
            }
            else if (rx_audio[2] == AUDIO_MODE_MID)
            {
                fanState = MID;
            }
            else if (rx_audio[2] == AUDIO_MODE_HIGH)
            {
                fanState = HIGH;
            }
            break;
        
        default:
            break;
        }
    }
    
}
