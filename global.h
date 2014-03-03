#ifndef __global_h_
#define __global_h_
	#define STV3_DEBUG
//	#include "board_stv307.h"
#include "board_MotorTalkV1a.h"
	#include "config.h"
	
	// Structure for measuring the time
	typedef struct {
	uint8_t timeStart;
	uint8_t timeElapsed;
} Ttimer;

	// Structure for storing RAMP mode configuration
	typedef struct {
		uint16_t RPM_min;
		uint16_t PWM_min;
		uint16_t RPM_max;
		uint16_t PWM_max;
		uint8_t min_dwell;
		uint8_t max_dwell;
	} TrampConfig;
	

	// Structure for storing main device configuration.
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
	

	// Defines the frequency of RPM measurement
	#define RPM_PULSE_MEASUREMENT_FREQ 1
	// Calculates maximum allowed pulses per second
	#define RPM_PULSE_COUNT_MAX	((RPM_MAX_VALUE/60)*NUM_REFLECTORS_MAX)/RPM_PULSE_MEASUREMENT_FREQ
	
	// Defines the index numbers for the main menu
	#define STARTUP_MENU_ANALOG		1
	#define STARTUP_MENU_DIGITAL	2
	#define STARTUP_MENU_RAMP			3
	#define STARTUP_MENU_NONE			0
	
	// Defines the backlight indexes
	#define BACKLIGHT_OFF			1
	#define BACKLIGHT_LOW			2
	#define BACKLIGHT_HIGH		3
	
	//****************** Global variables used within all project*****************
	// Main device configuration
	extern TmainConfig mainConfig; 
	// Counter value, incremented every 20ms
	extern volatile uint16_t TIM1_cnt;
	// Measured RPM values
	extern uint16_t rpm,rpm_p;	
	// ADC conversion value, used for reading the potentiometer
	extern volatile uint16_t Conversion_Value;
	// Variable, defining the current menu
	extern uint8_t menu;	
	// Array of possible increment values in digital mode
	extern const uint8_t pwm_inc_array[PWM_INC_COUNT];
	// PWM values for S1 and S2 outputs
	extern uint16_t pwm_S1,pwm_S2;
	// PC mode flag
	extern uint8_t PCmode;
	// Values for detecting the loss of RPM signal
	extern uint8_t rpmNoSignal,rpmSpinCNT;
#endif