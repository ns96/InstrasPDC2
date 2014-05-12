/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.3.1
  * @date    17-January-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "global.h"
#include "communication.h" 
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


void TIM3_IRQHandler(void)
{
	static uint16_t t_last=0;
  /* Clear TIM1 COM pending bit */
	TIM1_cnt++;
	if (((uint16_t)(TIM1_cnt-t_last))>=(50/RPM_PULSE_MEASUREMENT_FREQ)){
	//	rpm_timerInterruptHandler();
		t_last=TIM1_cnt;
	}
		EXGPIO_toggle(D2);
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}


/**
  * @brief  This function handles USART1 global interrupts requests.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void){
	 if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    unsigned char recdata;
    unsigned char temphead;

    recdata=USART_ReceiveData(USART1)&0xFF;
		usart_byte_received(recdata);
	//	USART_SendData(USART1,recdata);
    
		
		 /* Clear the USART1 Receive interrupt */
     USART_ClearITPendingBit(USART1, USART_IT_RXNE);
  }
}

/**
  * @brief  This function handles ADC1 global interrupts requests.
  * @param  None
  * @retval None
  */
void ADC1_IRQHandler(void)
{
  if(ADC_GetITStatus(ADC1, ADC_IT_EOC) != RESET)
  {
			#ifdef POT_INVERTED
				Conversion_Value = 1023-ADC_GetConversionValue(ADC1);
			#else
				Conversion_Value = ADC_GetConversionValue(ADC1);
			#endif
		EXGPIO_toggle(D1);
    /* Clear ADC1 ADRDY pending interrupt bit */
    ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
