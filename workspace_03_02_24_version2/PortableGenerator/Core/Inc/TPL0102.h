#ifndef TPL0102_H
#define TPL0102_H

#include "stm32l5xx_hal.h"

// Registers

#ifndef TPL0102_ADDR
#define TPL0102_ADDR 0x50
#endif


#define CHANNEL_0 0x00 // Channel 0 is used for the offset
#define CHANNEL_1 0x10 // Channel 1 is used for amplitude adjustment

void TPL0102_Init(I2C_HandleTypeDef *hi2c);
void TPL0102_Write(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t value);
void TPL0102_Read(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t *value);

#endif
