/*
 * system_state.c
 *
 *  Created on: Nov 19, 2025
 *      Author: chrislann
 */

#include "system_state.h"


DisplayMode_t currentMode = MODE_ACCEL;

uint8_t accelView = 0;
uint8_t driftIndex = 0;
uint8_t volumeLevel = 0;
uint8_t refreshDisplay = 0;
uint8_t playSound = 0;

float volumeScale = 1;

