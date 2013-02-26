/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "lcd_3310.h"
#include "btn.h"
#include "menu.h"
#include "global.h"
#include "Utils.h"
#include "pot.h"
#include "pwm.h"
#include "ee.h"
#include "buzzer.h"
/* Private defines -----------------------------------------------------------*/
#define RS_FIELD_RPM_MIN		0
#define RS_FIELD_DWELL_MIN	1
#define RS_FIELD_RPM_MAX		2
#define RS_FIELD_DWELL_MAX	3
/* Private function prototypes -----------------------------------------------*/
void menuSetupRamp_redraw(void);
void menuSetupRamp_btn(uint8_t state);
/* Private global variables -----------------------------------------------*/
uint8_t menuSetupRamp_firstRun=1,menuSetupRamp_edit=0,menuSetupRamp_editField=0;
uint8_t menuSetupRamp_displayChanged=0;

uint16_t menuSetupRamp_pwm_width=1000;

/* Private functions ---------------------------------------------------------*/


	/**
  * @brief  Redraws the screen.
  * @retval None
  */
	void menuSetupRamp_redraw(void){
		lcd_3310_drawTextXY(0,0,"RAMP: 1 2 3");
		lcd_3310_drawTextXY(0,2,"MIN  310  20 s");
		lcd_3310_drawTextXY(0,3,"MAX  2110 35 s");
		lcd_3310_drawTextXY(0,4,"RPM 2105");
		lcd_3310_drawTextXY(0,5,"PWM 1456 us");
	}
	
	/**
  * @brief  Draws the menu items in the top
	* @note		The selected item text is inverted
	* @note		If the ramp program is active (menuSetupRamp_started=0)
	*					none of the items is inverted
  * @retval None
  */
	void menuSetupRamp_drawMenuItems(void){
		uint8_t i,str[14];

			

		// Move LCD cursor to the first line
		lcd_3310_gotoXY(6*6,0);
		// Go trough all menu items
		for (i=0;i<RAMP_MODE_COUNT;i++){
			// If current item is selected and RAMP program is inactive
			if (i==mainConfig.rampCurrent)
				// invert the text
				lcd_3310_invert(1);
			else
				lcd_3310_invert(0);
			
			// convert integer to string
			itoa((int32_t)(i+1),&str);
			// draw on lcd
			lcd_3310_drawText(str);			
			// disable text inversion
			lcd_3310_invert(0);
			// if this is not the last item
			if (i!=RAMP_MODE_COUNT-1)
				// add space
				lcd_3310_drawText(" ");	
		}
	}
	
	/**
  * @brief  Draws the parameters of selected RAMP program
  * @retval None
  */
	void menuSetupRamp_drawParams(void){
		uint8_t str[14];
		static TrampConfig rampCfg;		

		// Calculate time elapsed since ramp action start [in 0.1seconds]
	//	timeElapsed=(uint16_t)(TIM1_cnt-_timeStarted)/5;
		
		// If elapsed time is shorter 
		//if (timeElapsed<5)
	//		return;
	//	_timeStarted=TIM1_cnt;	
		
		rampCfg=mainConfig.rampCfg[mainConfig.rampCurrent];
		// Clear symbols on LCD
		lcd_3310_drawTextXY(3*6,2,"          ");
		lcd_3310_drawTextXY(3*6,3,"          ");
		
		if ((menuSetupRamp_edit)&&(menuSetupRamp_editField==RS_FIELD_RPM_MIN))
			lcd_3310_invert(1);
		else
			lcd_3310_invert(0);
		// Display RPM min value
		itoa((int32_t)rampCfg.RPM_min,&str);
		lcd_3310_drawTextXY(4*6,2,str);
		
		if ((menuSetupRamp_edit)&&(menuSetupRamp_editField==RS_FIELD_DWELL_MIN))
			lcd_3310_invert(1);
		else
			lcd_3310_invert(0);
		// Display RPM min dwell time
		itoa((int32_t)rampCfg.min_dwell,&str);
		lcd_3310_drawTextXY(10*6,2,str);
		
		if ((menuSetupRamp_edit)&&(menuSetupRamp_editField==RS_FIELD_RPM_MAX))
			lcd_3310_invert(1);
		else
			lcd_3310_invert(0);
		// Display RPM max value
		itoa((int32_t)rampCfg.RPM_max,&str);
		lcd_3310_drawTextXY(4*6,3,str);

		if ((menuSetupRamp_edit)&&(menuSetupRamp_editField==RS_FIELD_DWELL_MAX))
			lcd_3310_invert(1);
		else
			lcd_3310_invert(0);
		// Display RPM max dwell time
		itoa((int32_t)rampCfg.max_dwell,&str);
		lcd_3310_drawTextXY(10*6,3,str);
		lcd_3310_invert(0);
	}
	
	/**
	* @brief  Initializes the menu and required peripherals
  * @retval None
  */
	void menuSetupRamp_Init(void){
			pot_init();		
			
		lcd_3310_clear();
		menuSetupRamp_redraw();
		menuSetupRamp_drawMenuItems();
		menuSetupRamp_drawParams();
		// Wait for enter button to be depressed
		while ((btn_getState()&btnEnter)>0)
			;
	}
	/**
	* @brief  Deinitializes the menu and used peripherals
  * @retval None
  */
	void menuSetupRamp_DeInit(void){
		pot_DeInit();
		PWM_outputDisable();
		menuSetupRamp_firstRun=1;
		ee_writeBuff((uint32_t)FLASH_DATA_START_PHYSICAL_ADDRESS,(uint8_t*)&mainConfig,sizeof(TmainConfig));
	}

	
	/**
	* @brief  Reads the state of buttons and executes associated actions
  * @retval None
  */
	void menuSetupRamp_buttons(void){
		uint8_t buttons;
		static Ttimer btnTimer={0,0};
		// Calculate the time elapsed since the button timer was started
		btnTimer.timeElapsed=(uint8_t)((TIM1_cnt&0xFF)-btnTimer.timeStart);	
		if (btnTimer.timeElapsed>10)// every 200ms(10*20ms)
		{
			btnTimer.timeStart=(TIM1_cnt&0xFF);

			// Read state of buttons
			buttons=btn_getState();
			if ((buttons>0)&&(menuSetupRamp_edit))
				menuSetupRamp_displayChanged=1;
			// If UP button is pressed
			if (((buttons&btnUp)>0)){
				if (!menuSetupRamp_edit){ 					
					if (mainConfig.rampCurrent<RAMP_MODE_COUNT-1){
						mainConfig.rampCurrent++;				
					//	menuSetupRamp_drawParams();
						menuSetupRamp_displayChanged=1;
						buzzer_beep();
					}
				/*	else{
						mainConfig.rampCurrent=0;	
					}*/
				}
				else
				{
						menuSetupRamp_btn(BTN_UP);						
				}
			}
			
			// If DOWN button is pressed
			if ((buttons&btnDown)>0){
				if (!menuSetupRamp_edit){ 
					if (mainConfig.rampCurrent>0){
						buzzer_beep();
						mainConfig.rampCurrent--;		
					//	menuSetupRamp_drawParams();
						menuSetupRamp_displayChanged=1;
					}	
				}				
				else
				{
						menuSetupRamp_btn(BTN_DOWN);
						
				}
			}
			
			// If ENTER button is pressed
			if (((buttons&btnEnter)>0)){
				buzzer_beep();
				if (!menuSetupRamp_edit){
					menuSetupRamp_edit=1;
				}
				else
				{
					if (menuSetupRamp_editField<RS_FIELD_DWELL_MAX)
						menuSetupRamp_editField++;
					else
						menuSetupRamp_editField=0;
						// Wait for enter button to be depressed
					while ((btn_getState()&btnEnter)>0)
						;
				}
			}	
			
			// If EXIT button is pressed
			if ((buttons&btnExit)>0){
				if (menuSetupRamp_edit){
					menuSetupRamp_edit=0;
				}
				else
				{
					menuSetupRamp_DeInit();
					menu=MENU_MAIN;
				}
			}	
		}
	}
	

	void menuSetupRamp_btn(uint8_t state){
		if (!menuSetupRamp_edit)
			return;
			
		switch(menuSetupRamp_editField){
			case RS_FIELD_RPM_MIN:
				
			break;
			
			case RS_FIELD_DWELL_MIN:
				if (state==BTN_UP){
					if (mainConfig.rampCfg[mainConfig.rampCurrent].min_dwell<RAMP_DWELL_MAX)
					{
						mainConfig.rampCfg[mainConfig.rampCurrent].min_dwell++;
						buzzer_beep();
					}
				}
				else
				{
					if (mainConfig.rampCfg[mainConfig.rampCurrent].min_dwell>RAMP_DWELL_MIN)
					{
						mainConfig.rampCfg[mainConfig.rampCurrent].min_dwell--;
						buzzer_beep();
					}
				}
			break;
			
			case RS_FIELD_RPM_MAX:		
			
			break;
			
			case RS_FIELD_DWELL_MAX:		
				if (state==BTN_UP){
					if (mainConfig.rampCfg[mainConfig.rampCurrent].max_dwell<RAMP_DWELL_MAX)
					{
						mainConfig.rampCfg[mainConfig.rampCurrent].max_dwell++;
						buzzer_beep();
					}
				}
				else
				{
					if (mainConfig.rampCfg[mainConfig.rampCurrent].max_dwell>RAMP_DWELL_MIN)
					{
						mainConfig.rampCfg[mainConfig.rampCurrent].max_dwell--;
						buzzer_beep();
					}
				}
			break;
		}
	}	
	
	
/* Public functions ---------------------------------------------------------*/
	/**
	* @brief  Menu callback procedure.
	* @note		This procedure must be executed continiously from the main thread
	* @param	_menuSetupRampMode: sets mode of the menu
	*         This parameter can be one of the following values:
	*					MENU_RAMP_SETUP:	RAMP parameters setup
	*					MENU_RAMP_NORMAL:	normal RAMP operation
  * @retval None
  */
	void menuSetupRamp(void){
		uint8_t str[14];
		static Ttimer rpmTimer={0,0};
		// Check if the function is called for the first time
		if (menuSetupRamp_firstRun)
		{
			// Initialize
			menuSetupRamp_Init();
			// clear menuSetupRamp_firstRun variable
			menuSetupRamp_firstRun=0;
		}	
		// Read the state of buttons
		// And react to changes
		menuSetupRamp_buttons();
		
		
		if (menuSetupRamp_displayChanged){
			// Draw menu items on LCD
			menuSetupRamp_drawMenuItems();		
			menuSetupRamp_drawParams();
			menuSetupRamp_displayChanged=0;
		}
				
		// Calculate the PWM width. The width step is 0.5us, 
		// thus the required number of us is multiplied by two
		menuSetupRamp_pwm_width=1000+Conversion_Value;
				
		if ((menuSetupRamp_edit)&&
			((menuSetupRamp_editField==RS_FIELD_RPM_MIN)||(menuSetupRamp_editField==RS_FIELD_RPM_MAX))){
			PWM_outputEnable();	
			
			if (((TIM1_cnt&0xFF)-rpmTimer.timeStart)>50)
			{
				// Store current time
				rpmTimer.timeStart=(TIM1_cnt)&0xFF;
				menuSetupRamp_displayChanged=1;			
			}
			// limit PWM width to PWM_WIDTH_MAX value
			if (menuSetupRamp_pwm_width>PWM_WIDTH_MAX)
				menuSetupRamp_pwm_width=PWM_WIDTH_MAX;
			// Set PWM width
			PWM_setCH1Duty(menuSetupRamp_pwm_width*2);
		}
		else
			PWM_outputDisable();
			
		if (menuSetupRamp_edit){
			if (menuSetupRamp_editField==RS_FIELD_RPM_MIN){
				mainConfig.rampCfg[mainConfig.rampCurrent].RPM_min=rpm;
				mainConfig.rampCfg[mainConfig.rampCurrent].PWM_min=menuSetupRamp_pwm_width;
			}	
			
			if (menuSetupRamp_editField==RS_FIELD_RPM_MAX){
				mainConfig.rampCfg[mainConfig.rampCurrent].RPM_max=rpm;
				mainConfig.rampCfg[mainConfig.rampCurrent].PWM_max=menuSetupRamp_pwm_width;
			}	
		}
			
		
			
		// Display RPM on the screen
		menu_displayRPM(4*6,4);
		
		//display pwm width in us
		itoa((int32_t)menuSetupRamp_pwm_width,&str);
		lcd_3310_drawTextXY(4*6,5,str);
	}