/*
 * led.c
 *
 *  Created on: Dec 7, 2025
 *      Author: chrislann
 */

#include "led.h"
#include <stdint.h>

//#include "main.h"
#include "tim.h"

void led_init() {
	 HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2); // PA5
	 HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3); // PA1
	 HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4); // PA2
}


void Set_LED_Brightness(float level)
{

    uint32_t max = __HAL_TIM_GET_AUTORELOAD(&htim2);

    uint32_t duty_green  = 0;
    uint32_t duty_yellow = 0;
    uint32_t duty_red    = 0;

    level = level * 100;

    if (level <= 33)
    {
        // scale green
        float scale = level / 33.0f;
        duty_green = (uint32_t)(scale * max);
    }
    else if (level <= 66)
    {
        // green max, scale yellow
        duty_green = max;
        float scale = (level - 33) / 33.0f;
        duty_yellow = (uint32_t)(scale * max);
    }
    else
    {
        // green and yellow max, scale red
        duty_green = max;
        duty_yellow = max;
        float scale = (level - 66) / 34.0f;
        duty_red = (uint32_t)(scale * max);
    }


    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, duty_green);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, duty_yellow);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, duty_red);
}
