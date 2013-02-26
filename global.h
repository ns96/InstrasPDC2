#ifndef __global_h_
#define __global_h_

	#define STV3_DEBUG
	#define _ARM_ESC_ON_RAMP
	
	#include "board_stv307.h"

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
	
	#define RAMP_MODE_COUNT 3
	#define RAMP_DWELL_MAX	50
	#define RAMP_DWELL_MIN	1
	
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
	
	#define NUM_REFLECTORS_MAX		10

	#define RAMP1_DEFAULTS 200,3000,10,30
	
	#define STARTUP_MENU_ANALOG		1
	#define STARTUP_MENU_DIGITAL	2
	#define STARTUP_MENU_RAMP			3
	#define STARTUP_MENU_NONE			0
	
	
	#define BACKLIGHT_OFF			1
	#define BACKLIGHT_LOW			2
	#define BACKLIGHT_HIGH		3
	
	
	#define PWM_WIDTH_MIN		1000
	#define PWM_WIDTH_MAX		2000
	
	#define PWM_INC_COUNT 5
	#define PWM_INC_VALUES 1,2,4,10,100
	
	extern TmainConfig mainConfig;
	extern volatile uint16_t TIM1_cnt;
	extern uint16_t rpm;	
	extern volatile uint16_t Conversion_Value;
	extern uint8_t menu;
	
	extern const uint8_t pwm_inc_array[PWM_INC_COUNT];
#endif