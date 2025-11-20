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

static ButtonState buttonState = BUTTON_IDLE;
static uint32_t debounceStart = 0;
static uint32_t pressStart = 0;

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

//    printf("short press\r\n");	// debug

    switch (currentMode) {

		case MODE_ACCEL:
			// Cycle between different accelerometer views
			accelView = (accelView + 1) % 4;
			refreshDisplay = 1;
			break;

		case MODE_SOUND:
			// Cycle between different sounds
//	        soundIndex = (soundIndex + 1) % NUM_SOUNDS;
			refreshDisplay = 1;
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

//    printf("long press\r\n");	// debug

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
	// Get accurate time
    uint32_t now = HAL_GetTick();


    // State machine for debouncing
    switch (buttonState)
    {
    	// Waiting state
        case BUTTON_IDLE:
            // Interrupt detected rising edge
            if (buttonIRQFlag)
            {
                buttonIRQFlag = false;
                debounceStart = now;			// Start debounce time
                buttonState = BUTTON_DEBOUNCE;
            }
            break;

        // Debounce state
        case BUTTON_DEBOUNCE:
            // Wait for debounce time
            if (now - debounceStart >= DEBOUNCE_MS)
            {
                // Check button state after debouncing time
                if (HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) == GPIO_PIN_SET)
                {
                    pressStart = now;
                    buttonState = BUTTON_PRESSED;
                }
                else
                {
                    // Return to idle for a bounce
                    buttonState = BUTTON_IDLE;
                }
            }
            break;

        // Pressed state
        case BUTTON_PRESSED:
            // Button has been verified as pressed.
            // Check if released.
            if (HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) == GPIO_PIN_RESET)
            {
                buttonState = BUTTON_RELEASED;
            }
            break;

        // Released state
        case BUTTON_RELEASED:
        {
            uint32_t pressDuration = now - pressStart;

            if (pressDuration >= LONG_PRESS_MS)
            {
            	// Long press
            	handle_long_press();
            }
            else
            {
            	// Short press
            	handle_short_press();
            }

            buttonState = BUTTON_IDLE;
            break;
        }

        // Default state
        default:
            buttonState = BUTTON_IDLE;
            break;
    }
}


