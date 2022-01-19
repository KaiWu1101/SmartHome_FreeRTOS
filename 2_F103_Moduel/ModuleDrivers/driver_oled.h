#ifndef _DRIVER_OLED_H_
#define _DRIVER_OLED_H_

#include "stm32f1xx_hal.h"

#define OLED_WRITE_ADDR (0x78) //0b' 0 1 1 1_1 0 0 0
#define OLED_READ_ADDR  (0x79) //0b' 0 1 1 1_1 0 0 1


typedef enum{
	H_RIGHT = 0,
	H_LEFT  = 1
}H_SCROLL_DIR;

typedef enum{
	HV_RIGHT = 0,
	HV_LEFT  = 1
}HV_SCROLL_DIR;

typedef enum {
	H_ADDR_MODE     = 0x0,
	V_ADDR_MODE     = 0x1,
	PAGE_ADDR_MODE  = 0x2
}MEM_MODE;

void OLED_WriteCmd(uint8_t Cmd);
void OLED_WriteData(uint8_t data);

/* 1. 基础命令功能函数 */
extern void OLED_SetContrastValue(uint8_t value);

/* 2. 滚动命令功能函数*/
extern void OLED_V_Scroll(HV_SCROLL_DIR dir, uint8_t start, uint8_t fr_time, uint8_t end, uint8_t offset);
extern void OLED_V_Scroll(HV_SCROLL_DIR dir, uint8_t start, uint8_t fr_time, uint8_t end, uint8_t offset);

/* 3. 地址设置功能函数 */
extern void OLED_SetPageAddr_PAGE(uint8_t page);
extern void OLED_SetColAddr_PAGE(uint8_t col);
extern void OLED_SetPosition(uint8_t page, uint8_t col);
extern void OLED_SetMemAddrMode(MEM_MODE mode);
extern void OLED_SetColAddr_HV(uint8_t start, uint8_t end);
extern void OLED_SetPageAddr_HV(uint8_t start, uint8_t end);

/* 4. 设置硬件功能函数 */
extern void OLED_SetDispStartLine(uint8_t line);
extern void OLED_SetMuxRatio(uint8_t ratio);

#define OLED_SEG_REMAP()       OLED_WriteCmd(0xA1)
#define OLED_SEG_NOREMAP()     OLED_WriteCmd(0xA0)
#define OLED_SCAN_NORMAL()     OLED_WriteCmd(0xC0)
#define OLED_SCAN_REMAP()      OLED_WriteCmd(0xC8)

typedef enum {
	COM_PIN_SEQ = 0,
	COM_PIN_ALT = 1
} COM_PINS_MODE;

typedef enum {
	COM_NOREMAP = 0,
	COM_REMAP   = 1
} COM_REMAP_STATE;
extern void OLED_SetDispOffset(uint8_t offset);
extern void OLED_SetComConfig(COM_PINS_MODE mode, COM_REMAP_STATE state);
	

/* 5.时间设置功能函数 */
typedef enum 
{
	LEVEL_0 = 0,
	LEVEL_1 = 1,
	LEVEL_2 = 2
} VCOMH_LEVEL;

extern void OLED_SetDCLK_Freq(uint8_t div, uint8_t freq);
extern void OLED_SetPreChargePeriod(uint8_t phase1, uint8_t phase2);
extern void OLED_SetVcomLevel(VCOMH_LEVEL level);


/* 6.电荷碰撞功能函数 */
typedef enum
{
	PUMP_DISABLE = 0,
	PUMP_ENABLE  = 1
}CHARGE_PUMP_STATE;
extern void OLED_SetChargePump(CHARGE_PUMP_STATE state);

/*control block*/
extern void OLED_SetContrastValue(uint8_t value);
#define ENTIRE_DISP_ON()  OLED_WriteCmd(0xA5)
#define ENTIRE_DISP_OFF() OLED_WriteCmd(0xA4)
#define DISP_NORMAL()     OLED_WriteCmd(0xA6)
#define DISP_INVERSE()    OLED_WriteCmd(0xA7)
#define DISP_ON()         OLED_WriteCmd(0xAF)
#define DISP_OFF()        OLED_WriteCmd(0xAE)
#define SCROLL_ON()       OLED_WriteCmd(0x2F)
#define SCROLL_OFF()      OLED_WriteCmd(0x2E)


#endif /*__DRIVER_OLED_H_ */
