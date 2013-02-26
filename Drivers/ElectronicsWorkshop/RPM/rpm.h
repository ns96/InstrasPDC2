#ifndef __rpm_h_
#define __rpm_h_
	/* Public type definitions ------------------------------------------------*/
	typedef struct {
		u32 RPM_pin;
		GPIO_TypeDef* RPM_port;
		EXTI_Port_TypeDef RPM_exti;
	} Trpm_pinConfig;
	
	/* Public function prototypes ---------------------------------------------*/
		void rpm_init(Trpm_pinConfig _rpm_pins,uint16_t min,uint16_t max);
		void rpm_callback(void);
		void rpm_interruptHandler(void);
#endif