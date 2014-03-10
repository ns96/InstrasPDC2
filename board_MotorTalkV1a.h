/**
  ******************************************************************************
  * @file    board_MotorTalkV1a.h 
  * @author  Vaidas Zakarka
  * @version V1.0.0
  * @date    02-February-2013
  * @brief   MotorTalk V1.0a Board GPIO definitions
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 ElectronicsWorkshop.eu</center></h2>
  ******************************************************************************
  */ 
#ifndef __board_MotorTalkV1a_H
#define __board_MotorTalkV1a_H
	
	/* macros for SET, RESET or TOGGLE Output port */
	#define GPIO_HIGH(a,b) 		a->ODR|=b
	#define GPIO_LOW(a,b)			a->ODR&=~b
	#define GPIO_TOGGLE(a,b) 	a->ODR^=b
	
	
	
	/* User button port/pin defines */
	#define BTN_ENTER_PORT	GPIOA
	#define BTN_ENTER_PIN		GPIO_PIN_6
	
	#define BTN_EXIT_PORT		GPIOA
	#define BTN_EXIT_PIN		GPIO_PIN_3
	
	#define BTN_INC_PORT		GPIOA
	#define BTN_INC_PIN			GPIO_PIN_5
	
	#define BTN_DEC_PORT		GPIOA
	#define BTN_DEC_PIN			GPIO_PIN_4
	
	/* Speaker port/pin */
	
	#define BUZZER_PORT		GPIOD
	#define BUZZER_PIN		GPIO_PIN_4	
	
	/* Potentiometer port/pin */
	
	#define POT_PORT		GPIOB
	#define POT_PIN			GPIO_PIN_7
	#define POT_INVERTED	1
	
	/* Slave Servo port/pin */
	
	#define S1_PORT			GPIOC
	#define S1_PIN			GPIO_PIN_4
	#define S1_TimSetCompare(x)	TIM1_SetCompare4(x)
	#define S1_TimGetCapture() TIM1_GetCapture4()
	#define S1_OCInit(a,b,c,d,e,f,g,h)	TIM1_OC4Init(a,b,d,e,g)
	
	#define S2_PORT			GPIOC
	#define S2_PIN			GPIO_PIN_3
	#define S2_TimSetCompare(x)	TIM1_SetCompare3(x)
	#define S2_OCInit(a,b,c,d,e,f,g,h)	TIM1_OC3Init(a,b,c,d,e,f,g,h)
	
	#define S3_PORT			GPIOE
	#define S3_PIN			GPIO_PIN_0
	
	/* Master Servo port/pin */
	
	#define S4_PORT			GPIOE
	#define S4_PIN			GPIO_PIN_0
	
	
	#define STEPPER_DIR_PIN			GPIO_PIN_0
	#define STEPPER_DIR_PORT		GPIOG
	#define STEPPER_PULSE_PIN		GPIO_PIN_1
	#define STEPPER_PULSE_PORT	GPIOG
	
	/* RPM sensor input port/pin */
	
	#define RPM_PORT			GPIOE
	#define RPM_PIN				GPIO_PIN_7
	#define RPM_ext	EXTI_PORT_GPIOC
	#define RPM_INT_HANDLER	0
	
	/* LCD port/pin */
	#define LCD_ILI9341	1
	#define LCD_SCK_PORT		GPIOC
	#define LCD_SCK_PIN			GPIO_PIN_5
	
	#define LCD_MOSI_PORT		GPIOC
	#define LCD_MOSI_PIN		GPIO_PIN_6
	
	#define LCD_RST_PORT		GPIOE
	#define LCD_RST_PIN			GPIO_PIN_0
	
	#define LCD_CE_PORT			GPIOD
	#define LCD_CE_PIN			GPIO_PIN_0
	
	#define LCD_DC_PORT			GPIOD
	#define LCD_DC_PIN			GPIO_PIN_3
	
	#define LCD_MISO_PORT		GPIOC
	#define LCD_MISO_PIN		GPIO_PIN_7
	
	#define LCD_BACKLIGHT_PORT		GPIOD
	#define LCD_BACKLIGHT_PIN			GPIO_PIN_2
	
	#define lcd_clear()	lcd_ili9341_clear()
	#define lcd_drawText(x)	lcd_ili9341_drawText(x)
	#define lcd_drawTextXY(a,b,c)	lcd_ili9341_drawTextXY(a,b,c)
	#define lcd_invert(x) lcd_ili9341_invert(x)
	#define lcd_gotoXY(x,y)	lcd_ili9341_gotoXY(x,y)
	#define lcd_init(x) lcd_ili9341_init(x)
	#define lcd_splash(x) lcd_ili9341_splash(x)
	
	
	/* UART interface  */
	#define TX_PORT				GPIOD
	#define TX_PIN				GPIO_PIN_5
	#define RX_PORT				GPIOD
	#define RX_PIN				GPIO_PIN_6
	#define RX_EXTI_PORT	EXTI_PORT_GPIOD
	#define RX_HANDLER		6

#endif