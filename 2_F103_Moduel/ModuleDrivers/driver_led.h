#ifndef _DRIVER_LED_H_
#define _DRIVER_LED_H_

#define BLUE_ON  (HAL_GPIO_WritePin(GPIOF, BLUE_Pin, 0))
#define BLUE_OFF (HAL_GPIO_WritePin(GPIOF, BLUE_Pin, 1))

extern  void BlueOn(void);
extern  void BlueOff(void);
extern  void BlueShine(void);
extern  void BlueShine2(void);
extern void HorseRunLed(void);
extern void WaterLed();
extern void GreenOn(void);
extern void GreenOff(void);
extern void WhiteOn(void);
extern void WhiteOff(void);

#endif