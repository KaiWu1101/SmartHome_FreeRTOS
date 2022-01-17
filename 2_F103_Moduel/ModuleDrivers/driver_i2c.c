#include "driver_i2c.h"

void I2C_Delay(uint32_t t)
{
	volatile uint32_t tmp = t; //prevent t from being optimized by compiler.
	while(tmp--);
}


void I2C_PortInit()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
	
	HAL_GPIO_DeInit(GPIOF, GPIO_PIN_10|GPIO_PIN_11); //scl and sda pin

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}


void I2C_Start(void)
{
	SCL_H;
	SDA_H;
	I2C_Delay(100);
	SDA_L;
	I2C_Delay(100); //keep sda low for a while
}

void I2C_Stop()
{
	SCL_H;
	SDA_L;
	I2C_Delay(100);
	SDA_H;
	I2C_Delay(100); //keep sda high for a while
}

int I2C_GetAck(void)
{
	int i = 0;
	SCL_L; //pull down SCL first, to make sure SDA_h NOT be received by slave as '1'
	SDA_H;
	//I2C_Delay(100);
	SCL_H;
	//wait ack in a limited time, add i here to 
	//prevent dead loop
	while(SDA_IN != 0)
	{
		i++;
		if(i >= 1000)
		{
			SCL_L;
			return -1;
		}
	}
	SCL_L;
	return 0;
}

void I2C_ACK()
{
	//once SCL_L happens, SDA's change will not be received by slave
	SCL_L;
	SDA_L;
	I2C_Delay(100);
	SCL_H;
	I2C_Delay(100);
	SCL_L;
}

void I2C_NACK()
{
	//once SCL_L happens, SDA's change will not be received by slave
	SCL_L;
	SDA_H;
	I2C_Delay(100);
	SCL_H;
	I2C_Delay(100);
	SCL_L;
}

void I2C_WriteByte(uint8_t data)
{
    uint8_t i = 0;
    for(i=0; i<8; i++)
    {
        SCL_L;
        I2C_Delay(100);
        if(data & 0x80)
        {
            SDA_H;
        }
        else
        {
            SDA_L;
        }
        data <<= 1; // 发出1bit数据后，要更新数据，将data的次高位移位到最高位
        SCL_H;
        I2C_Delay(100);
    }
    I2C_GetAck();
}

uint8_t I2C_ReadByte(uint8_t ack)
{
	uint8_t i=0;
	uint8_t data=0;
	SDA_H; //release sda control to slave
	while(i<8)
	{
		//SCL is still controlled by master, not slave
		SCL_L; 
		I2C_Delay(100);
		SCL_H;
		I2C_Delay(100);
		if(SDA_IN)
		{
			data ++;
		} else {
			data = data;
		}
		data <<= 1;
	}
	if(!ack)
	{
	  I2C_ACK();
	} else {
		I2C_NACK();
	}
	return data;
}
