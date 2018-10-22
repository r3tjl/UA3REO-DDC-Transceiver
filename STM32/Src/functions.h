#ifndef Functions_h
#define Functions_h

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "arm_math.h"

#define    DWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define    DWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define    SCB_DEMCR     *(volatile unsigned long *)0xE000EDFC

// Internal Macros
#define HEX__(n) 0x##n##LU
#define B8__(x) ((x&0x0000000FLU)?1:0) \
+((x&0x000000F0LU)?2:0) \
+((x&0x00000F00LU)?4:0) \
+((x&0x0000F000LU)?8:0) \
+((x&0x000F0000LU)?16:0) \
+((x&0x00F00000LU)?32:0) \
+((x&0x0F000000LU)?64:0) \
+((x&0xF0000000LU)?128:0)

// User-visible Macros
#define B8(d) ((unsigned char)B8__(HEX__(d)))
#define B16(dmsb,dlsb) (((unsigned short)B8(dmsb)<<8) + B8(dlsb))
#define B32(dmsb,db2,db3,dlsb) \
(((unsigned long)B8(dmsb)<<24) \
+ ((unsigned long)B8(db2)<<16) \
+ ((unsigned long)B8(db3)<<8) \
+ B8(dlsb))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

extern UART_HandleTypeDef huart1;
extern uint8_t FPGA_spi_data;

uint32_t getFrequencyFromPhrase(uint32_t phrase);
uint32_t getPhraseFromFrequency(uint32_t freq);
uint32_t hexStringToInt(char* in);
void addSymbols(char* dest, char* str, uint8_t length, char* symbol, bool toEnd);
void logToUART1_str(char* str);
void logToUART1_num(uint8_t data);
void logToUART1_numinline(uint8_t data);
void logToUART1_num16(uint16_t data);
void logToUART1_num32(uint32_t data);
void logToUART1_int16(int16_t data);
void logToUART1_float32(float32_t data);
void delay_us(uint32_t us);
float log10f_fast(float X);
void readHalfFromCircleBuffer32(float32_t *source, float32_t *dest, uint16_t index, uint16_t length);

#endif