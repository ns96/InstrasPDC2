/**
  ******************************************************************************
  * @file    buzzer.c 
  * @author  Vaidas Zakarka
  * @version V1.0.0
  * @date    02-February-2013
  * @brief   software buzzer driver
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 ElectronicsWorkshop.eu</center></h2>
  ******************************************************************************
  */ 
	
	/* Includes ------------------------------------------------------------------*/
		#include "stm8s.h"
		#include "buzzer.h"
		#include "global.h"
	/* Private defines -----------------------------------------------------------*/
		#define GPIO_HIGH(a,b) 		a->ODR|=b
		#define GPIO_LOW(a,b)		a->ODR&=~b
	/* Private function prototypes -----------------------------------------------*/
		void buzzer_GPIO_init(void);		
		uint16_t defaultFrequency=3000;
		uint16_t defaultTime=20;
	/* Public variables ----------------------------------------------------------*/
		Tbuzzer_Config buzzer_config;
	/* ---------------------------------------------------------------------------*/
	
	/**
  * @brief  Initializes the buzzer driver
  * @param xx: yyy
  * @retval : None
  */
		void buzzer_init(Tbuzzer_Config _buzzer_config){
			buzzer_config=_buzzer_config;
			buzzer_GPIO_init();
		}
			
		void delay_us(uint32_t duration){
			uint16_t time_current;
			static uint16_t time_last;
			time_last=(uint16_t)(((TIM1->CNTRH)<<8)|(TIM1->CNTRL));
			do {
				time_current=(uint16_t)(((TIM1->CNTRH)<<8)|(TIM1->CNTRL));
			} while((uint16_t)((uint16_t)time_current-(uint16_t)time_last)<(duration*2));
		}		
	/**
  * @brief  Beeps
  * @param xx: yyy
  * @retval : None
  */
		void buzzer_beepA(uint16_t frequency,uint16_t time){
			// period in us
			uint16_t half_period=((uint32_t)1000000/(uint32_t)frequency)/2;
			static uint32_t t;
			t=(((uint32_t)time*(uint32_t)1000)/(uint32_t)(half_period*2));

			while(t-->0){
			
				//GPIO_TOGGLE(S1_PORT, S1_PIN);
				GPIO_HIGH(buzzer_config.buzzer_port, buzzer_config.buzzer_pin);
				GPIO_HIGH(S1_PORT, S1_PIN);
				delay_us(half_period);
				GPIO_LOW(S1_PORT, S1_PIN);
				GPIO_LOW(buzzer_config.buzzer_port, buzzer_config.buzzer_pin);		
				delay_us(half_period);				
			}
		}		
		
	/**
  * @brief  Beeps according to default pitch and time values
  * @retval : None
  */
		void buzzer_beep(){
			buzzer_beepA(defaultFrequency,defaultTime);
		}
		
		/**
  * @brief  Changes the pitch and duration of the beep
  * @param frequency: the frequency applied to the speaker
	* @param time: duration of a single beep
  * @retval : None
  */
		void buzzer_setFreqTime(uint16_t frequency,uint16_t time){
			defaultFrequency=frequency;
			defaultTime=time;			
		}
  
	/* Private functions ---------------------------------------------------------*/		
	/**
  * @brief  Initializes the gpio for software SPI
  * @param xx: yyy
  * @retval : None
  */
	void buzzer_GPIO_init(void){
		
		/* Configure SPI1 MOSI as output */
		GPIO_Init( buzzer_config.buzzer_port, buzzer_config.buzzer_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
		
		// Turn the buzzer off
		if (buzzer_config.buzzer_polarity)
			GPIO_LOW(buzzer_config.buzzer_port, buzzer_config.buzzer_pin);
		else
			GPIO_HIGH(buzzer_config.buzzer_port, buzzer_config.buzzer_pin);
	}