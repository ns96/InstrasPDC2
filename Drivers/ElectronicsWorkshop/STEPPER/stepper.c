/**
  ******************************************************************************
  * @file    stepper.c 
  * @author  Vaidas Zakarka
  * @version V1.0.0
  * @date    09-March-2014
  * @brief   stepper driver driver
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2014 ElectronicsWorkshop.eu</center></h2>
  ******************************************************************************
  */ 
	
	/* Includes ------------------------------------------------------------------*/
		#include "stm8s.h"
		#include "stepper.h"
		#include "global.h"
	/* Private defines -----------------------------------------------------------*/
		#define GPIO_HIGH(a,b) 		a->ODR|=b
		#define GPIO_LOW(a,b)		a->ODR&=~b
	/* Private function prototypes -----------------------------------------------*/
		void stepper_GPIO_init(void);		

	/* Public variables ----------------------------------------------------------*/
		Tstepper_Config stepper_config;
	/* ---------------------------------------------------------------------------*/
	
	/**
  * @brief  Initializes the stepper driver
  * @param xx: yyy
  * @retval : None
  */
		void stepper_init(Tstepper_Config _stepper_config){
			stepper_config=_stepper_config;
			stepper_GPIO_init();
		}
			
		void delay_us1(uint32_t duration){
			uint16_t time_current;
			static uint16_t time_last;
			time_last=(uint16_t)(((TIM1->CNTRH)<<8)|(TIM1->CNTRL));
			do {
				time_current=(uint16_t)(((TIM1->CNTRH)<<8)|(TIM1->CNTRL));
			} while((uint16_t)((uint16_t)time_current-(uint16_t)time_last)<(duration*2));
		}		
	/**
  * @brief  Steps
  * @param xx: yyy
  * @retval : None
  */
			void stepper_step(uint8_t dir,uint16_t count){
				uint8_t i=0;
				if (dir)
					GPIO_HIGH(stepper_config.stepper_dir_port, stepper_config.stepper_dir_pin);
				else
					GPIO_LOW(stepper_config.stepper_dir_port, stepper_config.stepper_dir_pin);
				for (i=0;i<count;i++){
					GPIO_HIGH(stepper_config.stepper_pulse_port, stepper_config.stepper_pulse_pin);
					delay_us1(1000);
					GPIO_LOW(stepper_config.stepper_pulse_port, stepper_config.stepper_pulse_pin);
					delay_us1(2000);	
				}
			}
  
	/* Private functions ---------------------------------------------------------*/		
	/**
  * @brief  Initializes the gpio for software SPI
  * @param xx: yyy
  * @retval : None
  */
	void stepper_GPIO_init(void){
		
		/* Configure direction and pulse pins as outputs */
		GPIO_Init( stepper_config.stepper_dir_port, stepper_config.stepper_dir_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
		GPIO_Init( stepper_config.stepper_pulse_port, stepper_config.stepper_pulse_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
		
			GPIO_LOW(stepper_config.stepper_dir_port, stepper_config.stepper_dir_pin);
			GPIO_LOW(stepper_config.stepper_pulse_port, stepper_config.stepper_pulse_pin);

	}