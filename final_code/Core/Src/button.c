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

#include "speaker.h"


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

    	case MODE_START:
    		// Go to next mode
    	    currentMode = MODE_ACCEL;
    	    refreshDisplay = 1;
    	    break;

		case MODE_ACCEL:
			accelView = (accelView + 1) % 4; 		// Cycle between different accelerometer views
			refreshDisplay = 1;
			break;

		case MODE_SOUND:
	        driftIndex = (driftIndex + 1) % 3;		// Cycle between different sounds
	        loadDrift(driftIndex, volumeScale);		// Load drift into memory when index changes
			refreshDisplay = 1;
			break;

		case MODE_VOLUME:
			refreshDisplay = 1;
			volumeSet = 0;					// Reset volume set flag

			// Increase volume
			volumeScale += 0.1f;
			if (volumeScale > 1.0f) {
			    volumeScale = 1.0f;
			}

			break;

		default:
			currentMode = MODE_START;
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

		case MODE_START:
			// Go to next mode
			currentMode = MODE_ACCEL;
			refreshDisplay = 1;
			break;

		case MODE_ACCEL:
			currentMode = MODE_SOUND;
			accelView = 0;				// reset accel view
			refreshDisplay = 1;
			break;

		case MODE_SOUND:
			currentMode = MODE_VOLUME;
			refreshDisplay = 1;
			break;

		case MODE_VOLUME:

			// On first long press load drift into memory with new volume
			if (!volumeSet) {
				loadDrift(driftIndex, volumeScale);
				volumeSet = 1;
				refreshDisplay = 1;
			// On second uninterrupted long press go to next view
			} else {
				currentMode = MODE_ACCEL;
				refreshDisplay = 1;
				volumeSet = 0;
			}
			break;

		default:
			currentMode = MODE_START;
			refreshDisplay = 1;
			break;
    }
}



/*
 * Handles double button presses
 *
 * Plays sound
 * TODO: implement volume control instead of playing sound
 */
void handle_double_press() {
	if (currentMode == MODE_VOLUME) {
		volumeSet = 0;					// Reset volume set flag
		refreshDisplay = 1;
		// decrease volume
        volumeScale -= 0.1f;
        if (volumeScale < 0.1f) {
            volumeScale = 0.1f;
        }
//        loadDrift(driftIndex, volumeScale);
	}
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
                handle_double_press();

	        }
	        clickCount = 0;
	    }
	}
