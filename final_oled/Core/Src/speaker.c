/*
 * speaker.c
 *
 *  Created on: Dec 2, 2025
 *      Author: chrislann
 */


#include "speaker.h"

#include "system_state.h"

#include "utils.h"
#include <stdio.h>

#include "dac.h"

extern uint8_t *__USER_DATA;
extern uint8_t *__USER_DATA1;
extern uint8_t *__USER_DATA2;

uint8_t flg_dma_done;

#define BUFFERSIZE 20000
#define MIN(a,b) (((a)<(b))? (a):(b))


uint8_t *ptrDrift[3];
uint32_t samplesDrift[3];


// Speaker initialization
void initSpeaker() {
//	  HAL_TIM_Base_Start(&htim6);

	    // DRIFT 0
	    uint8_t *p = (uint8_t *)&__USER_DATA;
	    p += 40;
	    samplesDrift[0] = p[0]
	                    + (p[1] << 8)
	                    + (p[2] << 16)
	                    + (p[3] << 24);
	    samplesDrift[0] /= 2;
	    p += 4;
	    ptrDrift[0] = p;

	    // DRIFT 1
	    uint8_t *q = (uint8_t *)&__USER_DATA1;
	    q += 40;
	    samplesDrift[1] = q[0]
	                    + (q[1] << 8)
	                    + (q[2] << 16)
	                    + (q[3] << 24);
	    samplesDrift[1] /= 2;
	    q += 4;
	    ptrDrift[1] = q;

	    // DRIFT 2
	    uint8_t *r = (uint8_t *)&__USER_DATA2;
	    r += 40;
	    samplesDrift[2] = r[0]
	                    + (r[1] << 8)
	                    + (r[2] << 16)
	                    + (r[3] << 24);
	    samplesDrift[2] /= 2;
	    r += 4;
	    ptrDrift[2] = r;


}


// Play drift sounds
void playDrift(int driftIndex, float volumeScale) {

    printf("drift function: index=%d, volume=%.2f\r\n", driftIndex, volumeScale);


    int16_t *pp  = (int16_t *)ptrDrift[driftIndex];
    int samples  = samplesDrift[driftIndex];

    uint16_t dmaBuf[2][BUFFERSIZE];
    int bank = 0;

    flg_dma_done = 1;
    int count = samples;

	// load audio from flash memory
    while (count > 0)
    {
        int blksize = MIN(count, BUFFERSIZE);

   		// load current block
        for (int i = 0; i < blksize; i++)
        {
            int16_t v0 = *pp;
			pp++;
            int32_t v = v0 >> 4;
            v += 2047;
            v = (float)v * volumeScale;
            dmaBuf[bank][i] = (int32_t)v & 0x0FFF;
        }


        while (!flg_dma_done) {
            __NOP();
        }

        flg_dma_done = 0;

		// start playing
        printf("start playing\r\n");
        HAL_DAC_Start_DMA(
            &hdac1,
            DAC_CHANNEL_1,
            (uint32_t*)dmaBuf[bank],
            blksize,
            DAC_ALIGN_12B_R
        );

        bank = !bank;
        count -= blksize;
    }

    printf("end drift\r\n");


    HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_1);
}
