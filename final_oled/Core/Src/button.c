/*
 * button.c
 *
 *  Created on: Nov 19, 2025
 *      Author: chrislann
 */

#include "button.h"
#include "system_state.h"

#include "main.h"

#include "utils.h"
#include <stdio.h>


// State variables

static ButtonState_t buttonState = BUTTON_IDLE;
static uint32_t debounceStart = 0;
static uint32_t pressStart = 0;

static uint8_t clickCount = 0;
static uint32_t lastReleaseTime = 0;

static volatile bool buttonIRQFlag = false;


/*
 * Set the external interrupt flag
 */
void button_SetIRQFlag(void)
{
    buttonIRQFlag = true;
}


/*
 * Handles short button presses
 *
 * Cycles between OLED mode's different display views
 */
void handle_short_press() {

    switch (currentMode) {

		case MODE_ACCEL:
			// Cycle between different accelerometer views
			accelView = (accelView + 1) % 4;
			refreshDisplay = 1;
			break;

		case MODE_SOUND:
			// Cycle between different sounds
	        driftIndex = (driftIndex + 1) % 3;
			refreshDisplay = 1;
			playSound = 1;
			break;

		case MODE_VOLUME:
//	        volumeLevel = MIN(volumeLevel + 1, 10);
			refreshDisplay = 1;
			break;
    }
}


/*
 * Handles long button presses
 *
 * Cycles between different display modes
 */
void handle_long_press() {

    switch (currentMode) {

		case MODE_ACCEL:
//			peakAccel = 0;  // reset peak
			refreshDisplay = 1;
			break;

		case MODE_SOUND:
//			selectedSound = soundIndex;
			refreshDisplay = 1;
			break;

		case MODE_VOLUME:
			refreshDisplay = 1;
			break;
    }

    // Switch to next mode on long press
    currentMode = (currentMode + 1) % 3;
}


/*
 * Handles button press and debounce
 *
 * Debounce state machine
 */
void handle_button(void)
	{
	    uint32_t now = HAL_GetTick();

	    switch (buttonState)
	    {
	        case BUTTON_IDLE:
	            if (buttonIRQFlag)
	            {
	                buttonIRQFlag = 0;
	                debounceStart = now;
	                buttonState = BUTTON_DEBOUNCE;
	            }
	            break;

	        case BUTTON_DEBOUNCE:
	            if (now - debounceStart >= DEBOUNCE_MS)
	            {
	                if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_RESET)   // active low
	                {
	                    pressStart = now;
	                    buttonState = BUTTON_PRESSED;
	                }
	                else
	                {
	                    buttonState = BUTTON_IDLE;
	                }
	            }
	            break;

	        case BUTTON_PRESSED:
	            if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_SET)
	            {
	                buttonState = BUTTON_RELEASED;
	            }
	            break;

	        case BUTTON_RELEASED:
	        {
	            uint32_t duration = now - pressStart;

	            if (duration >= LONG_PRESS_MS)
	            {
	                printf("Long Press\r\n");
	                clickCount = 0;
	                handle_long_press();
	            }
	            else
	            {
	                clickCount++;
	                lastReleaseTime = now;
	            }

	            buttonState = BUTTON_IDLE;
	            break;
	        }

	        default:
	            buttonState = BUTTON_IDLE;
	            break;
	    }

	    // single/double click
	    if (clickCount > 0 && (now - lastReleaseTime > DOUBLE_CLICK_MS))
	    {
	        if (clickCount == 1) {
	            printf("Single Click\r\n");
	        	handle_short_press();
	        }
	        else {
	            printf("Double Click\r\n");
	        }
	        clickCount = 0;
	    }
	}
