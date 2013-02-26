#ifndef __pwm_h_
#define __pwm_h_
	/* Public function prototypes ---------------------------------------------*/
	void PWM_init(void);
	void PWM_outputEnable();
	void PWM_outputDisable();
	void PWM_setCH1Duty(uint16_t duty);
	void PWM_setCH2Duty(uint16_t duty);
	void PWM_setCH3Duty(uint16_t duty);
#endif