#ifndef WM8731_h
#define WM8731_h

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "wire.h"
#include "fpga.h"

#define I2C_ADDRESS_WM8731 0x34

#define CODEC_AUDIO_BUFFER_SIZE FPGA_AUDIO_BUFFER_SIZE*2
extern uint16_t CODEC_Audio_Buffer[CODEC_AUDIO_BUFFER_SIZE];

extern uint8_t WM8731_SampleMode;
extern uint32_t WM8731_DMA_samples;

extern I2S_HandleTypeDef hi2s3;
extern bool WM8731_DMA_state;
void WM8731_SendI2CCommand(uint8_t reg, uint8_t value);
extern void WM8731_Init(void);
extern void WM8731_switchToActualSampleRate(int32_t rate);
extern void start_i2s_rx_dma(void);
extern void start_loopback_dma(void);

#endif