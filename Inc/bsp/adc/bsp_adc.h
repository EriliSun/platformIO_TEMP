#ifndef __ADC_H__
#define	__ADC_H__

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_it.h"

/* ���Ͷ��� ------------------------------------------------------------------*/
/* �궨�� --------------------------------------------------------------------*/
// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC����ͨ�������ţ�����**************************/
#define ADCx_RCC_CLK_ENABLE()            __HAL_RCC_ADC1_CLK_ENABLE()
#define ADCx_RCC_CLK_DISABLE()           __HAL_RCC_ADC1_CLK_DISABLE()
#define ADCx                             ADC1

//#define ADCx_RCC_CLK_ENABLE()            __HAL_RCC_ADC2_CLK_ENABLE()
//#define ADCx_RCC_CLK_DISABLE()           __HAL_RCC_ADC2_CLK_DISABLE()
//#define ADCx                             ADC2

// #define ADCx_RCC_CLK_ENABLE()            __HAL_RCC_ADC3_CLK_ENABLE()
// #define ADCx_RCC_CLK_DISABLE()           __HAL_RCC_ADC3_CLK_DISABLE()
// #define ADCx                             ADC3


#define ADC_GPIO_ClK_ENABLE()            __HAL_RCC_GPIOA_CLK_ENABLE()
#define ADC_GPIO                         GPIOA
#define ADC_GPIO_PIN                     GPIO_PIN_1       
#define ADC_CHANNEL                      ADC_CHANNEL_1  
                                 
/* ��չ���� ------------------------------------------------------------------*/
extern ADC_HandleTypeDef hadcx;

/* �������� ------------------------------------------------------------------*/
void MX_ADCx_Init(void);

#endif /* __ADC_H__ */

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
