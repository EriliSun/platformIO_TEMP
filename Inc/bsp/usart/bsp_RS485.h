#ifndef __BSP_USARTX_H__
#define __BSP_USARTX_H__

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"

/* ���Ͷ��� ------------------------------------------------------------------*/
/* �궨�� --------------------------------------------------------------------*/

#define MX_RS485_UARTx                              USART3
#define MX_RS485_UARTx_BAUDRATE                     115200
#define MX_RS485_UART_RCC_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE()
#define MX_RS485_UARTx_GPIO_AFx                     GPIO_AF7_USART3

#define MX_RS485_UARTx_Tx_GPIO_ClK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define MX_RS485_UARTx_Tx_GPIO_PIN                  GPIO_PIN_10
#define MX_RS485_UARTx_Tx_GPIO                      GPIOB

#define MX_RS485_UARTx_Rx_GPIO_ClK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define MX_RS485_UARTx_Rx_GPIO_PIN                  GPIO_PIN_11
#define MX_RS485_UARTx_Rx_GPIO                      GPIOB

#define MX_RS485_UARTx_IRQn                         USART3_IRQn
#define MX_RS485_UARTx_IRQHandler                   USART3_IRQHandler



#define USARTx_CTRL_GPIO_ClK_ENABLE()          __HAL_RCC_GPIOH_CLK_ENABLE()
#define USARTx_CTRL_PIN                        GPIO_PIN_8
#define USARTx_CTRL_GPIO                       GPIOH

#define RX_MODE()                              HAL_GPIO_WritePin(USARTx_CTRL_GPIO,USARTx_CTRL_PIN,GPIO_PIN_RESET)
#define TX_MODE()                              HAL_GPIO_WritePin(USARTx_CTRL_GPIO,USARTx_CTRL_PIN,GPIO_PIN_SET)


/* ��չ���� ------------------------------------------------------------------*/
extern UART_HandleTypeDef huartx_RS485;

/* �������� ------------------------------------------------------------------*/
void MX_RS485_USARTx_Init(void);


#endif  /* __BSP_USARTX_H__ */

/******************* (C) COPYRIGHT 2015-2020 Erili *****END OF FILE****/
