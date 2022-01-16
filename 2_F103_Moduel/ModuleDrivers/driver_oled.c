#include "driver_oled.h"
#include "driver_i2c.h"

/*
 * When writing byte to OLED, control byte != data byte 
 *                            control byte != cmd byte
 */
 
 
 /*
  * HOW OLED display pixels:
  *     The screen is divided into 8 pages(x rows = 1 page), 128 columns
	*/

//actually we can send cmd only, no data followed!
void OLED_WriteCmd(uint8_t Cmd)
{
	I2C_Start();
	I2C_WriteByte(OLED_WRITE_ADDR);
	I2C_GetAck();
	I2C_WriteByte(0x0); //Control Byte: CO = 0 D/C# = 0 (cmd)
	I2C_WriteByte(Cmd);
	I2C_Stop();
}

void OLED_WriteData(uint8_t data)
{
	I2C_Start();
	I2C_WriteByte(OLED_WRITE_ADDR);
	I2C_GetAck();
	I2C_WriteByte(0x40); //CO = 0 D/C# = 0 (cmd)
	I2C_WriteByte(data);
	I2C_Stop();
}

void OLED_WriteNBytes(uint8_t data[], uint16_t len)
{
	if(data == NULL) return; //void function can still return.
	I2C_Start();
	I2C_WriteByte(OLED_WRITE_ADDR);
	I2C_GetAck();
	I2C_WriteByte(0x40); //CO = 0 D/C# = 0 (cmd)
	for(int i = 0; i < len; i++)
	{
		I2C_WriteByte(data[i]);
	}
	I2C_Stop();
}

/* 1. 基础命令功能函数 */
void OLED_SetContrastValue(uint8_t value)
{
	OLED_WriteCmd(0x81);
	OLED_WriteCmd(value);
}


/* 2. 滚动命令功能函数*/
void OLED_H_Scroll(H_SCROLL_DIR dir, uint8_t start, uint8_t fr_time, uint8_t end)
{
	if((dir != H_RIGHT) && (dir  != H_LEFT)) return;
	if((start > 0x7) | (fr_time > 0x07) | (end > 0x7)) return;
	OLED_WriteCmd(dir);
	OLED_WriteCmd(0x0);     //dummy bytes
	OLED_WriteCmd(start);
	OLED_WriteCmd(fr_time); 
	OLED_WriteCmd(end);
	OLED_WriteCmd(0x0);     //dummy bytes
	OLED_WriteCmd(0xFF);     //dummy bytes
}

void OLED_V_Scroll(HV_SCROLL_DIR dir, uint8_t start, uint8_t fr_time, uint8_t end, uint8_t offset)
{
	if((dir != HV_RIGHT) && (dir  != HV_LEFT)) return;
	if((start > 0x7) | (fr_time > 0x07) | (end > 0x7)) return;
	if(offset > 0x3f) return;
	OLED_WriteCmd(dir);
	OLED_WriteCmd(0x0);     //dummy bytes
	OLED_WriteCmd(start);
	OLED_WriteCmd(fr_time); 
	OLED_WriteCmd(end);
	OLED_WriteCmd(offset);
}

void OLED_SetVScrollArea(uint8_t area, uint8_t row_num)
{
	if((area > 0x3F) | (row_num > 0x7F)) return;
	OLED_WriteCmd(0xA3);
	OLED_WriteCmd(area);
	OLED_WriteCmd(row_num);
}

/* 3. 地址设置功能函数 */
static MEM_MODE mem_mode = PAGE_ADDR_MODE;
void OLED_SetPageAddr_PAGE(uint8_t page)
{
	if(mem_mode != PAGE_ADDR_MODE) return;
	if(page > 7) return;
	OLED_WriteCmd(0xB0 + page);
}

void OLED_SetColAddr_PAGE(uint8_t col)
{
	if(mem_mode != PAGE_ADDR_MODE) return;
	if(col > 0x7f) return;
	OLED_WriteCmd(0x00 + (col &0x0F)); //low   4 bits
	OLED_WriteCmd(0x10 + (col >> 4));   //hight 4 bits
}

void OLED_SetPosition(uint8_t page, uint8_t col)
{
	OLED_SetPageAddr_PAGE(page);
	OLED_SetColAddr_PAGE(col);
}

void OLED_SetMemAddrMode(MEM_MODE mode)
{
	if((mode != H_ADDR_MODE) && (mode != V_ADDR_MODE) && (mode != PAGE_ADDR_MODE)) return;
	OLED_WriteCmd(0x20);
	OLED_WriteCmd(mode);
}

void OLED_SetColAddr_HV(uint8_t start, uint8_t end)
{
	if(mem_mode == PAGE_ADDR_MODE) return;
	if((start > 127) | (end > 127)) return;
	OLED_WriteCmd(0x21);
	OLED_WriteCmd(start);
	OLED_WriteCmd(end);
}

void OLED_SetPageAddr_HV(uint8_t start, uint8_t end)
{
	if(mem_mode == PAGE_ADDR_MODE) return;
	if((start > 7) | (end > 7)) return;
	OLED_WriteCmd(0x22);
	OLED_WriteCmd(start);
	OLED_WriteCmd(end);
}

/* 4. 设置硬件功能函数 */
void OLED_SetDispStartLine(uint8_t line)
{
	if(line > 63) return;
	OLED_WriteCmd(0x40 + line);
}

void OLED_SetMuxRatio(uint8_t ratio)
{
	if((ratio < 15)| (ratio > 63)) return;
	OLED_WriteCmd(0xA8);
	OLED_WriteCmd(ratio);
}


void OLED_SetDispOffset(uint8_t offset)
{
	if(offset > 63) return;
	OLED_WriteCmd(0xD3);
	OLED_WriteCmd(offset);
}

void OLED_SetComConfig(COMP_PINS_MODE mode, COM_REMAP_STATE state)
{
	if((mode  != COM_PIN_SEQ) && (mode  != COM_PIN_ALT)) return;
	if((state != COM_NOREMAP) && (state != COM_REMAP))   return;
	OLED_WriteCmd(0xDA);
	OLED_WriteCmd(0x02 + (mode << 4) + (state << 5));
}
	
/* 5.时间设置功能函数 */
void OLED_SetDCLK_Freq(uint8_t div, uint8_t freq)
{
	if((div > 0xf) | (freq > 0xf)) return;
	OLED_WriteCmd(0xd5);
	OLED_WriteCmd(div + (freq << 4));
}

void OLED_SetPreChargePeriod(uint8_t phase1, uint8_t phase2)
{
	if((phase1 > 0xf) | (phase2 > 0xf)) return;
	OLED_WriteCmd(0xd9);
	OLED_WriteCmd(phase1 + (phase2 << 4));
}

void OLED_SetVcomLevel(VCOMH_LEVEL level)
{
	if((level != LEVEL_0) && (level != LEVEL_1) && (level != LEVEL_2))
	OLED_WriteCmd(0xDB);
	OLED_WriteCmd(level << 4);
}

/* 6.电荷碰撞功能函数 */
void OLED_SetChargePump(CHARGE_PUMP_STATE state)
{
	if((state != PUMP_DISABLE) && (state != PUMP_ENABLE)) return;
	OLED_WriteCmd(0x8D);
	OLED_WriteCmd((state << 2) + 0x10);
}

/* 7.初始化 */
