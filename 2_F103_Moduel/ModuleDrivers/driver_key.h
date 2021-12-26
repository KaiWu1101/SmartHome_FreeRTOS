#ifndef _DRIVER_KEY_H_
#define _DRIVER_KEY_H_
#include "main.h"
#include "stm32f1xx_hal.h"
#define K1 (HAL_GPIO_ReadPin(GPIOE, K1_Pin))
#define K2 (HAL_GPIO_ReadPin(GPIOE, K2_Pin))

extern uint8_t K1_Value(void);
extern uint8_t K2_Value(void);

#endif
