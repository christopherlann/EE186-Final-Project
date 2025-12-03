/*
 * button.h
 *
 *  Created on: Nov 19, 2025
 *      Author: chrislann
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_


void button_SetIRQFlag(void);

void handle_short_press(void);

void handle_long_press(void);

void handle_button(void);


typedef enum {
    BUTTON_IDLE,
    BUTTON_DEBOUNCE,
    BUTTON_PRESSED,
    BUTTON_RELEASED
} ButtonState_t;


//#define DEBOUNCE_MS     50
//#define LONG_PRESS_MS   600

#define DEBOUNCE_MS        50
#define LONG_PRESS_MS     800
#define DOUBLE_CLICK_MS   300



#endif /* INC_BUTTON_H_ */
