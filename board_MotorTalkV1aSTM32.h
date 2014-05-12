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
	#define BTN_ENTER_PORT	GPIOC
	#define BTN_ENTER_PIN		GPIO_Pin_14
	
	#define BTN_EXIT_PORT		GPIOC
	#define BTN_EXIT_PIN		GPIO_Pin_13
	
	#define BTN_INC_PORT		GPIOC
	#define BTN_INC_PIN			GPIO_Pin_15
	
	#define BTN_DEC_PORT		GPIOA
	#define BTN_DEC_PIN			GPIO_Pin_15
	
	/* Speaker port/pin */
	
	#define BUZZER_PORT		GPIOB
	#define BUZZER_PIN		GPIO_Pin_14	
	
	/* Potentiometer port/pin */
	
	#define POT_PORT		GPIOA
	#define POT_PIN			GPIO_Pin_4
	#define POT_INVERTED	1
	
	/* Slave Servo port/pin */
	
	#define S1_PORT			GPIOB
	#define S1_PIN			GPIO_Pin_4
	#define S1_TimSetCompare(x)	PWM_setCH1Duty(x)
	#define S1_TimGetCapture() TIM1_GetCapture4()
	#define S1_OCInit(a,b,c,d,e,f,g,h)	TIM1_OC4Init(a,b,d,e,g)
	
	#define S2_PORT			GPIOB
	#define S2_PIN			GPIO_Pin_5
	#define S2_TimSetCompare(x)	PWM_setCH2Duty(x)
	#define S2_OCInit(a,b,c,d,e,f,g,h)	TIM1_OC3Init(a,b,c,d,e,f,g,h)
	
	#warning "check if S3 port exists"
	#define S3_PORT			GPIOE
	#define S3_PIN			GPIO_Pin_0
	
	/* Master Servo port/pin */
	
	#define S4_PORT			GPIOE
	#define S4_PIN			GPIO_Pin_0
	
	
	#define STEPPER_DIR_PIN			GPIO_Pin_0
	#define STEPPER_DIR_PORT		GPIOG
	#define STEPPER_PULSE_PIN		GPIO_Pin_1
	#define STEPPER_PULSE_PORT	GPIOG
	
	/* RPM sensor input port/pin */
	
	#define RPM_PORT			GPIOE
	#define RPM_PIN				GPIO_Pin_7
	#define RPM_ext	EXTI_PORT_GPIOE
	#define RPM_INT_HANDLER	0
	
	/* LCD port/pin */
	#define LCD_ILI9341	1
	#define LCD_SCK_PORT		GPIOA
	#define LCD_SCK_PIN			GPIO_Pin_5
	
	#define LCD_MOSI_PORT		GPIOA
	#define LCD_MOSI_PIN		GPIO_Pin_7
	
	#define LCD_RST_PORT		GPIOB
	#define LCD_RST_PIN			GPIO_Pin_11
	
	#define LCD_CE_PORT			GPIOB
	#define LCD_CE_PIN			GPIO_Pin_2
	
	#define LCD_DC_PORT			GPIOB
	#define LCD_DC_PIN			GPIO_Pin_10
	
	#define LCD_MISO_PORT		GPIOA
	#define LCD_MISO_PIN		GPIO_Pin_6
	
	#define LCD_BACKLIGHT_PORT		GPIOB
	#define LCD_BACKLIGHT_PIN			GPIO_Pin_12
	#define LCD_BACKLIGHT_INVERTED	1
	
	#define lcd_clear()	lcd_ili9341_clear()
	#define lcd_drawText(x)	lcd_ili9341_drawText(x)
	#define lcd_drawTextXY(a,b,c)	lcd_ili9341_drawTextXY(a,b,c)
	#define lcd_invert(x) lcd_ili9341_invert(x)
	#define lcd_gotoXY(x,y)	lcd_ili9341_gotoXY(x,y)
	#define lcd_init(x) lcd_ili9341_init(x)
	#define lcd_splash(x) lcd_ili9341_splash(x)
	
	
	/* UART interface  */
	#define TX_PORT				GPIOA
	#define TX_PIN				GPIO_Pin_10
	#define RX_PORT				GPIOA
	#define RX_PIN				GPIO_Pin_9
	#define RX_EXTI_PORT	0//EXTI_PORT_GPIOD
	#define RX_HANDLER		6
	
	
	#define D0_PORT		GPIOB
	#define D0_PIN		GPIO_Pin_15

	#define D1_PORT		GPIOA
	#define D1_PIN		GPIO_Pin_8
	
	#define D2_PORT		GPIOA
	#define D2_PIN		GPIO_Pin_3

	#define D3_PORT		GPIOA
	#define D3_PIN		GPIO_Pin_2	
	
	#define D4_PORT		GPIOB
	#define D4_PIN		GPIO_Pin_6

	#define D5_PORT		GPIOB
	#define D5_PIN		GPIO_Pin_7	

#endif
