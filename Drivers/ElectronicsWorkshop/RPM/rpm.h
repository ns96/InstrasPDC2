#ifndef __rpm_h_
#define __rpm_h_
#include "stm32f0xx_gpio.h"
	/* Public type definitions ------------------------------------------------*/
	typedef uint32_t EXTI_Port_TypeDef ;
	typedef struct {
		uint32_t RPM_pin;
		GPIO_TypeDef* RPM_port;
		EXTI_Port_TypeDef RPM_exti;
	} Trpm_pinConfig;
	
	/* Public function prototypes ---------------------------------------------*/
		void rpm_init(Trpm_pinConfig _rpm_pins,uint16_t min,uint16_t max);
		void rpm_callback(void);
		void rpm_interruptHandler(void);
		void rpm_timerInterruptHandler(void);
#endif
	
	