#ifndef _DRIVERS_LED_H_
#define _DRIVERS_LED_H_

#include <stdint.h>
#include "stm32f10x_lib.h"
#include "stm32f10x_gpio.h"

#define WHITE_Pin GPIO_Pin_7
#define BLUE_Pin  GPIO_Pin_8
#define GREEN_Pin GPIO_Pin_9

#define BLUE_LED  0
#define WHITE_LED 1
#define GREEN_LED 2

void DriversGPIOInit_GPIO_F(void);
void LED_ON(uint32_t LED);
void LED_OFF(uint32_t LED);
void DriversGPIOInit_GPIO_F(void);

#define     __IO    volatile             /*!< Defines 'read / write' permissions */

#define RCC_APB2ENR_IOPFEN_Pos               (7U)                              
#define RCC_APB2ENR_IOPFEN_Msk               (0x1UL << RCC_APB2ENR_IOPFEN_Pos)  /*!< 0x00000080 */
#define RCC_APB2ENR_IOPFEN                   RCC_APB2ENR_IOPFEN_Msk            /*!< I/O port F clock enable */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */
#define __HAL_RCC_GPIOF_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPFEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPFEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)


#endif
