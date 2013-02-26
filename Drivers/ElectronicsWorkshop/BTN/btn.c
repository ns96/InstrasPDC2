/**
  ******************************************************************************
  * @file    btn.c 
  * @author  Vaidas Zakarka
  * @version V1.0.0
  * @date    02-February-2013
  * @brief   Button driver
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 ElectronicsWorkshop.eu</center></h2>
  ******************************************************************************
  */ 
	
	/* Includes ------------------------------------------------------------------*/
	#include "stm8s.h"
	#include "btn.h"
	
	/* Public variables ----------------------------------------------------------*/
	Tbtn_pinConfig pin_cfg;
	
	/* Public functions ---------------------------------------------------------*/		
	/**
  * @brief  Initializes the GPIO pins
  * @param _pin_cfg: Tbtn_pinConfig structure, 
	* containing pin and port definitions for buttons
  * @retval : None
  */
	void btn_init(Tbtn_pinConfig _pin_cfg){
		pin_cfg=_pin_cfg;
		/* Configure Enter button pin as input with pull-up resistor*/
		GPIO_Init( pin_cfg.Enter_port, pin_cfg.Enter_pin, GPIO_MODE_IN_PU_NO_IT);
		
		/* Configure Enter button pin as input with pull-up resistor*/
		GPIO_Init( pin_cfg.Exit_port, pin_cfg.Exit_pin, GPIO_MODE_IN_PU_NO_IT);
		
		/* Configure Enter button pin as input with pull-up resistor*/
		GPIO_Init( pin_cfg.Up_port, pin_cfg.Up_pin, GPIO_MODE_IN_PU_NO_IT);
		
		/* Configure Enter button pin as input with pull-up resistor*/
		GPIO_Init( pin_cfg.Down_port, pin_cfg.Down_pin, GPIO_MODE_IN_PU_NO_IT);		
	}
	
	
	/**
  * @brief  Reads the state of buttons
  * @param  None
  * @retval : returns the state of buttons. If button
	* is down, the corresponding bit is set to '1'
  */
	uint8_t btn_getState(void){
		uint8_t retval=0;
		
		if ((pin_cfg.Enter_port->IDR&pin_cfg.Enter_pin)==0)
			retval|=btnEnter;
			
		if ((pin_cfg.Exit_port->IDR&pin_cfg.Exit_pin)==0)
			retval|=btnExit;

		if ((pin_cfg.Up_port->IDR&pin_cfg.Up_pin)==0)
			retval|=btnUp;
			
		if ((pin_cfg.Down_port->IDR&pin_cfg.Down_pin)==0)
			retval|=btnDown;			

		return retval;
	}