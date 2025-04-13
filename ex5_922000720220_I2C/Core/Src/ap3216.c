#include "ap3216.h"
#include <stdint.h>

#define hi2c1 hi2c2

uint8_t AP3216_Init(void) {
  uint8_t ret_value = 0;
  AP3216_WriteOneByte(SYS_CONFIG_ADDR, SYS_SW_RESET);
  HAL_Delay(50);
  AP3216_WriteOneByte(SYS_CONFIG_ADDR, SYS_ALS_ACT);
  HAL_Delay(50);
  ret_value = AP3216_ReadOneByte(SYS_CONFIG_ADDR);

  return ret_value;
}

/*往i2c总线上写一个字节的数据*/
uint8_t AP3216_WriteOneByte(uint8_t reg, uint8_t data) {
  uint16_t write_data = reg | (data << 8);

  /*先发送高位*/
  if (HAL_I2C_Master_Transmit(&hi2c1, AP3216_ADDR | AP3216_W,
                              (uint8_t *)&write_data, 2, 300) != HAL_OK) {
    return 0;
  }
  while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
    ;
  return 0;
}

uint8_t AP3216_ReadOneByte(uint8_t reg) {
  uint8_t read_data = 0;
  if (HAL_I2C_Master_Transmit(&hi2c1, AP3216_ADDR | AP3216_W, (uint8_t *)&reg,
                              1, 300) != HAL_OK) {
    return 0;
  }
  while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
    ;
  if (HAL_I2C_Master_Receive(&hi2c1, AP3216_ADDR | AP3216_R,
                             (uint8_t *)&read_data, 1, 300) != HAL_OK) {
    return 0;
  }
  return read_data;
}

uint16_t AP3216_Read_ALS_Data() {
  uint8_t als_l = 0, als_h = 0;
  uint16_t data;
  als_l = AP3216_ReadOneByte(ALS_DATA_LOW);
  als_h = AP3216_ReadOneByte(ALS_DATA_HIGH);
  data = (als_h << 8) | (als_l);

  return data;
}

uint16_t AP3216_Read_IR_Data() {
  uint8_t als_l = 0, als_h = 0;
  uint16_t data;
  als_l = AP3216_ReadOneByte(PS_DATA_LOW);
  als_h = AP3216_ReadOneByte(PS_DATA_HIGH);
  if (als_l & 0x40)
    return 1;
  data = (((uint16_t)als_h & 0x3f) << 4) | ((als_l)&0xf);

  return data;
}
