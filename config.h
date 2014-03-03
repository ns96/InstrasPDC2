#ifndef __config_h_
#define __config_h_		

		/* Define the device version string.
		* This string is shown on the logo screen.
		*/
		#define DEVICE_VERSION_STRING " PDC2 ver.1.0 "
			
		/* Default values for RAMP programs. 
		* Format as follows: { RPM_MIN, PWM_MIN, RPM_MAX, PWM_MAX, DWELL_MIN, DWELL_MAX}
		*
		* example: {100,1200,400,1500,1,2} - RPM min=100, PWM min=1200us, 
		* RPM max=400, PWM max=1500us, DWELL min=1s, DWELL max=2s
		*/
		#define RAMP_DEFAULT_1	{100,1200,400,1500,1,2}
		#define RAMP_DEFAULT_2	{200,1300,500,1600,3,4}
		#define RAMP_DEFAULT_3	{300,1400,600,1700,5,6}
		
		/* Ramp mode settings.
		* RAMP_MODE_COUNT defines the number of RAMP modes
		* RAMP_DWELL_MAX defines the max dwell time
		* RAMP_DWELL_MIN defines the min dwell time
		*/
		#define RAMP_MODE_COUNT 3
		#define RAMP_DWELL_MAX	50
		#define RAMP_DWELL_MIN	1
		
		/* Default values for device configuration
		* REFLECTOR_COUNT_DEFAULT : defines the reflector count
		* PWM_INCREMENT_DEFAULT : defines the PWM width increment in DIGITAL mode
		*/
		#define REFLECTOR_COUNT_DEFAULT	1
		
		/* Values for buzzer control
		* BUZZER_FREQUENCY : frequency of the signal for speaker
		* BUZZER_TIME : duration of beep
		*/
		
		#define BUZZER_FREQUENCY		3000
		#define BUZZER_TIME					10
		
		/* Limiting values for RPM measurement
		* RPM_MIN_VALUE : min RPM value
		* RPM_MAX_VALUE : max RPM value
		*/		
		#define RPM_MIN_VALUE				100
		#define RPM_MAX_VALUE				30000
		#define NUM_REFLECTORS_MAX		10		
		
		/* Limiting values for the PWM signal width.
		*	PWM_WIDTH_MIN defines min PWM width in us
		*	PWM_WIDTH_MAX defines max PWM width in us
		*/
		#define PWM_WIDTH_MIN		1000
		#define PWM_WIDTH_MAX		2000
		
		/* Values for digital mode increment steps.
		*	PWM_INC_COUNT defines the number of steps to chose from.
		*	PWM_INC_VALUES defines the values of increment steps.
		* PWM_INCREMENT_DEFAULT defines the default value for increment step.
		*/
		#define PWM_INC_COUNT 5
		#define PWM_INC_VALUES 1,2,4,10,100
		#define PWM_INCREMENT_DEFAULT	4
		
		
		//#define _ARM_ESC_ON_RAMP
		/*Arm the ESC when showing the logo*/
		#define _ARM_ESC_ON_STARTUP 
		// Enable the PWM output when in main menu
		#define _ENABLE_PWM_OUTPUT_ON_MAIN_MENU
		// Enable the PWM output when in setup menu
		#define _ENABLE_PWM_OUTPUT_ON_SETUP_MENU		
		/* Vacuum pump control parameters
		* Vacuum pump is turned on when the motor is spinning
		* and switched off after the motor stops.
		*/
		// To disable vacuum pump control,
		// comment the following line
//		#define PUMP_CONTROL_ENABLED 1
		// Switches on the pump when 
		// S1 PWM value exceeds this limit
		#define PUMP_TURN_ON_PWM	1010
		// Defines the S2 PWM value required
		// for turning on the pump
		#define PUMP_ON_PWM_VALUE	2000
		// Set the time in seconds motor has to be stopped
		// before the vacuum pump is switched off
		#define PUMP_DELAY	2
		// In case of RPM measurement failure
		#define PUMP_RPM_TEST_PWM 1065
		// the pump will be switched off in
		// PUMP_ON_DELAY seconds after S1 PWM value is less
		// than PUMP_TURN_ON_PWM
		#define PUMP_ON_DELAY	10
		
#endif		