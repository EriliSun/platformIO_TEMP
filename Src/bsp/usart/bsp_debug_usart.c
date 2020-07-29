/**
  ******************************************************************************
  * 文件名程: main.c 
  * 作    者: Erili
  * 版    本: V1.0
  * 编写日期: 2017-03-30
  * 功    能: 板载调试串口底层驱动程序：默认使用USART1
  ******************************************************************************
  * 说明：

  ******************************************************************************
  */
/* 包含头文件 ----------------------------------------------------------------*/  
#include "usart/bsp_debug_usart.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
UART_HandleTypeDef husart_debug;

/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/

/**
  * 函数功能: 串口硬件初始化配置
  * 输入参数: huart：串口句柄类型指针
  * 返 回 值: 无
  * 说    明: 该函数被HAL库内部调用
  */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  if(huart->Instance==DEBUG_USARTx)
  {
    /* 串口外设时钟使能 */
    DEBUG_USART_RCC_CLK_ENABLE();
  
    /* 串口外设功能GPIO配置 */
    GPIO_InitStruct.Pin = DEBUG_USARTx_Tx_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = DEBUG_USARTx_AFx;
    HAL_GPIO_Init(DEBUG_USARTx_Tx_GPIO, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = DEBUG_USARTx_Rx_GPIO_PIN;  
    HAL_GPIO_Init(DEBUG_USARTx_Tx_GPIO, &GPIO_InitStruct);       
  }  
}

/**
  * 函数功能: 串口硬件反初始化配置
  * 输入参数: huart：串口句柄类型指针
  * 返 回 值: 无
  * 说    明: 该函数被HAL库内部调用
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{

  if(huart->Instance==DEBUG_USARTx)
  {
    /* 串口外设时钟禁用 */
    DEBUG_USART_RCC_CLK_DISABLE();
  
    /* 串口外设功能GPIO配置 */
    HAL_GPIO_DeInit(DEBUG_USARTx_Tx_GPIO, DEBUG_USARTx_Tx_GPIO_PIN);
    HAL_GPIO_DeInit(DEBUG_USARTx_Rx_GPIO, DEBUG_USARTx_Rx_GPIO_PIN);
    
    /* 串口中断禁用 */
    HAL_NVIC_DisableIRQ(DEBUG_USART_IRQn);
  }
}

/**
  * 函数功能: 串口参数配置.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void MX_DEBUG_USART_Init(void)
{
  /* 使能串口功能引脚GPIO时钟 */
  DEBUG_USARTx_GPIO_ClK_ENABLE();
  
  husart_debug.Instance = DEBUG_USARTx;
  husart_debug.Init.BaudRate = DEBUG_USARTx_BAUDRATE;
  husart_debug.Init.WordLength = UART_WORDLENGTH_8B;
  husart_debug.Init.StopBits = UART_STOPBITS_1;
  husart_debug.Init.Parity = UART_PARITY_NONE;
  husart_debug.Init.Mode = UART_MODE_TX_RX;
  husart_debug.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  husart_debug.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&husart_debug);
  
}

/**
  * 函数功能: 重定向c库函数printf到DEBUG_USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
// int fputc(int ch, FILE *f)
// {
//   HAL_UART_Transmit(&husart_debug, (uint8_t *)&ch, 1, 0xffff);
//   return ch;
// }
// int __io_putchar(int ch)
// {
//   HAL_UART_Transmit(&husart_debug,(uint8_t*)&ch,1,0xffff);
//   return ch;
// }
// int _write(int file,char *prt,int len)
// {
//   int DataIdx;
//   for (DataIdx = 0; DataIdx < len; DataIdx++)
//   {
//     __io_putchar(*prt++);

//   }
//   return len;
  
// }

int _write (int fd, char *pBuffer, int size) 
{ 
    for (int i = 0; i < size; i++) 
    { 
        while((USART1->SR&0X40)==0);//等待上一次串口数据发送完成 ?
        USART1->DR = (uint8_t) pBuffer[i]; //写DR,串口1将发送数据
    } 
  return size;
}

// int vprintf_(const char* format, va_list va);
// int printf(const char *str, ...) {
//      va_list va;
//      va_start(va, str);
//      int ret = vprintf_(str, va);
//      va_end(va);
//      return ret;
// }
// int _write(int fd, char *pBuffer, int size)
// {
//         HAL_UART_Transmit(&husart_debug, pBuffer, size, 0xff);
//         return size;
// }

// void vprint(const char *fmt, va_list argp)
// {
//     char string[200];
//     if(0 < vsprintf(string,fmt,argp)) // build string
//     {
//         HAL_UART_Transmit(&husart_debug, (uint8_t*)string, strlen(string), 0xffffff); // send message via UART
//     }
// }

// void my_printf(const char *fmt, ...) // custom printf() function
// {
//     va_list argp;
//     va_start(argp, fmt);
//     vprint(fmt, argp);
//     va_end(argp);
// }



/**
  * 函数功能: 重定向c库函数getchar,scanf到DEBUG_USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
int fgetc(FILE * f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&husart_debug,&ch, 1, 0xffff);
  return ch;
}

/******************* (C) COPYRIGHT 2015-2020 Erili *****END OF FILE****/
