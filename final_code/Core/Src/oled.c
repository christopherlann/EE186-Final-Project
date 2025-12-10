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

    switch(driftIndex) {
    	case 0:
    		ssd1306_WriteString("SCREECH", Font_11x18, White);
    		break;
		case 1:
			ssd1306_WriteString("SWERVE", Font_11x18, White);
			break;
		case 2:
			ssd1306_WriteString("DRIFT", Font_11x18, White);
			break;
	}

	ssd1306_UpdateScreen();

}

// Call this function to display the volume level
void oled_volume_mode() {
    ssd1306_Fill(Black);

    const int segments = 10;

    // VolumeScale to bar segments
    int filledSegments = (int)(volumeScale * segments + 0.05f);	// small offset for boundaries

    // Clamp because minimum volume is 0.1, and max is 1
    if (filledSegments < 1) {
    	filledSegments = 1;
    }
    if (filledSegments > segments) {
    	filledSegments = segments;
    }

    // Bar geometry
    int segmentWidth  = 12;
    int segmentHeight = 20;
    int barWidth = segments * segmentWidth;
    int startX = (128 - barWidth) / 2;			// Center on screen
    int startY = 20;

    // Compute rectangles
    for (int i = 0; i < segments; i++) {
        int x1 = startX + i * (segmentWidth);
        int y1 = startY;
        int x2 = x1 + segmentWidth - 1;
        int y2 = y1 + segmentHeight - 1;

        if (i < filledSegments) {
            // Filled rectangle
            ssd1306_FillRectangle(x1, y1, x2, y2, White);
        } else {
            // Outline rectangle
            ssd1306_DrawRectangle(x1, y1, x2, y2, White);
        }
    }

    ssd1306_UpdateScreen();
}


// Call this function to display that volume is set
void oled_volume_set() {
	// Display volume set message
	ssd1306_Fill(Black);
	ssd1306_SetCursor(5,5);
	ssd1306_WriteString("Volume set", Font_11x18, White);
    ssd1306_UpdateScreen();
}












