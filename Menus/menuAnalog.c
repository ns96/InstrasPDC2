/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "lcd_3310.h"
#include "btn.h"
#include "menu.h"
#include "Utils.h"
#include "global.h"
#include "pot.h"
#include "pwm.h"
#include "buzzer.h"

/* Private defines -----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
	void menuAnalog_redraw(void);

/* Private global variables -----------------------------------------------*/

	// Variable for determing if the menu task 
	// is called for the first time
	uint8_t menuAnalog_firstRun=1,menuAnalog_outputEnable=0;


/* Private functions ---------------------------------------------------------*/
	/**	Redraws the screen completely
	*
	*/
	void menuAnalog_redraw(void){
		lcd_3310_drawTextXY(0,0,"Analog Control");
		lcd_3310_drawTextXY(0,2,"RPM PAUSE");
		lcd_3310_drawTextXY(0,3,"PWM 00000 us");
	}

	/**	Initializes  Menu
	*/
	void menuAnalog_Init(void){
		pot_init();		
		lcd_3310_clear();
		menuAnalog_redraw();
		// Wait for enter button to be depressed
		while ((btn_getState()&btnEnter)>0)
			;
	}
	/**	Deinitializes Main Menu
	*/
	void menuAnalog_DeInit(void){
		pot_DeInit();
		PWM_outputDisable();
		menuAnalog_firstRun=1;
		menuAnalog_outputEnable=0;
	}

/* Public functions ---------------------------------------------------------*/
	void menuAnalog(void){
		uint8_t buttons,str[14];
		uint16_t pwm_width;
		static Ttimer btnTimer={0,0};
		static uint16_t pauseTimer=0;
		static uint8_t pauseState=0;
		// Check if the function is called for the first time
		if (menuAnalog_firstRun)
		{
			// Initialize
			menuAnalog_Init();
			// Clear menuAnalog_firstRun variable
			menuAnalog_firstRun=0;
		}	
		
		// Calculate the time elapsed since the button timer was started
		btnTimer.timeElapsed=(TIM1_cnt&0xFF)-btnTimer.timeStart;	
		// If time elapsed is more than 200ms(10*20ms)
		if (btnTimer.timeElapsed>10)
		{
			// Set timeStart to the current time
			btnTimer.timeStart=TIM1_cnt&0xFF;
			// Read state of buttons
			buttons=btn_getState();
			if (buttons>0)
				buzzer_beep();
			// If EXIT button is pressed
			if ((buttons&btnExit)>0){
				buzzer_beepA(3200,10);
				if (menuAnalog_outputEnable){
					menuAnalog_outputEnable=0;
					PWM_outputDisable();
				}
				else{
					menuAnalog_DeInit();
					menu=MENU_MAIN;
				}
			}	
			
				// If ENTER button is pressed
			if ((buttons&btnEnter)>0){
				if (!menuAnalog_outputEnable){
					menuAnalog_outputEnable=1;
					PWM_outputEnable();
					buzzer_beepA(3200,10);
				}
			}
			
			if ((buttons&btnUp)>0){
				//	buzzer_beepA(3200,10);
			}
			if ((buttons&btnDown)>0){
				//	buzzer_beepA(3200,10);
			}
			
			
		}

		// Calculate the PWM width. The width step is 0.5us, 
		// thus the required number of us is multiplied by two
		pwm_width=1000+Conversion_Value;
		
		// limit PWM width to PWM_WIDTH_MAX value
		if (pwm_width>PWM_WIDTH_MAX)
			pwm_width=PWM_WIDTH_MAX;
		 
		
		// Set PWM width
		PWM_setCH1Duty(pwm_width*2);
			
			//display pwm width in us
			itoa(pwm_width,&str);
			lcd_3310_drawTextXY(8*6,3," ");
			lcd_3310_drawTextXY(4*6,3,str);
			
			
		if ((menuAnalog_outputEnable)||(!pauseState)){
			menu_displayRPM(4*6,2);
			//menu_displayRPM_pulses(4*6,3);
		}
		
		if (!menuAnalog_outputEnable){
			if (((uint16_t)(TIM1_cnt-pauseTimer))>50){
				pauseTimer=TIM1_cnt;
				if (pauseState)
					pauseState=0;
				else{
					pauseState=1;
					lcd_3310_drawTextXY(4*6,2,"PAUSE");
				}
			}
		}
	}