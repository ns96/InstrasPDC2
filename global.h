#ifndef __global_h_
#define __global_h_
	#define STV3_DEBUG

	
	#include "board_stv307.h"
	#include "defaults.h"
	typedef struct {
	uint8_t timeStart;
	uint8_t timeElapsed;
} Ttimer;

	typedef struct {
		uint16_t RPM_min;
		uint16_t PWM_min;
		uint16_t RPM_max;
		uint16_t PWM_max;
		uint8_t min_dwell;
		uint8_t max_dwell;
	} TrampConfig;
	

	
	typedef struct {
		uint8_t numReflectors;
		uint8_t PWMincValue;
		uint8_t startupMenu;
		uint8_t backLight;
		uint8_t PWMincIndex;
		TrampConfig rampCfg[3];
		uint8_t rampCurrent;
		uint16_t RPMus;
	} TmainConfig;
	


	#define RPM_PULSE_MEASUREMENT_FREQ 1
	#define RPM_PULSE_COUNT_MAX	((RPM_MAX_VALUE/60)*NUM_REFLECTORS_MAX)/RPM_PULSE_MEASUREMENT_FREQ
	
	#define STARTUP_MENU_ANALOG		1
	#define STARTUP_MENU_DIGITAL	2
	#define STARTUP_MENU_RAMP			3
	#define STARTUP_MENU_NONE			0
	
	
	#define BACKLIGHT_OFF			1
	#define BACKLIGHT_LOW			2
	#define BACKLIGHT_HIGH		3
		
	extern TmainConfig mainConfig;
	extern volatile uint16_t TIM1_cnt;
	extern uint16_t rpm,rpm_p;	
	extern volatile uint16_t Conversion_Value;
	extern uint8_t menu;
	
	extern const uint8_t pwm_inc_array[PWM_INC_COUNT];
#endif