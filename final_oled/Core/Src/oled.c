/*
 * oled.c
 *
 *  Created on: Nov 17, 2025
 *      Author: chrislann
 */

#include "oled.h"

#include "ssd1306.h"
#include "ssd1306_fonts.h"

#include "system_state.h"


// Call this function to display accelerometer data
void oled_accel_mode() {
	ssd1306_Fill(Black);

	ssd1306_SetCursor(5,5);

    switch(accelView) {
    	case 0:
    		ssd1306_WriteString("Accel X:", Font_7x10, White);
    		break;
		case 1:
			ssd1306_WriteString("Accel Y:", Font_7x10, White);
			break;
		case 2:
			ssd1306_WriteString("Accel Z:", Font_7x10, White);
			break;
		case 3:
			ssd1306_WriteString("Peak:",    Font_7x10, White);
			break;
	}

	ssd1306_UpdateScreen();
}

// Call this function to display and set speaker mode
void oled_speaker_mode() {
	ssd1306_Fill(Black);
	ssd1306_SetCursor(5,5);

	ssd1306_WriteString("Speaker 1", Font_7x10, White);

	ssd1306_UpdateScreen();
}

// Call this function to display and set volume level
void oled_volume_mode() {
	ssd1306_Fill(Black);
	ssd1306_SetCursor(5,5);

	ssd1306_WriteString("Volume 1", Font_7x10, White);

	ssd1306_UpdateScreen();
}
