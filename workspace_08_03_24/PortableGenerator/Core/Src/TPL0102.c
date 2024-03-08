#include "tpl0102.h"

void TPL0102_Init(I2C_HandleTypeDef *hi2c) {
    // Set digipot to 50k ohm value at the start ==> offset 0V
    TPL0102_Write(hi2c, CHANNEL_0, 128);
    TPL0102_Write(hi2c, CHANNEL_1, 128);
}

void TPL0102_Write(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t value) {
    uint8_t data[2] = {channel, value};
    HAL_I2C_Master_Transmit(hi2c, (uint16_t)(TPL0102_ADDR<<1), data, 2, HAL_MAX_DELAY);
}

void TPL0102_Read(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t *value) {
    HAL_I2C_Master_Transmit(hi2c, (uint16_t)(TPL0102_ADDR<<1), &channel, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(hi2c, (uint16_t)(TPL0102_ADDR<<1), value, 1, HAL_MAX_DELAY);
}
