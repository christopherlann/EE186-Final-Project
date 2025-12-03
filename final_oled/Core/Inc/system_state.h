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
extern uint8_t driftIndex;
extern float volumeScale;
extern uint8_t refreshDisplay;
extern uint8_t playSound;


#endif /* INC_SYSTEM_STATE_H_ */
