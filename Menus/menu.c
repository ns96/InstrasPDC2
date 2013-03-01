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
	/**	Draws the current RPM value on the screen
	* @param x - x coordinate
	* @param y - y coordinate
	*/
	void menu_displayRPM(uint8_t x, uint8_t y){
			uint8_t str[14];
			uint16_t trpm1,trmp2;
		static Ttimer rpmTimer={0,0};
		// Calculate elapsed time since last rpm refresh
		// If time is more than 1s (50*20ms)
		if (((TIM1_cnt&0xFF)-rpmTimer.timeStart)>50)
		{
			// Store current time
			rpmTimer.timeStart=(TIM1_cnt)&0xFF;
			// Clear part of LCD, showing the RPM number
			lcd_3310_drawTextXY(x,y,"      ");			
			trpm1=rpm;
			trmp2=rpm_p;
			if ((rpm_p*mainConfig.numReflectors/60)<150)
				// Convert integer to string
				itoa((int32_t)trpm1,&str);
			else
				// Convert integer to string
				itoa((int32_t)trmp2,&str);			
			// Draw the RPM on the screen
			lcd_3310_drawTextXY(x,y,str);
		}
	}
	