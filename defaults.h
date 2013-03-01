#ifndef __defaults_h_
#define __defaults_h_		

		/* Default values for RAMP programs. 
		* Format as follows: { RPM_MIN, PWM_MIN, RPM_MAX, PWM_MAX, DWELL_MIN, DWELL_MAX}
		*
		* example: {100,1200,400,1500,1,2} - RPM min=100, PWM min=1200us, 
		* RPM max=400, PWM max=1500us, DWELL min=1s, DWELL max=2s
		*/
		#define RAMP_DEFAULT_1	{100,1200,400,1500,1,2}
		#define RAMP_DEFAULT_2	{200,1300,500,1600,3,4}
		#define RAMP_DEFAULT_3	{300,1400,600,1700,5,6}
		
		#define RAMP_MODE_COUNT 3
		#define RAMP_DWELL_MAX	50
		#define RAMP_DWELL_MIN	1
		
		/* Default values for device configuration
		* REFLECTOR_COUNT_DEFAULT : defines the reflector count
		* PWM_INCREMENT_DEFAULT : defines the PWM width increment in DIGITAL mode
		*/
		#define REFLECTOR_COUNT_DEFAULT	1
		#define PWM_INCREMENT_DEFAULT	4
		
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
		
		
		#define PWM_WIDTH_MIN		1000
		#define PWM_WIDTH_MAX		2000
		
		
		#define PWM_INC_COUNT 5
		#define PWM_INC_VALUES 1,2,4,10,100
		
		
		//#define _ARM_ESC_ON_RAMP
		#define _ARM_ESC_ON_STARTUP /*Arm the ESC when showing the logo*/
		// Enable the PWM output when in main menu
		#define _ENABLE_PWM_OUTPUT_ON_MAIN_MENU
		// Enable the PWM output when in setup menu
		#define _ENABLE_PWM_OUTPUT_ON_SETUP_MENU		
		
#endif		