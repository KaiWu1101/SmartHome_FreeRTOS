#include "drivers_led.h"
#include "stm32f10x_lib.h"
#include "stm32f10x_gpio.h"



																			
																			
void DriversGPIOInit_GPIO_F(void) {
	    GPIO_InitTypeDef GPIO_InitStruct = {0};
	  __HAL_RCC_GPIOF_CLK_ENABLE();

		
    /*Configure GPIO pin Output Level */
		GPIO_WriteBit(GPIOF, BLUE_Pin|WHITE_Pin|GREEN_Pin, Bit_SET);

    /*Configure GPIO pins : PFPin PFPin PFPin PFPin
                            PFPin */
    GPIO_InitStruct.GPIO_Pin = WHITE_Pin|BLUE_Pin|GREEN_Pin;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &GPIO_InitStruct);
}

void LED_ON(uint32_t LED){
    if (LED == BLUE_LED) {
        GPIO_WriteBit(GPIOF, BLUE_Pin, Bit_RESET);
    } else if (LED == WHITE_LED) {
        GPIO_WriteBit(GPIOF, WHITE_Pin, Bit_RESET);
		} else {
        GPIO_WriteBit(GPIOF, GREEN_Pin, Bit_RESET);
		}
}

void LED_OFF(uint32_t LED){
    if (LED == BLUE_LED) {
        GPIO_WriteBit(GPIOF, BLUE_Pin, Bit_SET);
    } else if (LED == WHITE_LED) {
        GPIO_WriteBit(GPIOF, WHITE_Pin, Bit_SET);
    } else {
        GPIO_WriteBit(GPIOF, GREEN_Pin, Bit_SET);
    }
}
