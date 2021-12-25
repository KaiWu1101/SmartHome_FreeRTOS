#include "driver_key.h"
#include "main.h"

//HOW TO CONFIGURE GPIO:
// step 1: enable rcc clokc
// step 2: declare and configure gpio struct
// step 3: pass gpio struct to HAL_GPIO_Init function

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