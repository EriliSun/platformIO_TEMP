/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "led/bsp_led.h"
#include "delay/delay.h"
#include "stm32f4xx_hal_adc.h"
#include "adc/bsp_adc.h"
#include "usart/bsp_debug_usart.h"
#include "stm32f4xx_it.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint32_t sys_clk_monitor1 = 0;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
float ADC_ConvertedValueLocal;
// AD转换结果值
__IO uint16_t ADC_ConvertedValue;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  uint8_t count = 0;
  float TEMP = 0;
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
  delay_init();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  LED_GPIO_Init();
  /* USER CODE BEGIN 2 */
  MX_DEBUG_USART_Init();
  MX_ADCx_Init();
  /* USER CODE END 2 */
  HAL_ADC_Start_IT(&hadcx);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
         switch(count)
    {
      /* č°ç¨LEDçŻć§ĺśĺ˝ć°ćšćłć§ĺśLEDç? */
      case 0:
        sys_clk_monitor1=HAL_RCC_GetHCLKFreq();           
        LEDx_StateSet(LED1 | LED2 | LED3,LED_OFF);
        
        break;
      case 1:           
        LEDx_StateSet(LED1,LED_ON);
        break;
      case 2:
        LEDx_StateSet(LED1,LED_OFF);
        LEDx_StateSet(LED2,LED_ON);
        break;
       /* ä˝żç¨ĺŽĺŽäšćšćłć§ĺśLEDç? */
      case 3:                       
        LED2_OFF;
        LED3_ON;
        break;
      case 4:
        LED3_OFF;
        LED2_ON;
        break;
      case 5:
        LED2_OFF;
        LED1_ON; 
        break;
      case 6:
        LED1_ON;
        LED2_ON;
        LED3_ON;
        break;
    }    
    /* ĺťśćśä¸?ćŽľćśé? */
    //HAL_Delay(1000);
    delay_ms(1000);
    
    /* čŽĄć°ĺ˘ĺ 1 */
    count++;
    /* éć°ĺź?ĺ§čŽĄć? */
    if(count==7)count=0;
     /* 3.3为AD转换的参考电压值，stm32的AD转换为12bit，2^12=4096，
       即当输入为3.3V时，AD转换结果为4096 */
    ADC_ConvertedValueLocal =(double)ADC_ConvertedValue*3.3/4096; 	
    TEMP = (ADC_ConvertedValueLocal*1000-424)/6.25;
		printf("AD转换原始值 = 0x%04x \r\n", ADC_ConvertedValue); 
		printf("计算得出电压值 = %.3fV\r\n",ADC_ConvertedValueLocal); 
    printf("计算得出温度值 = %.3f℃\r\n",TEMP); 
  }
  /* USER CODE END 3 */
}

/**
  * 函数功能: AD转换结束回调函数
  * 输入参数: hadc：AD设备类型句柄
  * 返 回 值: 无
  * 说    明: 无
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  ADC_ConvertedValue=HAL_ADC_GetValue(&hadcx);
}  

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
