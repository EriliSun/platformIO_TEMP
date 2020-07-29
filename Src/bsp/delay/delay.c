
/* Private includes ----------------------------------------------------------*/
#include "delay/delay.h"


/* USER CODE BEGIN Includes */

/* USER CODE END Includes */


/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */


/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
static uint32_t fac_us = 0; 
//static uint16_t fac_ms = 0;  
/* USER CODE END PV */


/* USER CODE BEGIN 0 */
void delay_init(void)
{
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	fac_us = HAL_RCC_GetHCLKFreq()/1000000;
	// fac_us = SystemCoreClock/8000000;
	// fac_ms=(uint16_t)fac_us*1000;
}
/* USER CODE END 0 */


/* USER CODE BEGIN 1 */
void delay_ms(uint16_t nms)
{
	uint32_t i;
	for(i=0;i<nms;i++) delay_us(1000);
// 	uint32_t temp;		   
// 	SysTick->LOAD=(uint32_t)nms*fac_ms;				//ʱ�����(SysTick->LOADΪ24bit)
// 	SysTick->VAL =0x00;							//��ռ�����
// 	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
// 	do
// 	{
// 		temp=SysTick->CTRL;
// 	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
// 	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
// 	SysTick->VAL =0X00;       					//��ռ�����
 }
/* USER CODE END 1 */


/* USER CODE BEGIN 2 */
void delay_us(uint32_t nus)
{
	uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
	uint32_t reload=SysTick->LOAD;				//LOAD��ֵ	    	 
	ticks=nus*fac_us; 						//��Ҫ�Ľ����� 
	told=SysTick->VAL;        				//�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	};     					 //��ռ�����	 
}
/* USER CODE END 2 */
