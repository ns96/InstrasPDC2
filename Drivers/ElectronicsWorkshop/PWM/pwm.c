/**
  ******************************************************************************
  * @file    pwm.c 
  * @author  Vaidas Zakarka
  * @version V1.0.0
  * @date    02-February-2013
  * @brief   PWM output driver
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 ElectronicsWorkshop.eu</center></h2>
  ******************************************************************************
  */ 
	/* Includes ------------------------------------------------------------------*/
	#include "global.h"
	#include "pwm.h"
			#define GPIO_HIGH(a,b) 		a->ODR|=b
		#define GPIO_LOW(a,b)		a->ODR&=~b
	/* Public functions ---------------------------------------------------------*/		

	/**
		* @brief  Configure PWM time period and enable the outputs
		* @param  None
		* @retval None
		*/
	void PWM_init(void) 
	{
		NVIC_InitTypeDef NVIC_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		/* GPIOB Clock enable */
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
		
		/* GPIOA Configuration: Channel 1, 2 and Channel 1N as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin = S1_PIN | S2_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
//		GPIO_HIGH(GPIOB,S1_PIN);
//		GPIO_HIGH(GPIOB,S2_PIN);
//		GPIO_LOW(GPIOB,S1_PIN);
//		GPIO_LOW(GPIOB,S2_PIN);
		/* set gpio alternate function*/
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_1);
		
		/* TIM3 clock enable */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
		
		/* Time Base configuration */
		TIM_TimeBaseStructure.TIM_Prescaler = 24;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseStructure.TIM_Period = 40000;//(SystemCoreClock / 50 ) - 1;//50hz
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		 
		 /* Channel 1, 2 Configuration in PWM mode */
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
		TIM_OCInitStructure.TIM_Pulse = 10000;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
		//TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	//	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

		TIM_OC1Init(TIM3, &TIM_OCInitStructure);

		TIM_OCInitStructure.TIM_Pulse = 5000;
		TIM_OC2Init(TIM3, &TIM_OCInitStructure);
		
		
		 TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
     TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
				
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);		
		/* TIM3 counter enable */
		TIM_Cmd(TIM3, ENABLE);
		
		/* Enable the TIM1 Trigger and commutation interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);


//		TIM1_DeInit();
//		//Timer step 0.5us, reload every 20ms
//		TIM1_TimeBaseInit(7, TIM1_COUNTERMODE_UP, 40000, 0);
//		/*TIM1_Pulse = CCR1_Val*/
//		TIM1_OC1Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_DISABLE, TIM1_OUTPUTNSTATE_ENABLE,
//								 0, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
//								 TIM1_OCNIDLESTATE_RESET); 
//	
//		/*TIM1_Pulse = CCR2_Val*/
//		S1_OCInit(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE, 0,
//								 TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET, 
//								 TIM1_OCNIDLESTATE_RESET);
//	
//		/*TIM1_Pulse = CCR3_Val*/
//		S2_OCInit(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE, 0,
//								 TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
//								 TIM1_OCNIDLESTATE_RESET); 				 
//								 
//		/* Enable Timer1 compare interrupt*/
//		TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
//		
//	
//		/* TIM1 counter enable */
//		TIM1_Cmd(ENABLE);
	}

	/**
		* @brief  Enable PWM outputs
		* @param  None
		* @retval None
		*/
	void PWM_outputEnable(){
		/* TIM1 Main Output Enable */
//		TIM1_CtrlPWMOutputs(ENABLE);
		/* TIM3 Main Output Enable */
		TIM_CtrlPWMOutputs(TIM3, ENABLE);
	}

	/**
		* @brief  Disable PWM outputs
		* @param  None
		* @retval None
		*/
	void PWM_outputDisable(void){
		/* TIM1 Main Output Disable */
//		TIM1_CtrlPWMOutputs(DISABLE);
		/* TIM3 Main Output Enable */
		TIM_CtrlPWMOutputs(TIM3, DISABLE);		
	}

	/**
		* @brief  Sets PWM duty for all channels
		* @param  None
		* @retval None
		*/
	void PWM_setAllChannelDuty(uint16_t duty){
//			TIM1_SetCompare1(duty);
//			S2_TimSetCompare(duty);
//			S1_TimSetCompare(duty);
		PWM_setCH1Duty(duty);
		PWM_setCH2Duty(duty);
	}
	
	/**
		* @brief  Sets PWM duty for CH1
		* @param  None
		* @retval None
		*/
	void PWM_setCH1Duty(uint16_t duty){
	//		TIM1_SetCompare1(duty);
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		 /* Channel 1, 2 Configuration in PWM mode */
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
		TIM_OCInitStructure.TIM_Pulse = duty;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;

		TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	}

	/**
		* @brief  Sets PWM duty for CH2
		* @param  None
		* @retval None
		*/
	void PWM_setCH2Duty(uint16_t duty){
	//	 TIM1_SetCompare2(duty); 
				TIM_OCInitTypeDef  TIM_OCInitStructure;
		 /* Channel 1, 2 Configuration in PWM mode */
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
		TIM_OCInitStructure.TIM_Pulse = duty;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;

		TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	}
	
	/**
		* @brief  Sets PWM duty for CH3
		* @param  None
		* @retval None
		*/
	void PWM_setCH3Duty(uint16_t duty){
	//	 TIM1_SetCompare3(duty);
	}



