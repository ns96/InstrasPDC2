#ifndef __btn_h_
	#define __btn_h_
	#include "stm32f0xx_gpio.h"
	/* Public defines ---------------------------------------------------------*/
	#define btnEnter	1<<0
	#define btnExit		1<<1
	#define btnUp			1<<2
	#define btnDown		1<<3
	/* Public type definitions ------------------------------------------------*/
	typedef struct {
		uint32_t Enter_pin;
		GPIO_TypeDef* Enter_port;
		uint32_t Exit_pin;
		GPIO_TypeDef* Exit_port;		
		uint32_t Up_pin;
		GPIO_TypeDef* Up_port;		
		uint32_t Down_pin;
		GPIO_TypeDef* Down_port;		
	} Tbtn_pinConfig;
	/* Public function prototypes ---------------------------------------------*/
	void btn_init(Tbtn_pinConfig _pin_cfg);
	uint8_t btn_getState(void);
#endif
