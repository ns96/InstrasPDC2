/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  Vaidas Zakarka
  * @version V1.0.0
  * @date    02-February-2013
  * @brief   Main program body
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 ElectronicsWorkshop.eu</center></h2>
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
	#include "stm8s.h"
	#include "board_stv307.h"
	#include "lcd_3310.h"
	#include "logo.h"
	#include "btn.h"
	#include "menu.h"
	#include "rpm.h"
	#include "pwm.h"
	#include "global.h"
	#include "ee.h"
	#include "buzzer.h"
	#include "menu.h"
	
/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
	volatile uint16_t Conversion_Value = 0;
	uint16_t rpm=0,rpm_p=0;
	volatile uint16_t TIM1_cnt=0;
	uint8_t menu=MENU_MAIN;
	TmainConfig mainConfig;
	int test;
	const uint8_t pwm_inc_array[PWM_INC_COUNT]={PWM_INC_VALUES};
	uint8_t t[10];

/* Private functions ---------------------------------------------------------*/
	/**
	* @brief  Main initialization. Initializes all peripherals
	* and modules.
	* @param  None
	* @retval None
	*/
	void main_init(void){
		//  LCD initialization structure
		lcd_3310_pinConfig lcdPinCfg={LCD_RST_PIN,LCD_RST_PORT,
																LCD_CE_PIN,LCD_CE_PORT,
																LCD_DC_PIN,LCD_DC_PORT,
																LCD_MOSI_PIN,LCD_MOSI_PORT,
																LCD_SCK_PIN,LCD_SCK_PORT};
		// Buttons initialization structure											
		Tbtn_pinConfig		btnPinCfg={	BTN_ENTER_PIN,BTN_ENTER_PORT,
																	BTN_EXIT_PIN,BTN_EXIT_PORT,
																	BTN_INC_PIN,BTN_INC_PORT,
																	BTN_DEC_PIN,BTN_DEC_PORT};
		// RPM meter initialization structure							
		Trpm_pinConfig		rpmPinCfg= {	RPM_PIN,RPM_PORT,RPM_ext};
		// Buzzer initialization structure
		Tbuzzer_Config		buzzerCfg= {BUZZER_PIN,BUZZER_PORT,1};

		// Default values for RAMP programs
		TrampConfig rampDefault=RAMP_DEFAULT_1;
		TrampConfig rampDefault1=RAMP_DEFAULT_2;
		TrampConfig rampDefault2=RAMP_DEFAULT_3;
		
		/* Deinitialize CLK */
		CLK_DeInit();
	
		/* Configure the Fcpu to DIV1*/
		CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
			
		/* Configure the HSI prescaler to the optimal value */
		CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
					
	 /* Configure the system clock to use HSI clock source and to run at 16Mhz */
		CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);		

		// Initialize PWM output
		PWM_init();	
		// Initialize RPM meter
		rpm_init(rpmPinCfg,RPM_MIN_VALUE,RPM_MAX_VALUE);
		// Initialize LCD
		lcd_3310_init(lcdPinCfg);
		// Initialize buttons
		btn_init(btnPinCfg);	
		// Initialize non-volatile memory
		ee_init();
		
		// Initialize buzzer
		buzzer_init(buzzerCfg);
		
		buzzer_setFreqTime(BUZZER_FREQUENCY,BUZZER_TIME);


		//Initialize S1-4 outputs as push-pull, low level
		GPIO_Init( S1_PORT, S1_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
		GPIO_Init( S2_PORT, S2_PIN, GPIO_MODE_OUT_PP_LOW_FAST);	
		GPIO_Init( S3_PORT, S3_PIN, GPIO_MODE_OUT_PP_LOW_FAST);	
		GPIO_Init( S4_PORT, S4_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
		// Initialize LCD background light control pin as output
		GPIO_Init( LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_PIN, GPIO_MODE_OUT_PP_LOW_FAST);	
		
		// Read device configuration from EEPROM data memory
		ee_readBuff((uint32_t)FLASH_DATA_START_PHYSICAL_ADDRESS,(uint8_t*)&mainConfig,sizeof(TmainConfig));

		// Check if configuration contains valid data
		if (mainConfig.numReflectors>10){
			// Configuration values are out of range. Set defaults
			mainConfig.numReflectors=REFLECTOR_COUNT_DEFAULT;
			mainConfig.PWMincValue=PWM_INCREMENT_DEFAULT;
			mainConfig.startupMenu=STARTUP_MENU_NONE;
			mainConfig.backLight=BACKLIGHT_OFF;
			mainConfig.PWMincIndex=0;
			
			mainConfig.rampCfg[0]=rampDefault;
			mainConfig.rampCfg[1]=rampDefault1;
			mainConfig.rampCfg[2]=rampDefault2;
			mainConfig.rampCurrent=0;
			
			// Temporary coefficient
			mainConfig.RPMus=10;
			
			// Write new configuration to EEPROM data memory
			ee_writeBuff((uint32_t)FLASH_DATA_START_PHYSICAL_ADDRESS,(uint8_t*)&mainConfig,sizeof(TmainConfig));
		}
	}
	
	/**
	* @brief  Main function. This function is executed after
	* power up.
	* @retval None
	*/
	void main(void)
	{
		// Temporary variable
		uint8_t tmp=0,tmp1=0;
		// Main initialization
		main_init();
		// Switch the backlight on/of accorting to config
		if ((mainConfig.backLight==BACKLIGHT_HIGH)||(mainConfig.backLight==BACKLIGHT_LOW))
				GPIO_HIGH(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_PIN);
		else		
				GPIO_LOW(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_PIN);
		// Set the startup menu from config
		menu=mainConfig.startupMenu;
		
/*If ESC arming on startup required*/					
#ifdef _ARM_ESC_ON_STARTUP		
		// Enable PWM output
		PWM_outputEnable();			
		// Set PWM width to 1000us
		PWM_setAllChannelDuty(1000*2);		
#endif		

		// Display logo screen
		lcd_3310_splash(logo);
		lcd_3310_drawTextXY(0,4,DEVICE_VERSION_STRING);
		// Wait for 2 seconds (100*20ms)
		tmp=TIM1_cnt&0xFF;
		while (((uint8_t)((TIM1_cnt&0xFF)-tmp))<250){
			tmp=btn_getState();
		/*	if ((tmp&btnDown)&&(tmp&btnUp)&&(tmp1<100))
				tmp1++;		*/	
		}
	/*	if (tmp1>50)
			menu=MENU_TEST;*/
			
/*If ESC arming on startup required*/								
#ifdef _ARM_ESC_ON_STARTUP		
		// Disable PWM output
		PWM_outputDisable();			
#endif		

		// Clear LCD
		lcd_3310_clear();
		
		/* Infinite loop */
		while (1)
		{
			// Scheduler for different modes (menus)
			switch(menu){
				case MENU_MAIN:
					mainMenu();
				break;
				case MENU_ANALOG:
					menuAnalog();
				break;
				case MENU_DIGITAL:
					menuDigital();
				break;
				case MENU_RAMP:
					menuRamp();
				break;
				case MENU_SETUP:
					menuSetup();
				break;	
				case MENU_SETUPRAMP:
					menuSetupRamp();
				break;	
				case MENU_TEST:
					menuTest();
				break;
				default:
					menu=MENU_MAIN;
				break;
			}
			// LCD backlight control
			if ((mainConfig.backLight==BACKLIGHT_HIGH)||(mainConfig.backLight==BACKLIGHT_LOW))
					GPIO_HIGH(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_PIN);
			else		
					GPIO_LOW(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_PIN);
			// RPM measurement callback
			rpm_callback();
		}  	
	}



#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2013 ElectronicsWorkshop.eu *****END OF FILE****/