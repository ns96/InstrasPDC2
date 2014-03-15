/**
  ******************************************************************************
  * @file    exgpio.c 
  * @author  Vaidas Zakarka
  * @version V1.0.0
  * @date    14-March-2014
  * @brief   software buzzer driver
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 ElectronicsWorkshop.eu</center></h2>
  ******************************************************************************
  */ 
	
	/* Includes ------------------------------------------------------------------*/
		#include "stm8s.h"
		#include "exgpio.h"
		#include "global.h"
	/* Private defines -----------------------------------------------------------*/
		#define GPIO_HIGH(a,b) 		a->ODR|=b
		#define GPIO_LOW(a,b)		a->ODR&=~b
		#define GPIO_TOGGLE(a,b) 	a->ODR^=b
	/* Private function prototypes -----------------------------------------------*/
	
	/* Public variables ----------------------------------------------------------*/
		TEXGPIO_Config exgpio_config;
	/* ---------------------------------------------------------------------------*/
	


  
	/* Private functions ---------------------------------------------------------*/		
	/**
  * @brief  Initializes the gpio
  * @param xx: yyy
  * @retval : None
  */
	void EXGPIO_init(TEXGPIO_Config _exgpio_config){
		exgpio_config=_exgpio_config;
		/* Configure SPI1 MOSI as output */
		GPIO_Init( _exgpio_config.D0_port, _exgpio_config.D0_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
		GPIO_Init( _exgpio_config.D1_port, _exgpio_config.D1_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
		GPIO_Init( _exgpio_config.D2_port, _exgpio_config.D2_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
		GPIO_Init( _exgpio_config.D3_port, _exgpio_config.D3_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
		GPIO_Init( _exgpio_config.D4_port, _exgpio_config.D4_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
		GPIO_Init( _exgpio_config.D5_port, _exgpio_config.D5_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
	}
	
	void EXGPIO_set(uint8_t pin,uint8_t state){
		if ((pin&D0)>0)
		{
			if (state)
				GPIO_HIGH(exgpio_config.D0_port, exgpio_config.D0_pin);
			else
				GPIO_LOW(exgpio_config.D0_port, exgpio_config.D0_pin);
		}
		if ((pin&D1)>0)
		{
			if (state)
				GPIO_HIGH(exgpio_config.D1_port, exgpio_config.D1_pin);
			else
				GPIO_LOW(exgpio_config.D1_port, exgpio_config.D1_pin);
		}		
		if ((pin&D2)>0)
		{
			if (state)
				GPIO_HIGH(exgpio_config.D2_port, exgpio_config.D2_pin);
			else
				GPIO_LOW(exgpio_config.D2_port, exgpio_config.D2_pin);
		}
		if ((pin&D3)>0)
		{
			if (state)
				GPIO_HIGH(exgpio_config.D3_port, exgpio_config.D3_pin);
			else
				GPIO_LOW(exgpio_config.D3_port, exgpio_config.D3_pin);
		}
		if ((pin&D4)>0)
		{
			if (state)
				GPIO_HIGH(exgpio_config.D4_port, exgpio_config.D4_pin);
			else
				GPIO_LOW(exgpio_config.D4_port, exgpio_config.D4_pin);
		}
		if ((pin&D5)>0)
		{
			if (state)
				GPIO_HIGH(exgpio_config.D5_port, exgpio_config.D5_pin);
			else
				GPIO_LOW(exgpio_config.D5_port, exgpio_config.D5_pin);
		}
	}
	
		void EXGPIO_toggle(uint8_t pin){
		if ((pin&D0)>0)
				GPIO_TOGGLE(exgpio_config.D0_port, exgpio_config.D0_pin);
		if ((pin&D1)>0)
				GPIO_TOGGLE(exgpio_config.D1_port, exgpio_config.D1_pin);
		if ((pin&D2)>0)
				GPIO_TOGGLE(exgpio_config.D2_port, exgpio_config.D2_pin);
		if ((pin&D3)>0)
				GPIO_TOGGLE(exgpio_config.D3_port, exgpio_config.D3_pin);
		if ((pin&D4)>0)
				GPIO_TOGGLE(exgpio_config.D4_port, exgpio_config.D4_pin);
		if ((pin&D5)>0)
				GPIO_TOGGLE(exgpio_config.D5_port, exgpio_config.D5_pin);				
	}