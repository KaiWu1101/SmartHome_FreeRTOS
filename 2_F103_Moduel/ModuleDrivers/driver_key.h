#ifndef _DRIVER_KEY_H_
#define _DRIVER_KEY_H_
#include "main.h"
#include "stm32f1xx_hal.h"

#define KEY_PRESSED  (0)
#define KEY_RELEASED (1)

#define KEY1_PIN GPIO_PIN_14
#define KEY2_PIN GPIO_PIN_15

#define KEY1_PORT GPIOE
#define KEY2_PORT_GPIOE

#define KEY1_GPIO_CLK_EN() __HAL_RCC_GPIOE_CLK_ENABLE()
#define KEY2_GPIO_CLK_EN() __HAL_RCC_GPIOE_CLK_ENABLE()

#define K1 (HAL_GPIO_ReadPin(GPIOE, K1_Pin))
#define K2 (HAL_GPIO_ReadPin(GPIOE, K2_Pin))

extern uint8_t K1_Value(void);
extern uint8_t K2_Value(void);

extern void KEY_GPIO_ReInit(void);
extern uint8_t KEY1_Value(void);
extern uint8_t KEY2_Value(void);

#endif
