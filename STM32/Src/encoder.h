#ifndef Encoder_h
#define Encoder_h

#include "stm32f4xx_hal.h"

void ENCODER_Init(void);
void ENCODER_checkRotate(void);
void ENCODER_checkClick(void);
void ENCODER_Rotated(int direction);

extern int ENCODER_ALast;
extern int ENCODER_AVal;
extern uint32_t ENCODER_last_micros_clickdebouncer;

#endif
