/*
 * speaker.h
 *
 *  Created on: Dec 2, 2025
 *      Author: chrislann
 */

#ifndef INC_SPEAKER_H_
#define INC_SPEAKER_H_

void initSpeaker(void);

void loadDrift(int driftIndex, float volumeScale);

void playDrift(void);

#endif /* INC_SPEAKER_H_ */
