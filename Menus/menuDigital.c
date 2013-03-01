/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "lcd_3310.h"
#include "btn.h"
#include "menu.h"
#include "global.h"
#include "Utils.h"
#include "pwm.h"
#include "buzzer.h"

/* Private defines -----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
	void menuDigital_redraw(void);

/* Private global variables -----------------------------------------------*/
	/* Variable for determing if the menu task 
	 is called for the first time*/
	uint8_t menuDigital_firstRun=1,menuDigital_outputEnable=0;

/* Private functions ---------------------------------------------------------*/
	/**	Redraws the menu screen completely
	*
	*/
	void menuDigital_redraw(void){
		/*Since the display can accomodate only 14 characters,  
		"Digital Control" would exceed the limits, thus
		the space between words is set 2pixels*/
		lcd_3310_drawTextXY(0,0,"Digital");
		// Push the word "Control" by 7 character widths + 2px
		lcd_3310_drawTextXY(7*6+2,0,"Control");	
		lcd_3310_drawTextXY(0,2,"RPM        ");
		lcd_3310_drawTextXY(0,3,"PWM      us");
		lcd_3310_drawTextXY(0,4,"INC:");	
		lcd_3310_drawTextXY(0,5,"1 2 4 10 100");	
	}

	/**	Draws the increment step selection
	* on the last line. Selected increment step
	* is inverted.
	*/
	void menuDigital_drawStep(void){
		uint8_t i,str[14];
		// Move LCD cursor to the last line
		lcd_3310_gotoXY(0,5);
		// Go trough all inc. step options
		for (i=0;i<PWM_INC_COUNT;i++){
			itoa((int32_t)pwm_inc_array[i],&str);
			// If current step is the step selected
			if (i==mainConfig.PWMincIndex)
				// invert the text
				lcd_3310_invert(1);
			else
				lcd_3310_invert(0);
			// draw the text
			lcd_3310_drawText(str);			
			// disable inversion
			lcd_3310_invert(0);
			// if this is not the last item
			if (i!=PWM_INC_COUNT-1)
				// add space
				lcd_3310_drawText(" ");	
		}
	}
	/**	Initializes  Menu
	*/
	void menuDigital_Init(void){
		PWM_setCH1Duty(1000);
		lcd_3310_clear();
		menuDigital_redraw();
		menuDigital_drawStep();
		// Wait for enter button to be depressed
		while ((btn_getState()&btnEnter)>0)
			;
	}
	/**	Deinitializes Main Menu
	*/
	void menuDigital_DeInit(void){
		PWM_outputDisable();
		menuDigital_outputEnable=0;
		menuDigital_firstRun=1;
	}

/* Public functions ---------------------------------------------------------*/
	void menuDigital(void){
		uint8_t buttons,str[14],tmp;
		static Ttimer btnTimer={0,0};
		static uint16_t pwm_width=1000;	
		static uint8_t pauseState=0;
		static uint16_t pauseTimer=0;
		
		// Check if the function is called for the first time
		if (menuDigital_firstRun)
		{
			pwm_width=1000;
			// Initialize
			menuDigital_Init();
			// clear menuDigital_firstRun variable
			menuDigital_firstRun=0;
		}	
		
		// Calculate the time elapsed since the button timer was started
		tmp=TIM1_cnt&0xFF;
		btnTimer.timeElapsed=(uint8_t)(tmp-btnTimer.timeStart);	
		if (btnTimer.timeElapsed>10)// every 200ms(10*20ms)
		{
			btnTimer.timeStart=tmp;
			// Read state of buttons
			buttons=btn_getState();
			if (buttons>0)
				buzzer_beep();
			menuDigital_drawStep();
			// If UP button is pressed
			if ((buttons&btnUp)>0){
					if (pwm_width+pwm_inc_array[mainConfig.PWMincIndex]<PWM_WIDTH_MAX)
						pwm_width+=pwm_inc_array[mainConfig.PWMincIndex];
					else
						pwm_width=PWM_WIDTH_MAX;
			}
			
			// If DOWN button is pressed
			if ((buttons&btnDown)>0){
					if (pwm_width-pwm_inc_array[mainConfig.PWMincIndex]>PWM_WIDTH_MIN)
						pwm_width-=pwm_inc_array[mainConfig.PWMincIndex];
					else
						pwm_width=PWM_WIDTH_MIN;
			}
			
			// If ENTER button is pressed
			if ((buttons&btnEnter)>0){
				if (!menuDigital_outputEnable){
					menuDigital_outputEnable=1;
					PWM_outputEnable();
				}
				else
				{				
					if (mainConfig.PWMincIndex<(PWM_INC_COUNT-1)){
						mainConfig.PWMincIndex++;
					}
					else
						mainConfig.PWMincIndex=0;
				}
			}	
			
			// If EXIT button is pressed
			if ((buttons&btnExit)>0){			
					if (menuDigital_outputEnable){
					menuDigital_outputEnable=0;
					PWM_outputDisable();
				}
				else{
					menuDigital_DeInit();
					menu=MENU_MAIN;
				}	
			}	
		}
		/*	
		if (menuDigital_outputEnable){
			menu_displayRPM(4*6,2);
			lcd_3310_drawText(" ");
		}
		else
			lcd_3310_drawTextXY(4*6,2,"PAUSE");*/
			
		if ((menuDigital_outputEnable)||(!pauseState)){
			menu_displayRPM(4*6,2);
		}
		
		if (!menuDigital_outputEnable){
			if (((uint16_t)(TIM1_cnt-pauseTimer))>50){
				pauseTimer=TIM1_cnt;
				if (pauseState)
					pauseState=0;
				else{
					pauseState=1;
					lcd_3310_drawTextXY(4*6,2,"PAUSE     ");
				}
			}
		}	
			
			
		/* Set PWM width. Width step is 0.5us, thus the value in
		   us is multiplied by two*/
		PWM_setCH1Duty(pwm_width*2);
		
	
		// Display PWM width
		itoa((int32_t)pwm_width,&str);
		lcd_3310_drawTextXY(4*6,3,str);
		
	}