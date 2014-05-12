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
	#include "stm32f0xx_adc.h"
	/* Public functions ---------------------------------------------------------*/		
	
	/**
  * @brief  Initializes the ADC. 
	* ADC conversion mode: continious, EOC interrupt enabled
  * @retval : None
  */
	void pot_init(void){
		ADC_InitTypeDef     ADC_InitStructure;
		GPIO_InitTypeDef    GPIO_InitStructure;
		NVIC_InitTypeDef    NVIC_InitStructure;
		
		/* GPIOC Periph clock enable */
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
		
		/* ADC1 Periph clock enable */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //ch8 ch9
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		  /* ADCs DeInit */  
		ADC_DeInit(ADC1);
				
		  /* Initialize ADC structure */
		ADC_StructInit(&ADC_InitStructure);
		
		/* Configure the ADC1 in continuous mode with a resolution equal to 10 bits  */
		ADC_InitStructure.ADC_Resolution = ADC_Resolution_10b;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
		ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
		ADC_Init(ADC1, &ADC_InitStructure); 
		
		ADC_ChannelConfig(ADC1, ADC_Channel_4 , ADC_SampleTime_239_5Cycles);
		
		/* Enable ready interrupt */
		ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
		
		/* Configure and enable ADC1 interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = ADC1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
			/* ADC Calibration */
		ADC_GetCalibrationFactor(ADC1);
		
		 /* Enable the ADC peripheral */
		ADC_Cmd(ADC1, ENABLE);     
		
//		/* Wait the ADRDY flag */
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY)); 
//		
		/* ADC1 regular Software Start Conv */ 
		ADC_StartOfConversion(ADC1);
		
//		 /*  Init GPIO for ADC7 */
//		GPIO_Init(GPIOB, GPIO_PIN_7, GPIO_MODE_IN_FL_NO_IT);
//		
//		GPIO_Init(GPIOB, GPIO_PIN_2, GPIO_MODE_IN_FL_NO_IT);
//		
//		/* De-Init ADC peripheral*/
//		ADC1_DeInit();
//	
//		/* Init ADC1 peripheral */
//		/*ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, ADC1_CHANNEL_7, ADC1_PRESSEL_FCPU_D18, \
//							ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL7,\
//							DISABLE);	*/
///* Init ADC1 peripheral */
//		ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, ADC1_CHANNEL_2, ADC1_PRESSEL_FCPU_D18, \
//							ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL2,\
//							DISABLE);								
//	
//		/* Enable EOC interrupt */
//		ADC1_ITConfig(ADC1_IT_EOCIE,ENABLE);
//	
//		/* Enable general interrupts */  
//		enableInterrupts();
//		
//		/*Start Conversion */
//		ADC1_StartConversion();
		
	}
	/**
  * @brief  Deinitializes the ADC. 
  * @retval : None
  */
	void pot_DeInit(void){
//	
		/* De-Init ADC peripheral*/
		ADC_DeInit(ADC1);				
	
		/* Disable EOC interrupt */
		ADC_ITConfig(ADC1, ADC_IT_EOC, DISABLE);
		
	}