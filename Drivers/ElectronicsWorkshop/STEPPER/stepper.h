#ifndef __stepper_h_
#define __stepper_h_
	/* Public type definitions ------------------------------------------------*/	
	typedef struct {
		u32 stepper_dir_pin;
		GPIO_TypeDef* stepper_dir_port;
		u32 stepper_pulse_pin;
		GPIO_TypeDef* stepper_pulse_port;
	} Tstepper_Config;
	
	/* Public function prototypes ---------------------------------------------*/
			void stepper_init(Tstepper_Config _stepper_config);
			void stepper_step(uint8_t dir,uint16_t count);
#endif