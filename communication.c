	/**
  ******************************************************************************
  * @file    communication.c 
  * @author  Vaidas Zakarka
  * @version V1.0.0
  * @date    02-February-2013
  * @brief   PC communication module
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 ElectronicsWorkshop.eu</center></h2>
  ******************************************************************************
  */ 
	/* Includes ------------------------------------------------------------------*/
		#include "stm8s.h"
		#include "usart.h"
		#include <string.h>
		#include "board_stv307.h"
		#include "communication.h" 
		#include "utils.h"
		#include "global.h"
		#include "menu.h"
	/* Private defines -----------------------------------------------------------*/
		#define MAX_COMMAND_LEN	20
	/* Private function prototypes -----------------------------------------------*/
	
	/* Public variables ----------------------------------------------------------*/
	unsigned char rsbuff[MAX_COMMAND_LEN],UART_index=0;
	CommunicationStates_t commState=C_IDLE;
	uint8_t PCmode=0;
	/**
  * @brief  Byte received callback
  * @param c: received byte
  * @retval : None
  */
	void usart_byte_received(uint8_t c){		
		static unsigned char n=0;		
		// if uart state is idle
		if (commState!=C_IDLE)
			return 0; // return
		// if byte received is alphanumeric character and 
		// current command lenght does not exceed max.
		if ((n<MAX_COMMAND_LEN)&&(c>=32)&&(c<=127))
		{
			// if this is the first byte
			if (n==0)
				// clear the command reception buffer
				memfill(rsbuff,0,MAX_COMMAND_LEN);
			//echo the received character
			//usart_send(c);
			// Add received character to the buffer
			rsbuff[n++]=c;
		}
		// If CR symbol received and command
		// length is more than 1 symbol
		if ((c==13)&&(n>1))
		{
			// store command length
			UART_index=n;
			// set state to command pending
			commState=C_PENDING;
			// clear the bytes received counter
			n=0;
		}			
	}	
	/**
  * @brief  communication module task callback
	*	this function must be executed periodically from the main loop
  * @param 	: None
  * @retval : None
  */
	void communication_callback(void)
	{
		// Command prefixes
		#define RS_SetPWM1 "SET S1 "
		#define RS_SetPWM2 "SET S2 "
		#define RS_GetPWM "GET S"
		#define RS_GetRPM "GET RPM"
		#define RS_ModePC "MODE PC"
		#define RS_ModeNormal "MODE NORMAL"		
		uint16_t param=0;
		uint8_t buff[20],i;
		// If no data is pending
		if (commState!=C_PENDING)
			return; // Finish the function
		// Clear temporary buffer
		memfill(buff,0,20);
		// RS_SetPWM1 received?
		if (memcmp(rsbuff,RS_SetPWM1,sizeof(RS_SetPWM1)-1)==0)
		{
			// Is it PC mode?
			if (PCmode==1){
				// parse PWM value
				param=atoi (&rsbuff[sizeof(RS_SetPWM1)-1],4);
				// check if it is in predefined range
				if (((param>=1000)||(param==0))&&(param<=2000)){
					// set PWM value
					pwm_S1=param;
					// send response
					usart_sendString("OK");
					usart_sendString("\r\n");
				}
				// PWM value is out of range
				else
				{
					// send error message
					usart_sendString("ERR:1\r\n");
				}
			}
			// Trying to change values not in PC mode
			else
				// send error message
				usart_sendString("ERR:3\r\n");
			
		}
		else
		// RS_SetPWM2 received?
		if (memcmp(rsbuff,RS_SetPWM2,sizeof(RS_SetPWM2)-1)==0)
		{
			// Is it PC mode?
			if (PCmode==1){
				// parse PWM value
				param=atoi (&rsbuff[sizeof(RS_SetPWM2)-1],4);
				// check if it is in predefined range
				if (((param>=1000)||(param==0))&&(param<=2000)){
					// set PWM value
					pwm_S2=param;
					// send response
					usart_sendString("OK");
					usart_sendString("\r\n");
				}
				// PWM value is out of range
				else
				{
					// send error message
					usart_sendString("ERR:1\r\n");
				}
			}
			// Trying to change values not in PC mode
			else
				// send error message
				usart_sendString("ERR:3\r\n");

		}
		else
		// RS_GetRPM received?
		if(memcmp(rsbuff,RS_GetRPM,sizeof(RS_GetRPM)-1)==0){
				// construct string with RPM value
				itoa (rpm_p,buff);
				// send rpm value
				usart_sendString(buff);			
				// send nl+cr
				usart_sendString("\r\n");
		}
		else		
		// RS_GetPWM received?
		if(memcmp(rsbuff,RS_GetPWM,sizeof(RS_GetPWM)-1)==0){
				// parse the channel number (1 or 2)
				param=atoi (&rsbuff[sizeof(RS_GetPWM)-1],1);
				// is it 1 or 2?
				if ((param==1)||(param==2)){
					if (param==1)
						// construct answer with S1 PWM value
						itoa (pwm_S1,buff);
					else 
					// construct answer with S2 PWM value
						itoa (pwm_S2,buff);
					// send the PWM value
					usart_sendString(buff);		
					// send new line and carriage return
					usart_sendString("\r\n");
				}		
				// the command is corrupted
				else
				{
					// send error message
					usart_sendString("ERR:1\r\n");
				}
			
		}
		else
		// RS_ModePC received?
		if(memcmp(rsbuff,RS_ModePC,sizeof(RS_ModePC)-1)==0){
			// Deinitialize all menus
			menu_deinitAll();
			// Switch on the PC mode
			PCmode=1;
			// Send response
			usart_sendString("OK\r\n");
		}
		else
		// RS_ModeNormal received?
		if(memcmp(rsbuff,RS_ModeNormal,sizeof(RS_ModeNormal)-1)==0){
			// Deinitialize all menus
			menu_deinitAll();
			// Switch off the PC mode
			PCmode=0;
			// Send response
			usart_sendString("OK\r\n");
		}		
		// Unknown command received
		else
			usart_sendString("ERR:0\r\n");
		// Clear the received command buffer
		memfill(rsbuff,0,MAX_COMMAND_LEN);
		// Set communication state to idle
		commState=C_IDLE;
	}
	
	