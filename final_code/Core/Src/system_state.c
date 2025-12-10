/*
 * system_state.c
 *
 *  Created on: Nov 19, 2025
 *      Author: chrislann
 */

#include "system_state.h"

#include <stdbool.h>


DisplayMode_t currentMode = MODE_START;

uint8_t accelView = 0;
uint8_t driftIndex = 0;
uint8_t volumeLevel = 0;
uint8_t refreshDisplay = 0;
bool playSound = 0;
bool turning = 0;

bool volumeSet = 0;

float volumeScale = .5;

