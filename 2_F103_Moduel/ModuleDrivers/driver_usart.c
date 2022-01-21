#include "driver_usart.h"
#include "usart.h"
#include <stdio.h>

static volatile int txcplt_flag = 0;
static volatile int rxcplt_flag = 0;
void EnableDebugIRQ(void)
{
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);    // ����USART1�жϵ����ȼ�
    HAL_NVIC_EnableIRQ(USART1_IRQn);            // ʹ��USART1���ж�
    
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_TC | UART_IT_RXNE);   // ʹ��USRAT1�ķ��ͺͽ����ж�
}

void DisableDebugIRQ(void)
{

		__HAL_UART_DISABLE_IT(&huart1,UART_IT_TC | UART_IT_RXNE);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
}

int fputc(int ch, FILE *f)
{
    txcplt_flag = 0;
    HAL_UART_Transmit_IT(&huart1, (uint8_t*)&ch, 1);
    while(txcplt_flag==0);
}

int fgetc(FILE *f)
{
	char c = 0;
	rxcplt_flag = 0;
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&c, 1);
	while(rxcplt_flag == 0);
	return c;
}


void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart1);   // HAL���е�UARTͳһ�жϷ�������ͨ���β��ж���Ҫ����˭���ж�
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance ==USART1)
	{
		txcplt_flag = 1;
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance ==USART1)
	{
		rxcplt_flag = 1;
	}
}
