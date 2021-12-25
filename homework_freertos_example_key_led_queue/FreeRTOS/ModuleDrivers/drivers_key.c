
#include "drivers_key.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f10x_gpio.h"


void DriversGPIOInit_GPIO_E(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.GPIO_Pin = K1_Pin|K2_Pin;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
}

u8 K1_Value(void)
{
	if(K1 == 0)
	{
		vTaskDelay(100);
		if(K1 == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	} else
	{
		return 1;
	}

}

//	void GPIO_WriteBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin, BitAction BitVal);
