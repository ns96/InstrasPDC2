/**
  ******************************************************************************
  * @file    pot.c 
  * @author  Vaidas Zakarka
  * @version V1.0.0
  * @date    02-February-2013
  * @brief   Potentiometer driver
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 ElectronicsWorkshop.eu</center></h2>
  ******************************************************************************
  */ 
	/* Includes ------------------------------------------------------------------*/
	#include "stm8s.h"
	/* Public functions ---------------------------------------------------------*/		
	
	/**
  * @brief  Initializes the ADC. 
	* ADC conversion mode: continious, EOC interrupt enabled
  * @retval : None
  */
	void pot_init(void){
		 /*  Init GPIO for ADC7 */
		GPIO_Init(GPIOB, GPIO_PIN_7, GPIO_MODE_IN_FL_NO_IT);
		
		GPIO_Init(GPIOB, GPIO_PIN_2, GPIO_MODE_IN_FL_NO_IT);
		
		/* De-Init ADC peripheral*/
		ADC1_DeInit();
	
		/* Init ADC1 peripheral */
		/*ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, ADC1_CHANNEL_7, ADC1_PRESSEL_FCPU_D18, \
							ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL7,\
							DISABLE);	*/
/* Init ADC1 peripheral */
		ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, ADC1_CHANNEL_2, ADC1_PRESSEL_FCPU_D18, \
							ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL2,\
							DISABLE);								
	
		/* Enable EOC interrupt */
		ADC1_ITConfig(ADC1_IT_EOCIE,ENABLE);
	
		/* Enable general interrupts */  
		enableInterrupts();
		
		/*Start Conversion */
		ADC1_StartConversion();
		
	}
	/**
  * @brief  Deinitializes the ADC. 
  * @retval : None
  */
	void pot_DeInit(void){
	
		/* De-Init ADC peripheral*/
		ADC1_DeInit();						
	
		/* Enable EOC interrupt */
		ADC1_ITConfig(ADC1_IT_EOCIE,DISABLE);
		
	}