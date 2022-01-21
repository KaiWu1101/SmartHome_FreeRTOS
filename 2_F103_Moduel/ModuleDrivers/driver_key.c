#include "driver_key.h"
#include "main.h"

//HOW TO CONFIGURE GPIO:
// step 1: enable rcc clokc
// step 2: declare and configure gpio struct
// step 3: pass gpio struct to HAL_GPIO_Init function


static volatile uint8_t key1_val = KEY_RELEASED;
static volatile uint8_t key2_val = KEY_RELEASED;

//remove dithering within function below
uint8_t K1_Value(void)
{
	if(K1 == 0)
	{
		HAL_Delay(100);
	  if(K1 == 0)
		{
			return 0;
		}
	} else {
		return 1;
	}
}

uint8_t K2_Value(void)
{
	if(K2 == 0)
	{
		HAL_Delay(100);
	  if(K2 == 0)
		{
			return 0;
		}
	} else {
		return 1;
	}
}

void KEY_GPIO_ReInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	KEY1_GPIO_CLK_EN();
	KEY2_GPIO_CLK_EN();
	GPIO_InitStruct.Pin = (KEY1_PIN | KEY2_PIN);
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	
	HAL_GPIO_Init(KEY1_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 2);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(KEY1_PIN);
	HAL_GPIO_EXTI_IRQHandler(KEY2_PIN);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(KEY1_PIN == GPIO_Pin) {
	    key1_val = K1;
	} else if(KEY2_PIN == GPIO_Pin) {
		  key2_val = K2;
	}
}

uint8_t KEY1_Value(void)
{
	return key1_val;
}

uint8_t KEY2_Value(void)
{
	return key2_val;
}
