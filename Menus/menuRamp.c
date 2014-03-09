/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "btn.h"
#include "menu.h"
#include "global.h"
#include "Utils.h"
#include "buzzer.h"
#include "pwm.h"
/* Private defines -----------------------------------------------------------*/
#define MENU_RAMP_STATE_INACTIVE	0
#define MENU_RAMP_STATE_MIN				1
#define MENU_RAMP_STATE_MAX				2
/* Private function prototypes -----------------------------------------------*/
void menuRamp_redraw(void);

/* Private global variables -----------------------------------------------*/
uint8_t menuRamp_firstRun=1,menuRamp_state=MENU_RAMP_STATE_INACTIVE;
uint8_t menuRamp_RampStagetimeLeft=52;
uint16_t menuRamp_pwm_width=1000;
TrampConfig rampCfg={200,3000,10,30};
uint8_t menuRampMode=0;
/* Private functions ---------------------------------------------------------*/
	/**
  * @brief  Redraws the screen.
  * @retval None
  */
	void menuRamp_redraw(void){
		lcd_drawTextXY(0,0,"RAMP: 1 2 3");
		lcd_drawTextXY(0,2,"MIN  310  20 s");
		lcd_drawTextXY(0,3,"MAX  2110 35 s");
		lcd_drawTextXY(0,4,"RPM 2105");
		lcd_drawTextXY(0,5,"PWM 1456 us");
	}
	
	/**
  * @brief  Draws the menu items in the top
	* @note		The selected item text is inverted
	* @note		If the ramp program is active (menuRamp_state=0)
	*					none of the items is inverted
  * @retval None
  */
	void menuRamp_drawMenuItems(void){
		static uint16_t blinkTimer=0;
		static uint8_t blinkState=0;
		uint8_t i,str[14];
		// Move LCD cursor to the first line
		lcd_gotoXY(6*6,0);
		// Go trough all menu items
		for (i=0;i<RAMP_MODE_COUNT;i++){
			// If current item is selected //and RAMP program is inactive
			if ((i==mainConfig.rampCurrent))//&&(menuRamp_state==MENU_RAMP_STATE_INACTIVE))
				// invert the text
				lcd_invert(1);
			else
				lcd_invert(0);			
			// convert integer to string
			itoa((int32_t)(i+1),&str);
			// draw on lcd
			lcd_drawText(str);			
			// disable text inversion
			lcd_invert(0);
			// if this is not the last item
			if (i!=RAMP_MODE_COUNT-1)
				// add space
				lcd_drawText(" ");	
		}
		// Check if RAMP program is started
		if (menuRamp_state!=MENU_RAMP_STATE_INACTIVE){
			// Chech if 0.5s has passed since the last time
			if (((uint16_t)(TIM1_cnt-blinkTimer))>25){
				blinkTimer=TIM1_cnt;
				// What is the display state at the moment?
				if (blinkState){
						// Text MIN/MAX is shown
							lcd_drawTextXY(0,2,"MIN");
							lcd_drawTextXY(0,3,"MAX");
					blinkState=0;				
				}
				else{
					// Time left for the step is shown
					if (menuRamp_state==MENU_RAMP_STATE_MIN){
						lcd_drawTextXY(0,2,"   ");
						//display time left
						itoa((int32_t)menuRamp_RampStagetimeLeft,&str);
						lcd_drawTextXY(0,2,str);	
					}
					
					if (menuRamp_state==MENU_RAMP_STATE_MAX){
						lcd_drawTextXY(0,3,"   ");
						//display time left
						itoa((int32_t)menuRamp_RampStagetimeLeft,&str);
						lcd_drawTextXY(0,3,str);	
					}
					blinkState=1;
				}
			}
		}
		else
		{
			// Program not started, draw the text MIN/MAX normally
			lcd_invert(0);
			lcd_drawTextXY(0,2,"MIN");
			lcd_drawTextXY(0,3,"MAX");	
		}
		// Make sure further text drawing on the screen will not be inverted
		lcd_invert(0);
	}
	
	/**
  * @brief  Draws the parameters of selected RAMP program
  * @retval None
  */
	void menuRamp_drawParams(void){
		uint8_t str[14];
		TrampConfig rampCfg;
		rampCfg=mainConfig.rampCfg[mainConfig.rampCurrent];
		// Clear symbols on LCD
		lcd_drawTextXY(3*6,2,"          ");
		lcd_drawTextXY(3*6,3,"          ");
		// Display RPM min value
		itoa((int32_t)rampCfg.RPM_min,&str);
		lcd_drawTextXY(5*6,2,str);
		// Display RPM min dwell time
		itoa((int32_t)rampCfg.min_dwell,&str);
		lcd_drawTextXY(10*6,2,str);
		// Display RPM max value
		itoa((int32_t)rampCfg.RPM_max,&str);
		lcd_drawTextXY(5*6,3,str);
		// Display RPM max dwell time
		itoa((int32_t)rampCfg.max_dwell,&str);
		lcd_drawTextXY(10*6,3,str);		
	}
	
	/**
	* @brief  Initializes the menu and required peripherals
  * @retval None
  */
	void menuRamp_Init(void){
		#ifdef _ARM_ESC_ON_RAMP	
		uint8_t tmp=0;
		#endif
		lcd_clear();
		menuRamp_redraw();
		menuRamp_drawMenuItems(); 
		menuRamp_drawParams();
		/*If ESC arming on startup required*/					
		#ifdef _ARM_ESC_ON_RAMP		 
				// Enable PWM output
				PWM_outputEnable();			
				// Set PWM width to 1000us
				PWM_setAllChannelDuty(1000*2);		
			// Wait for 2 seconds (100*20ms)
			tmp=TIM1_cnt&0xFF;
			while (((uint8_t)((TIM1_cnt&0xFF)-tmp))<100)
				;				
			
			#ifdef PUMP_CONTROL_ENABLED
				// Set S1 PWM width to 0
				S1_TimSetCompare(0);
			#else
				PWM_outputDisable();
			#endif
		#endif					

		
		// Wait for enter button to be depressed
		while ((btn_getState()&btnEnter)>0)
			;
	}
	
	/**
	* @brief  Deinitializes the menu and used peripherals
  * @retval None
  */
	void menuRamp_DeInit(void){
		menuRamp_firstRun=1;
	}

	
	/**
	* @brief  Reads the state of buttons and executes associated actions
  * @retval None
  */
	void menuRamp_buttons(void){
		uint8_t buttons;
		static Ttimer btnTimer={0,0};
		// Calculate the time elapsed since the button timer was started
		btnTimer.timeElapsed=(uint8_t)((TIM1_cnt&0xFF)-btnTimer.timeStart);	
		if (btnTimer.timeElapsed>10)// every 200ms(10*20ms)
		{
			btnTimer.timeStart=(TIM1_cnt&0xFF);

			// Read state of buttons
			buttons=btn_getState();
			if (buttons>0)
				buzzer_beep();
			// If UP button is pressed
			if (((buttons&btnUp)>0)&&(menuRamp_state==MENU_RAMP_STATE_INACTIVE)){
				if (mainConfig.rampCurrent<RAMP_MODE_COUNT-1){
					mainConfig.rampCurrent++;				
					menuRamp_drawParams();				
				}
			}
			
			// If DOWN button is pressed
			if ((buttons&btnDown)>0){
				if (mainConfig.rampCurrent>0){
					mainConfig.rampCurrent--;		
					menuRamp_drawParams();				
				}					
			}
			
			// If ENTER button is pressed
			if (((buttons&btnEnter)>0)&&(menuRamp_state==MENU_RAMP_STATE_INACTIVE)){
				if (menuRamp_state==MENU_RAMP_STATE_INACTIVE)
					menuRamp_state=MENU_RAMP_STATE_MIN;
			}	
			
			// If EXIT button is pressed
			if ((buttons&btnExit)>0){
				if (menuRamp_state==MENU_RAMP_STATE_INACTIVE){
					menuRamp_DeInit();
					menu=MENU_MAIN;
				}
				else
					menuRamp_state=MENU_RAMP_STATE_INACTIVE;
			}	
		}
	}
	
	
	/**
	* @brief  RAMP program execution procedure
	* @note		This procedure executes the RAMP program
  * @retval None
  */
	void menuRamp_action(void){
		static uint16_t timeStarted=0;
		static uint8_t first=1,timeElapsed=0,tmin=0,tmax=0;
		// Check if ramp mode is started
		if (menuRamp_state==MENU_RAMP_STATE_INACTIVE){
			// Set default values
			menuRamp_pwm_width=1000;
	//		menuRamp_state=MENU_RAMP_STATE_INACTIVE;
			first=1;
			#ifdef PUMP_CONTROL_ENABLED
				// Set S1 PWM width to 0
				S1_TimSetCompare(0);
			#else
				PWM_outputDisable();
			#endif
			// Exit the function
			return;
		}
		// Is it the first cycle of ramp action?
		if (first==1){
			// Mark the time it was started
			timeStarted=TIM1_cnt;
			PWM_outputEnable();
			// Read min and max dwell times to temporary variables
			tmin=mainConfig.rampCfg[mainConfig.rampCurrent].min_dwell;
			tmax=mainConfig.rampCfg[mainConfig.rampCurrent].max_dwell;

			// Clear first cycle flag
			first=0;
		}

		// Calculate time elapsed since ramp action start [in seconds]
		timeElapsed=(uint16_t)(TIM1_cnt-timeStarted)/50;		
		// If elapsed time is shorter than dwell time for min
		if (timeElapsed<tmin){
			// Set PWM width according to RPM min value
			menuRamp_pwm_width=mainConfig.rampCfg[mainConfig.rampCurrent].PWM_min;
			if (menuRamp_state!=MENU_RAMP_STATE_MIN)
				menuRamp_state=MENU_RAMP_STATE_MIN;
				menuRamp_RampStagetimeLeft=tmin-timeElapsed;
		}	// If elapsed time is more than min dwell time and less
			// than min+max dwell times
		else if (timeElapsed<(tmin+tmax)){
			if (menuRamp_state!=MENU_RAMP_STATE_MAX)
				menuRamp_state=MENU_RAMP_STATE_MAX;
			// Set PWM width according to RPM max value
			menuRamp_pwm_width=mainConfig.rampCfg[mainConfig.rampCurrent].PWM_max;
			menuRamp_RampStagetimeLeft=(tmin+tmax)-timeElapsed;
		}
		else{
			// Ramp program is done. 
			// Set default values and disable PWM
			menuRamp_pwm_width=1000;
			menuRamp_state=MENU_RAMP_STATE_INACTIVE;
			first=1;
			#ifdef PUMP_CONTROL_ENABLED
				// Set S1 PWM width to 0
				S1_TimSetCompare(0);
			#else
				PWM_outputDisable();
			#endif
			return;
		}
				
		/* Set PWM width. Width step is 0.5us, thus the value in
		   us is multiplied by two*/
		#ifdef PUMP_CONTROL_ENABLED
				S1_TimSetCompare(menuRamp_pwm_width*2);	//S1
		#else			
			// Set PWM width
			PWM_setAllChannelDuty(menuRamp_pwm_width*2);
		#endif				 
		
	}
	
/* Public functions ---------------------------------------------------------*/
	/**
	* @brief  Menu callback procedure.
	* @note		This procedure must be executed continiously from the main thread
	* @param	_menuRampMode: sets mode of the menu
	*         This parameter can be one of the following values:
	*					MENU_RAMP_SETUP:	RAMP parameters setup
	*					MENU_RAMP_NORMAL:	normal RAMP operation
  * @retval None
  */
	void menuRamp(void){
		uint8_t str[14];
		// Check if the function is called for the first time
		if (menuRamp_firstRun)
		{
			// Initialize
			menuRamp_Init();
			// clear menuRamp_firstRun variable
			menuRamp_firstRun=0;
		}	
		// Read the state of buttons
		// And react to changes
		menuRamp_buttons();
				
		// Take the actions needed
		menuRamp_action();
		
		// Draw menu items on LCD
		menuRamp_drawMenuItems();
		
		// Display RPM on the screen
		menu_displayRPM(4*6,4);
		
		//display pwm width in us
		itoa((int32_t)menuRamp_pwm_width,&str);
		lcd_drawTextXY(4*6,5,str);
	}