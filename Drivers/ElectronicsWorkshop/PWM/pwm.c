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
	#include "stm8s.h"
	
	/* Public functions ---------------------------------------------------------*/		

	/**
		* @brief  Configure PWM time period and enable the outputs
		* @param  None
		* @retval None
		*/
	void PWM_init(void)
	{
	
		TIM1_DeInit();
	
		TIM1_TimeBaseInit(7, TIM1_COUNTERMODE_UP, 40000, 0);
		/*TIM1_Pulse = CCR1_Val*/
		TIM1_OC1Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE,
								 0, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
								 TIM1_OCNIDLESTATE_RESET); 
	
		/*TIM1_Pulse = CCR2_Val*/
		TIM1_OC2Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_DISABLE, TIM1_OUTPUTNSTATE_ENABLE, 0,
								 TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET, 
								 TIM1_OCNIDLESTATE_RESET);
	
		/*TIM1_Pulse = CCR3_Val*/
	 TIM1_OC3Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_DISABLE, TIM1_OUTPUTNSTATE_ENABLE,
								 0, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
								 TIM1_OCNIDLESTATE_RESET); 				 
								 
		/* Enable Timer1 compare interrupt*/
		TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
		
	
		/* TIM1 counter enable */
		TIM1_Cmd(ENABLE);
	}

	/**
		* @brief  Enable PWM outputs
		* @param  None
		* @retval None
		*/
	void PWM_outputEnable(){
		/* TIM1 Main Output Enable */
		TIM1_CtrlPWMOutputs(ENABLE);
	}

	/**
		* @brief  Disable PWM outputs
		* @param  None
		* @retval None
		*/
	void PWM_outputDisable(){
		/* TIM1 Main Output Disable */
		TIM1_CtrlPWMOutputs(DISABLE);
	}

	/**
		* @brief  Sets PWM duty for CH1
		* @param  None
		* @retval None
		*/
	void PWM_setCH1Duty(uint16_t duty){
			TIM1_SetCompare1(duty);
	}

	/**
		* @brief  Sets PWM duty for CH2
		* @param  None
		* @retval None
		*/
	void PWM_setCH2Duty(uint16_t duty){
		 TIM1_SetCompare2(duty); 
	}
	
	/**
		* @brief  Sets PWM duty for CH3
		* @param  None
		* @retval None
		*/
	void PWM_setCH3Duty(uint16_t duty){
		 TIM1_SetCompare3(duty);
	}



