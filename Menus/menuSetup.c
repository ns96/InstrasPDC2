/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "lcd_3310.h"
#include "btn.h"
#include "menu.h"
#include "global.h"
#include "Utils.h"
#include "ee.h"
#include "buzzer.h"
/* Private defines -----------------------------------------------------------*/
	#define SEL_SETP	1
	#define SEL_START	2
	#define SEL_BL		3
	#define SEL_RAMP	4
	
	//								"xxxxxx  yyzzzzz"
	#define STR_SET   "SET P#"
	#define STR_START "START"
	#define STR_BL    "BL"
	#define STR_RAMP  "RAMP"
	


/* Private function prototypes -----------------------------------------------*/
void menuSetup_redraw(void);
void btn(uint8_t state);
/* Private global variables -----------------------------------------------*/
uint8_t menuSetup_firstRun=1,menuSetup_selection=SEL_SETP,menuSetup_displayChanged=0;
uint8_t menuNames[4][7]={STR_SET,STR_START,STR_BL,STR_RAMP};
uint8_t editing=0;
/* Private functions ---------------------------------------------------------*/
void menuSetup_redraw(void){
	lcd_3310_drawTextXY(0,0,"SETUP:");/*
	lcd_3310_drawTextXY(0,2,"SET P# 2");
	lcd_3310_drawTextXY(0,3,"START  DIGITAL");
	lcd_3310_drawTextXY(0,4,"BL     ON");
	lcd_3310_drawTextXY(0,5,"RAMP");*/
}

	/**	Inverts selected item
	* and draws other items
	*/
	void menuSetup_select(uint8_t sel){
		uint8_t i;
#ifdef SETUP_MENU_INVERT_SELECTED
		// Go trough all menu options
		for (i=SEL_SETP;i<=SEL_RAMP;i++){
			lcd_3310_invert(0);
			lcd_3310_drawTextXY(0,2+i-SEL_SETP,"      ");
			// If current menu option is selected
			if (i==sel)	
				// invert the text
				lcd_3310_invert(1);
			else				
				// invert the text
				lcd_3310_invert(0);
			lcd_3310_drawTextXY(0,2+i-SEL_SETP,menuNames[i-SEL_SETP]);
		}		
		lcd_3310_invert(0);
	}
#else
		// Go trough all menu options
		for (i=SEL_SETP;i<=SEL_RAMP;i++){
			lcd_3310_invert(0);
			lcd_3310_drawTextXY(1,2+i-SEL_SETP,"      ");
			// If current menu option is selected
			if (i==sel)	
				lcd_3310_drawTextXY(0,2+i-SEL_SETP,"*");
			else				
				lcd_3310_drawTextXY(0,2+i-SEL_SETP," ");

			lcd_3310_drawText(menuNames[i-SEL_SETP]);
		}		
		lcd_3310_invert(0);
	}
#endif
	
		/**	Inverts selected item
	* and draws other items
	*/
	void menuSetup_drawParams(void){
		uint8_t str[14];
		
		lcd_3310_invert(0);
		lcd_3310_drawTextXY(7*6,4,"   ");
		if ((editing)&&(menuSetup_selection==SEL_BL))
			lcd_3310_invert(1);
		else
			lcd_3310_invert(0);
		switch (mainConfig.backLight){
			case BACKLIGHT_HIGH:
			case BACKLIGHT_LOW:
				lcd_3310_drawTextXY(7*6,4,"ON");
			break;
			default:
				lcd_3310_drawTextXY(7*6,4,"OFF");
			break;
		}
		
		// Display P#
		lcd_3310_invert(0);
		lcd_3310_drawTextXY(7*6,2,"  ");
		if ((editing)&&(menuSetup_selection==SEL_SETP))
			lcd_3310_invert(1);
		else
			lcd_3310_invert(0);
		itoa((int32_t)mainConfig.numReflectors,&str);			
		lcd_3310_drawTextXY(7*6,2,str);
		
		lcd_3310_invert(0);
		lcd_3310_drawTextXY(7*6,3,"       ");
		if ((editing)&&(menuSetup_selection==SEL_START))
			lcd_3310_invert(1);
		else
			lcd_3310_invert(0);
		
			switch (mainConfig.startupMenu){
			case STARTUP_MENU_NONE:
				lcd_3310_drawTextXY(7*6,3,"NONE");
			break;
			
			case STARTUP_MENU_RAMP:
				lcd_3310_drawTextXY(7*6,3,"RAMP");
			break;
			
			case STARTUP_MENU_DIGITAL:
				lcd_3310_drawTextXY(7*6,3,"DIGITAL");
			break;
			
			case STARTUP_MENU_ANALOG:
				lcd_3310_drawTextXY(7*6,3,"ANALOG");
			break;
			
			default:
				lcd_3310_drawTextXY(7*6,3,"-------");
			break;
		}

	}
/**	Initializes  Menu
*/
void menuSetup_Init(void){

	lcd_3310_clear();
	menuSetup_redraw();
	menuSetup_drawParams();
	menuSetup_select(menuSetup_selection);
	// Wait for enter button to be depressed
	while ((btn_getState()&btnEnter)>0)
		;
}
/**	Deinitializes Main Menu
*/
void menuSetup_DeInit(void){
	menuSetup_firstRun=1;
	ee_writeBuff((uint32_t)FLASH_DATA_START_PHYSICAL_ADDRESS,(uint8_t*)&mainConfig,sizeof(TmainConfig));
}
void menuSetup_buttons(void){
	uint8_t buttons;
	static Ttimer btnTimer={0,0};
	// Check the time elapsed sinced last read of button state
		// If it is more than 200ms (10*20ms)
		if (((TIM1_cnt&0xFF)-btnTimer.timeStart)>10)
		{
			// Store current time
			btnTimer.timeStart=TIM1_cnt&0xFF;	
			// Read state of buttons
			buttons=btn_getState();
			if (buttons>0)
				menuSetup_displayChanged=1;
		// If UP button is pressed
			if ((buttons&btnUp)>0){		
				buzzer_beep();
				if (!editing){			
					if (menuSetup_selection>SEL_SETP){
						menuSetup_selection--;}
				}
				else{
					btn(BTN_UP);
				}
			}
			
			// If DOWN button is pressed
			if ((buttons&btnDown)>0){
				buzzer_beep();
				if (!editing){
					if (menuSetup_selection<SEL_RAMP){
						menuSetup_selection++;}
				}
				else{
					btn(BTN_DOWN);
				}
			}
	
			// If ENTER button is pressed
			if ((buttons&btnEnter)>0){
				buzzer_beep();
				if (menuSetup_selection!=SEL_RAMP)
					editing=1;
				else
				{
					menuSetup_DeInit();
					menu=MENU_SETUPRAMP;
				}
			}	
			
			// If EXIT button is pressed
			if ((buttons&btnExit)>0){
				buzzer_beep();
				if (editing)
				{
					editing=0;
				}
				else
				{
					menuSetup_DeInit();
					menu=MENU_MAIN;
				}
			}	
		}	
}


void btn(uint8_t state){
	if (!editing)
		return;
	switch(menuSetup_selection){
		case SEL_SETP:
			if (state==BTN_UP){
				if (mainConfig.numReflectors<NUM_REFLECTORS_MAX)
					mainConfig.numReflectors++;
			}
			else{
				if (mainConfig.numReflectors>1)
					mainConfig.numReflectors--;
			}
		break;
		case SEL_START:
			if (state==BTN_UP){
				if (mainConfig.startupMenu<STARTUP_MENU_RAMP)
					mainConfig.startupMenu++;
			}
			else{
				if (mainConfig.startupMenu>STARTUP_MENU_NONE)
					mainConfig.startupMenu--;
			}		
		break;
		case SEL_BL:		
			if (state==BTN_UP){
				mainConfig.backLight=BACKLIGHT_HIGH;
			}
			else{
				mainConfig.backLight=BACKLIGHT_OFF;
			}
		break;
	}
}


/* Public functions ---------------------------------------------------------*/
void menuSetup(void){
	
	// Check if the function is colled for the first time
	if (menuSetup_firstRun)
	{
		// Initialize
		menuSetup_Init();
		// clear menuSetup_firstRun variable
		menuSetup_firstRun=0;
	}	
	menuSetup_buttons();
	
	if (menuSetup_displayChanged){
		menuSetup_drawParams();
		menuSetup_select(menuSetup_selection);
		menuSetup_displayChanged=0;
	}
}