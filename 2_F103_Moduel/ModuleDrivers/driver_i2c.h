#ifndef _DRIVER_I2C_H_
#define _DRIVER_I2C_H_

#include "main.h"
#include "stm32f1xx_hal.h"

#define SCL_L HAL_GPIO_WritePin(GPIOF, SCL_Pin, 0)
#define SCL_H HAL_GPIO_WritePin(GPIOF, SCL_Pin, 1)
#define SDA_L HAL_GPIO_WritePin(GPIOF, SDA_Pin, 0)
#define SDA_H HAL_GPIO_WritePin(GPIOF, SDA_Pin, 1)

#define SDA_IN (HAL_GPIO_ReadPin(GPIOF, SDA_Pin))

void I2C_PortInit();
void I2C_WriteByte(uint8_t data);
uint8_t I2C_ReadByte(uint8_t ack);
void I2C_Start(void);
int I2C_GetAck(void);
void I2C_Stop();

#endif