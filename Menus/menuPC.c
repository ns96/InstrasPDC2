/* Includes ------------------------------------------------------------------*/
#include "global.h"	

#include "btn.h"
#include "menu.h"
#include "Utils.h" 
#include "pot.h"
#include "pwm.h"
#include "buzzer.h"

/* Private defines -----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
	void menuPC_redraw(void);

/* Private global variables -----------------------------------------------*/

	// Variable for determing if the menu task 
	// is called for the first time
	uint8_t menuPC_firstRun=1,menuPC_outputEnable=0;
	uint16_t pwm_S1=0,pwm_S2=0;


/* Private functions ---------------------------------------------------------*/
	/**	Redraws the screen completely
	*
	*/
	void menuPC_redraw(void){//              "
		lcd_drawTextXY(0,0,"    PC mode   ");
		lcd_drawTextXY(0,2,"RPM ");
		lcd_drawTextXY(0,3,"PWM1 0000 us");
		lcd_drawTextXY(0,4,"PWM2 0000 us");
	}

	/**	Initializes  Menu
	*/
	void menuPC_Init(void){	
		lcd_clear();
		menuPC_redraw();
		pwm_S1=0;
		pwm_S2=0;
		PWM_outputEnable();

		// Wait for enter button to be depressed
		while ((btn_getState()&btnEnter)>0)
			;
	}
	/**	Deinitializes Main Menu
	*/
	void menuPC_DeInit(void){
		PWM_outputDisable();
		menuPC_firstRun=1;
	}

/* Public functions ---------------------------------------------------------*/
	void menuPC(void){
		uint8_t buttons,str[14];
		static Ttimer btnTimer={0,0};
		// Check if the function is called for the first time
		if (menuPC_firstRun)
		{
			// Initialize
			menuPC_Init();
			// Clear menuPC_firstRun variable
			menuPC_firstRun=0;
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
				/*	menuPC_DeInit();
					menu=MENU_MAIN;*/
			}	
			
				// If ENTER button is pressed
			if ((buttons&btnEnter)>0){				
					buzzer_beepA(3200,10);
			}
			
			if ((buttons&btnUp)>0){
			}
			if ((buttons&btnDown)>0){
			}
		}
/////////////////////////////
		if (pwm_S1>PWM_WIDTH_MAX)
			pwm_S1=PWM_WIDTH_MAX;

		if (pwm_S2>PWM_WIDTH_MAX)
			pwm_S2=PWM_WIDTH_MAX;
		
			S1_TimSetCompare(pwm_S1*2);
			S2_TimSetCompare(pwm_S2*2);
/////////////////////////////			
			//display pwm width in us
			itoa(pwm_S1,(char *)&str);
			lcd_drawTextXY(9*6,3," ");
			if (pwm_S1==0)
				lcd_drawTextXY(5*6,3,"0000");
			else
			lcd_drawTextXY(5*6,3,str);

			//display pwm width in us
			itoa(pwm_S2,(char *)&str);
			lcd_drawTextXY(9*6,4," ");
			if (pwm_S2==0)
				lcd_drawTextXY(5*6,4,"0000");
			else			
			lcd_drawTextXY(5*6,4,str);
			
			menu_displayRPM(5*6,2);

	}