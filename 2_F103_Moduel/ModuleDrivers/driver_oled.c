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
	I2C_WriteByte(0x0); //CO = 0 D/C# = 0 (cmd)
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