#ifndef __pwm_h_
#define __pwm_h_
	#include "stm32f0xx_rcc.h"
	#include "stm32f0xx_tim.h"
	/* Public function prototypes ---------------------------------------------*/
	void PWM_init(void);
	void PWM_outputEnable(void);
	void PWM_outputDisable(void);
	void PWM_setCH1Duty(uint16_t duty);
	void PWM_setCH2Duty(uint16_t duty);
	void PWM_setCH3Duty(uint16_t duty);
	void PWM_setAllChannelDuty(uint16_t duty);
#endif
