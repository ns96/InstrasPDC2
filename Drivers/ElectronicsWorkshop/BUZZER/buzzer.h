#ifndef __buzzer_h_
#define __buzzer_h_
	/* Public type definitions ------------------------------------------------*/	
	typedef struct {
		u32 buzzer_pin;
		GPIO_TypeDef* buzzer_port;
		uint8_t buzzer_polarity;
	} Tbuzzer_Config;
	
	/* Public function prototypes ---------------------------------------------*/
			void buzzer_init(Tbuzzer_Config _buzzer_config);
			void buzzer_beepA(uint16_t frequency,uint16_t time);
			void buzzer_beep();
			void buzzer_setFreqTime(uint16_t frequency,uint16_t time);
#endif