#ifndef __stepper_h_
#define __stepper_h_
#include "stm32f0xx_gpio.h"
	/* Public type definitions ------------------------------------------------*/	
	typedef struct {
		uint32_t stepper_dir_pin;
		GPIO_TypeDef* stepper_dir_port;
		uint32_t stepper_pulse_pin;
		GPIO_TypeDef* stepper_pulse_port;
	} Tstepper_Config;
	
	/* Public function prototypes ---------------------------------------------*/
			void stepper_init(Tstepper_Config _stepper_config);
			void stepper_step(uint8_t dir,uint16_t count);
#endif
	