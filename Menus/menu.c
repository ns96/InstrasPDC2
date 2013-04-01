/* Includes ------------------------------------------------------------------*/
	#include "stm8s.h"
	#include "lcd_3310.h"
	#include "btn.h"
	#include "menu.h"
	#include "global.h"
	#include "Utils.h"
/* Private defines -----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private global variables -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ---------------------------------------------------------*/
	/**	Draws the current RPM value on the screen
	* @param x - x coordinate
	* @param y - y coordinate
	*/
	void menu_displayRPM(uint8_t x, uint8_t y){
			uint8_t str[14];
//			uint16_t trpm1,trmp2;
		static Ttimer rpmTimer={0,0};
		// Calculate elapsed time since last rpm refresh
		// If time is more than 1s (50*20ms)
		if (((TIM1_cnt&0xFF)-rpmTimer.timeStart)>50)
		{
			// Store current time
			rpmTimer.timeStart=(TIM1_cnt)&0xFF;
			// Clear part of LCD, showing the RPM number
			lcd_3310_drawTextXY(x,y,"      ");		
			itoa((int32_t)rpm_p,&str);			
		/*	trpm1=rpm;
			trmp2=rpm_p;
			if ((rpm_p*mainConfig.numReflectors/60)<150)
				// Convert integer to string
				itoa((int32_t)trpm1,&str);
			else
				// Convert integer to string
				itoa((int32_t)trmp2,&str);		*/	
			// Draw the RPM on the screen
			lcd_3310_drawTextXY(x,y,str);
		}
	}
	
	/**	Deinitializes all menus
	*/	
	void menu_deinitAll(void){
		
		menuPC_DeInit();
		menuSetupRamp_DeInit();
		menuSetup_DeInit();
		menuRamp_DeInit();
		menuDigital_DeInit();
		menuAnalog_DeInit();
		mainMenu_DeInit();
		menuTest_DeInit();
	}
	/**	Controls S2 PWM width separately, 
	*	when vacuum pump control is enabled
	*/	
	#ifdef PUMP_CONTROL_ENABLED	
		void controlS2(void){
			static uint8_t rpmFailCnt=0;
			// Read current PWM width value of S1
			if (TIM1_GetCapture3()>(PUMP_TURN_ON_PWM*2)){
				TIM1_SetCompare2(PUMP_ON_PWM_VALUE*2);	//S2	
			}
			else{
				// If the motor was not spinning for predefined period of time
				if (rpmSpinCNT==0){
					// Switch off the vacuum pump
					TIM1_SetCompare2(1000*2);	//S2		
				}
			}	
			// If there is no RPM measurement even though the motor is on	
			if ((rpm_p<60)&&(TIM1_GetCapture3()>(PUMP_RPM_TEST_PWM*2))){
				// Increment RPM module failure counter
				if (rpmFailCnt<5)
					rpmFailCnt++;
				else{
					// Counter exceeded the limit - there are errors in RPM sensing
					rpmSpinCNT=PUMP_ON_DELAY;	// Set delayed pump switch off
				}
			}
			else
			{
				// If there was a temporary RPM value loss
				if (rpmFailCnt>0)
					rpmFailCnt--;	// Decrease RPM module failure counter
			}			
		}
	#endif
	