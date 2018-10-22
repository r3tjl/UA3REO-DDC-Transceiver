#ifndef SETTINGS_h
#define SETTINGS_h

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "arm_math.h"

#define W25Q16_COMMAND_Write_Enable 0x06
#define W25Q16_COMMAND_Erase_Chip 0xC7
#define W25Q16_COMMAND_Sector_Erase 0x20
#define W25Q16_COMMAND_Page_Program 0x02
#define W25Q16_COMMAND_Read_Data 0x03

extern struct TRX_SETTINGS {
  uint8_t clean_flash; 
	uint32_t Freq;
	uint8_t Mode;
	bool Preamp;
	bool Agc;
	bool Loopback;
	uint8_t Gain_level;
	uint8_t Agc_speed;
	bool Tune;
	uint8_t LCD_menu_freq_index;
} TRX; 

extern SPI_HandleTypeDef hspi1;
extern void LoadSettings(void);
extern void SaveSettings(void);
void Flash_Sector_Erase(void);
void Flash_Erase_Chip(void);
void Flash_Write_Data(void);
void Flash_Read_Data(void);
	
#endif