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
	void menu_displayRPM(uint8_t x, uint8_t y){
			uint8_t str[14];
		static Ttimer rpmTimer={0,0};
		// Calculate elapsed time since last rpm refresh
		// If time is more than 1s (50*20ms)
		if (((TIM1_cnt&0xFF)-rpmTimer.timeStart)>50)
		{
			// Store current time
			rpmTimer.timeStart=(TIM1_cnt)&0xFF;
			// Clear part of LCD, showing the RPM number
			lcd_3310_drawTextXY(x,y,"      ");
			// Convert integer to string
			itoa((int32_t)rpm,&str);
			// Draw the RPM on the screen
			lcd_3310_drawTextXY(x,y,str);
		}
		
	}
	