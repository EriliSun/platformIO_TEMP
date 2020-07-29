/**
  ******************************************************************************
  * �ļ�����: bsp_usartx.c 
  * ��    ��: 
  * ��    ��: V1.0
  * ��д����: 2017-03-30
  * ��    ��: ���ش��ڵײ���������
  ******************************************************************************
  * ˵����

  ******************************************************************************
  */

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "usart/bsp_RS485.h"


/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
UART_HandleTypeDef huartx_RS485;

/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
/* ������ --------------------------------------------------------------------*/

/**
  * ��������: ����Ӳ����ʼ������
  * �������: huart�����ھ������ָ��
  * �� �� ֵ: ��
  * ˵    ��: �ú�����HAL���ڲ�����
  */
void HAL_RS485_UART_MspInit(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

	/* ʹ�ܴ��ڹ�������GPIOʱ�� */
	MX_RS485_UARTx_Rx_GPIO_ClK_ENABLE();
	MX_RS485_UARTx_Tx_GPIO_ClK_ENABLE();
	USARTx_CTRL_GPIO_ClK_ENABLE();
	/* �������蹦��GPIO���� */
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
  * ��������: ���ڲ�������.
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void MX_RS485_USARTx_Init(void)
{
	HAL_RS485_UART_MspInit();
  /* ��������ʱ��ʹ�� */
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
