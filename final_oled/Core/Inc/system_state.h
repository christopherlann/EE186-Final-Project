/*
 * system_state.h
 *
 *  Created on: Nov 19, 2025
 *      Author: chrislann
 */

#ifndef INC_SYSTEM_STATE_H_
#define INC_SYSTEM_STATE_H_

#include <stdbool.h>
#include <stdint.h>


// OLED display modes
typedef enum {
    MODE_ACCEL,
    MODE_SOUND,
    MODE_VOLUME
} DisplayMode_t;

extern DisplayMode_t currentMode;

extern uint8_t accelView;
//extern uint8_t soundIndex;
//extern uint8_t volumeLevel;
extern uint8_t refreshDisplay;


#endif /* INC_SYSTEM_STATE_H_ */
