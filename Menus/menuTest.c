/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "btn.h"
#include "menu.h"
#include "Utils.h"
#include "global.h"
#include "pot.h"
#include "pwm.h"
#include "buzzer.h"
/* Private defines -----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
	void menuTest_redraw(void);

/* Private global variables -----------------------------------------------*/

	// Variable for determing if the menu task 
	// is called for the first time
	uint8_t menuTest_firstRun=1;


/* Private functions ---------------------------------------------------------*/
	/**	Redraws the screen completely
	*
	*/
	void menuTest_redraw(void){
		lcd_drawTextXY(0,0,"Test menu");
		lcd_drawTextXY(0,2,"Freq.     Hz");
		lcd_drawTextXY(0,3,"Time      ms");
	}

	/**	Initializes  Menu
	*/
	void menuTest_Init(void){
		pot_init();		
		lcd_clear();
		menuTest_redraw();
		// Wait for enter button to be depressed
		while ((btn_getState()&btnEnter)>0)
			;
	}
	/**	Deinitializes menu
	*/
	void menuTest_DeInit(void){
		pot_DeInit();
		menuTest_firstRun=1;
	}

/* Public functions ---------------------------------------------------------*/
	void menuTest(void){
		uint8_t buttons,str[14];
		static Ttimer btnTimer={0,0};
		static uint16_t time_val=0,freq_val=0;
		static uint8_t valueToChange=0;		
		// Check if the function is called for the first time
		if (menuTest_firstRun)
		{
			// Initialize
			menuTest_Init();
			// Clear menuTest_firstRun variable
			menuTest_firstRun=0;
		}	
		
		// Calculate the time elapsed since the button timer was started
		btnTimer.timeElapsed=(TIM1_cnt&0xFF)-btnTimer.timeStart;	
		// If time elapsed is more than 400ms(20*20ms)
		if (btnTimer.timeElapsed>20)
		{
			// Set timeStart to the current time
			btnTimer.timeStart=TIM1_cnt&0xFF;
			// Read state of buttons
			buttons=btn_getState();
			
			// If EXIT button is pressed
			if ((buttons&btnExit)>0){
				menuTest_DeInit();
				menu=MENU_MAIN;
			}	
				// If ENTER button is pressed
			if ((buttons&btnEnter)>0){
				buzzer_beep();
			}
			
			if ((buttons&btnUp)>0){
				if (valueToChange<1)
					valueToChange++;
				else
					valueToChange=0;
					
				if (valueToChange==0)
					pot_init();
					
				if (valueToChange==2){
					pot_DeInit();
				}
			}
			if ((buttons&btnDown)>0){
			}
		}
		if (valueToChange==0){
			freq_val=Conversion_Value*5;
		}
		if (valueToChange==1){
			time_val=Conversion_Value/20;
		}
		
		buzzer_setFreqTime(freq_val,time_val);
		//display pwm width in us
		itoa(freq_val,&str);
		lcd_drawTextXY(5*6,2,"    ");
		if (valueToChange==0)
			lcd_invert(1);
		else
			lcd_invert(0);
		lcd_drawTextXY(5*6,2,str);
		lcd_invert(0);
			
		//display pwm width in us
		itoa(time_val,&str);
		lcd_drawTextXY(5*6,3,"    ");
		if (valueToChange==1)
			lcd_invert(1);
		else
			lcd_invert(0);
		lcd_drawTextXY(5*6,3,str);
		lcd_invert(0);
	}