#include "driver_led.h"
//led pin definition is insided main.h
#include "main.h"

void BlueOn(void)
{
    HAL_GPIO_WritePin(GPIOF, BLUE_Pin, 0);
}

void BlueOff(void)
{
    HAL_GPIO_WritePin(GPIOF, BLUE_Pin, 1);
}

void GreenOn(void)
{
    HAL_GPIO_WritePin(GPIOF, GREEN_Pin, 0);
}

void GreenOff(void)
{
    HAL_GPIO_WritePin(GPIOF, GREEN_Pin, 1);
}

void WhiteOn(void)
{
    HAL_GPIO_WritePin(GPIOF, WHITE_Pin, 0);
}

void WhiteOff(void)
{
    HAL_GPIO_WritePin(GPIOF, WHITE_Pin, 1);
}


void BlueShine(void)
{
	BlueOn();
	HAL_Delay(500);
  BlueOff();
	HAL_Delay(500);
}


void BlueShine2(void)
{
	HAL_GPIO_TogglePin(GPIOF, BLUE_Pin);
	HAL_Delay(200);
}

void WaterLed()
{
	GreenOn();
	HAL_Delay(500);
	BlueOn();
	HAL_Delay(500);
	WhiteOn();
	HAL_Delay(500);
	BlueOff();
	GreenOff();
	WhiteOff();
	HAL_Delay(500);
}


void HorseRunLed(void)
{
	BlueOn();
	HAL_Delay(500);
	BlueOff();
	WhiteOn();
	HAL_Delay(500);
	WhiteOff();
	GreenOn();
	HAL_Delay(500);
	GreenOff();
}
	