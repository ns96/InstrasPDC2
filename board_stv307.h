/**
  ******************************************************************************
  * @file    board_stv307.h 
  * @author  Vaidas Zakarka
  * @version V1.0.0
  * @date    02-February-2013
  * @brief   ST-V3 servo tester Board GPIO definitions
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 ElectronicsWorkshop.eu</center></h2>
  ******************************************************************************
  */ 
#ifndef __board_stv307_H
#define __board_stv307_H
	
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
	
	#define BUZZER_PORT		GPIOG
	#define BUZZER_PIN		GPIO_PIN_1	
	
	/* Potentiometer port/pin */
	
	#define POT_PORT		GPIOB
	#define POT_PIN			GPIO_PIN_7
	
	/* Slave Servo port/pin */
	
	#define S1_PORT			GPIOC
	#define S1_PIN			GPIO_PIN_3
	#define S1_TimSetCompare(x)	TIM1_SetCompare3(x)
	#define S1_TimGetCapture(x) TIM1_GetCapture3(x)
	#define S1_OCInit(x)	TIM1_OC3Init(x)
	
	#define S2_PORT			GPIOC
	#define S2_PIN			GPIO_PIN_2
	#define S2_TimSetCompare(x)	TIM1_SetCompare2(x)
	#define S2_OCInit(x)	TIM1_OC2Init(x)
	
	#define S3_PORT			GPIOC
	#define S3_PIN			GPIO_PIN_1
	
	/* Master Servo port/pin */
	
	#define S4_PORT			GPIOE
	#define S4_PIN			GPIO_PIN_5
	
	/* RPM sensor input port/pin */
	
	#define RPM_PORT			GPIOC
	#define RPM_PIN				GPIO_PIN_7
	#define RPM_ext	EXTI_PORT_GPIOC
	#define RPM_INT_HANDLER	7
	
	/* LCD port/pin */
	#define LCD_SCK_PORT		GPIOD
	#define LCD_SCK_PIN			GPIO_PIN_5
	
	#define LCD_MOSI_PORT		GPIOD
	#define LCD_MOSI_PIN		GPIO_PIN_4
	
	#define LCD_RST_PORT		GPIOD
	#define LCD_RST_PIN			GPIO_PIN_2
	
	#define LCD_CE_PORT			GPIOD
	#define LCD_CE_PIN			GPIO_PIN_0
	
	#define LCD_DC_PORT			GPIOD
	#define LCD_DC_PIN			GPIO_PIN_3
	
	#define LCD_BACKLIGHT_PORT		GPIOD
	#define LCD_BACKLIGHT_PIN			GPIO_PIN_6
	
	/* UART interface  */
	#define TX_PIN				S3_PIN
	#define TX_PORT				S3_PORT
	#define RX_PIN				S4_PIN
	#define RX_PORT				S4_PORT
	#define RX_EXTI_PORT	EXTI_PORT_GPIOE	
	#define RX_HANDLER		7

#endif