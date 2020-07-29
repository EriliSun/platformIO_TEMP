/**
  ******************************************************************************
  * 文件名程: bsp_usartx.c 
  * 作    者: 
  * 版    本: V1.0
  * 编写日期: 2017-03-30
  * 功    能: 板载串口底层驱动程序
  ******************************************************************************
  * 说明：

  ******************************************************************************
  */

/* 包含头文件 ----------------------------------------------------------------*/
#include "usart/bsp_RS485.h"


/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
UART_HandleTypeDef huartx_RS485;

/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/

/**
  * 函数功能: 串口硬件初始化配置
  * 输入参数: huart：串口句柄类型指针
  * 返 回 值: 无
  * 说    明: 该函数被HAL库内部调用
  */
void HAL_RS485_UART_MspInit(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

	/* 使能串口功能引脚GPIO时钟 */
	MX_RS485_UARTx_Rx_GPIO_ClK_ENABLE();
	MX_RS485_UARTx_Tx_GPIO_ClK_ENABLE();
	USARTx_CTRL_GPIO_ClK_ENABLE();
	/* 串口外设功能GPIO配置 */
	GPIO_InitStruct.Pin = MX_RS485_UARTx_Tx_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = MX_RS485_UARTx_GPIO_AFx;
	HAL_GPIO_Init(MX_RS485_UARTx_Tx_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = MX_RS485_UARTx_Rx_GPIO_PIN;
	HAL_GPIO_Init(MX_RS485_UARTx_Rx_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = USARTx_CTRL_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Alternate = 0;
	HAL_GPIO_Init(USARTx_CTRL_GPIO, &GPIO_InitStruct);		

	  /* USART1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(MX_RS485_UARTx_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(MX_RS485_UARTx_IRQn);
}

/**
  * 函数功能: 串口参数配置.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void MX_RS485_USARTx_Init(void)
{
	HAL_RS485_UART_MspInit();
  /* 串口外设时钟使能 */
  MX_RS485_UART_RCC_CLK_ENABLE();
  
  huartx_RS485.Instance = MX_RS485_UARTx;
  huartx_RS485.Init.BaudRate = MX_RS485_UARTx_BAUDRATE;
  huartx_RS485.Init.WordLength = UART_WORDLENGTH_8B;
  huartx_RS485.Init.StopBits = UART_STOPBITS_1;
  huartx_RS485.Init.Parity = UART_PARITY_NONE;
  huartx_RS485.Init.Mode = UART_MODE_TX_RX;
  huartx_RS485.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huartx_RS485.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huartx_RS485);

}

/******************* (C) COPYRIGHT 2015-2020 Erili *****END OF FILE****/
