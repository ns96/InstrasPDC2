/* Includes ------------------------------------------------------------------*/
	#include "stm8s.h"
	#include "global.h"	
	#include "btn.h"
	#include "pwm.h"	
	#include "menu.h"
	#include "buzzer.h"
/* Private defines -----------------------------------------------------------*/
	#define SEL_ANALOG	1
	#define SEL_DIGITAL	2
	#define SEL_RAMP		3
	#define SEL_SETUP		4

/* Private function prototypes -----------------------------------------------*/
	void mainMenu_redraw(void);
	void select(uint8_t sel);

/* Private global variables -----------------------------------------------*/
	/* Variable for determing if the menu task 
	 is called for the first time*/
	uint8_t firstRun=1;
	
	// Variables for storing the mode sellection
	uint8_t selection=SEL_ANALOG,selection_old=SEL_ANALOG;

/* Private functions ---------------------------------------------------------*/
	/**	Redraws the menu screen completely
	*
	*/
	void mainMenu_redraw(void){
		lcd_drawTextXY(0,0,"Select Mode:");
		lcd_drawTextXY(10,2,"ANALOG");
		lcd_drawTextXY(10,3,"DIGITAL");
		lcd_drawTextXY(10,4,"RAMP");
		lcd_drawTextXY(10,5,"SETUP");	
	}

	/**	Draws a tick in front of selected item
	* and clears previous ticks
	*/
	void select(uint8_t sel){
		uint8_t i;
		// Go trough all menu options
		for (i=SEL_ANALOG;i<=SEL_SETUP;i++){
			// If current menu option is selected
			if (i==sel)	
				// Write the tick symbol
				lcd_drawTextXY(2,2+i-SEL_ANALOG,"*");	
			else
				// Clear the tick symbol
				lcd_drawTextXY(2,2+i-SEL_ANALOG," ");
		}
	}

	/**	Initializes Main Menu
	*/
	void mainMenu_Init(void){
		selection_old=selection;
		lcd_clear();
		mainMenu_redraw();
		select(selection);
			/*If PWM output required*/					
		#ifdef _ENABLE_PWM_OUTPUT_ON_MAIN_MENU		
				// Enable PWM output
				PWM_outputEnable();			
				// Set PWM width to 1000us
				PWM_setAllChannelDuty(1000*2);		
		#endif		
	}
	
	/**	Deinitializes Main Menu
	*/
	void mainMenu_DeInit(void){
		firstRun=1;	
		#ifdef PUMP_CONTROL_ENABLED
			// Set S1 PWM width to 0
			S1_TimSetCompare(0);
		#else
			PWM_outputDisable();
		#endif			
	}


/* Public functions ---------------------------------------------------------*/
	void mainMenu(void){
		uint8_t buttons;
		static Ttimer btnTimer={0,0};
		// Check if the function is colled for the first time
		if (firstRun)
		{
			// Initialize
			mainMenu_Init();
			// clear firstRun variable
			firstRun=0;
		}	
		
		// Check the time elapsed sinced last read of button state
		// If it is more than 200ms (10*20ms)
		if (((TIM1_cnt&0xFF)-btnTimer.timeStart)>10)
		{
			// Store current time
			btnTimer.timeStart=TIM1_cnt&0xFF;
			// Read state of buttons
			buttons=btn_getState();
			if (buttons>0)
				buzzer_beep();
			// If UP button is pressed
			if ((buttons&btnUp)>0){
				if (selection>SEL_ANALOG){
					selection--;
				}
				
			}
			
			// If DOWN button is pressed
			if ((buttons&btnDown)>0){
				if (selection<SEL_SETUP){
					selection++;
				}
				
			}
			
			// If ENTER button is pressed
			if ((buttons&btnEnter)>0){
				mainMenu_DeInit();
				menu=selection;
			}	
	}
			
		//If selection was changed
		if (selection!=selection_old){
			//redraw the tick symbol
			select(selection);
			//store old selection value
			selection_old=selection;
		}	
	}