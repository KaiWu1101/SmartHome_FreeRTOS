#ifndef _DRIVERS_GPIO_H_
#define _DRIVERS_GPIO_H_

#include "stm32f10x_lib.h"
#include "stm32f10x_gpio.h"
#include <stdint.h>

#define K1_Pin GPIO_Pin_14    
#define K2_Pin GPIO_Pin_15


#define K1 GPIO_ReadInputDataBit(GPIOE, K1_Pin)
#define K2 GPIO_ReadInputDataBit(GPIOE, K2_Pin)

void DriversGPIOInit_GPIO_E(void);
u8 K1_Value(void);

#endif
