/**
  ******************************************************************************
  * @file    usart.c 
  * @author  Vaidas Zakarka
  * @version V1.0.0
  * @date    02-February-2013
  * @brief   Software usart driver
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 ElectronicsWorkshop.eu</center></h2>
  ******************************************************************************
  */ 
	/* Includes ------------------------------------------------------------------*/
		#include "stm8s.h"
		#include "usart.h"
		#include "board_stv307.h"
		#include "communication.h"
	/* Private defines -----------------------------------------------------------*/
		#define GPIO_HIGH(a,b) 		a->ODR|=b
		#define GPIO_LOW(a,b)		a->ODR&=~b
		//#define USART_DELAY ;
		#define BAUD	9600
		#define USART_DELAY_VAL	(1000000/BAUD)
	/* Private function prototypes -----------------------------------------------*/
		void usart_initTim4(uint8_t reload);
	/* Public variables ----------------------------------------------------------*/
		Tusart_pinConfig usart_pins;
	/*************/
	// bit-level communication states
	typedef enum
	{
			IDLE,                                       // Idle state
			TRANSMIT,                                   // Transmitting byte
			TRANSMIT_STOP_BIT,                          // Transmitting stop bit
			RECEIVE,                                    // Receiving byte
			DATA_PENDING                                // Byte received
	
	}AsynchronousStates_t;
	
	// bit-level state of the UART
	static volatile AsynchronousStates_t state;   
	// data to be transmitted
	static volatile unsigned char SwUartTXData;
	// transmit bit counter
	static volatile unsigned char SwUartTXBitCount; 
	// Received bits storage
	static volatile unsigned char SwUartRXData;   
	// receive bit counter
	static volatile unsigned char SwUartRXBitCount;
	
	
	/* ---------------------------------------------------------------------------*/
	/**
  * @brief  Initializes the uart driver
  * @param _usart_pins: Tusart_pinConfig structure containing pin definitions
  * @retval : None
  */	
	void usart_init(Tusart_pinConfig _usart_pins){
		usart_pins=_usart_pins;
		// initialize TX pin
		GPIO_Init( usart_pins.TX_port, usart_pins.TX_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
		// initialize RX pin
		GPIO_Init( usart_pins.RX_port, usart_pins.RX_pin, GPIO_MODE_IN_PU_IT);		
		// disable TIM4 update interrupt
		TIM4_ITConfig(TIM4_IT_UPDATE, DISABLE);//tim1
		// initialize TIM4
		usart_initTim4(USART_DELAY_VAL);
		//////////HARDCODED///////////////////////////////////////////
		EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOE,EXTI_SENSITIVITY_FALL_ONLY);
		//////////HARDCODED///////////////////////////////////////////
		enableInterrupts();
		//Internal State Variable
		state = IDLE;
	}
	/**
  * @brief  Initializes the Timer4
  * @param reload: timer reload value
  * @retval : None
  */		
void usart_initTim4(uint8_t reload){
		TIM4_DeInit();
		//Timer step 1us, reload every <reload> us
		TIM4_TimeBaseInit(TIM4_PRESCALER_16, reload);	
		/* TIM4 counter enable */
		TIM4_Cmd(ENABLE);
}
	/**
  * @brief  RX pin interrupt handler
  * @param 	: None
  * @retval : None
  */		
	void RX_pin_int_handler( void )
	{	
		//GPIO_TOGGLE(S3_PORT,S3_PIN); // FOR TIMING CORRECTION
		// Change state
		state = RECEIVE;                 
		// Disable interrupt during the data bits.	
		GPIO_Init( usart_pins.RX_port, usart_pins.RX_pin, GPIO_MODE_IN_PU_NO_IT);   
		// Disable timer to change its registers.
		TIM4_ITConfig(TIM1_IT_UPDATE, DISABLE);     
		// Count one and a half period into the future.			
		usart_initTim4(USART_DELAY_VAL*1.5);  
		//Compensate the delay in program execution
		TIM4_SetCounter(18);		
		// Clear received bit counter.
		SwUartRXBitCount = 0;         
		// Enable timer interrupt on again	    
		TIM4_ITConfig(TIM1_IT_UPDATE, ENABLE);        
	}
	/**
  * @brief  Timer interrupt handler
  * @param 	: None
  * @retval : None
  */		
	void Timer_interrupt_handler( void )
	{
	
		switch (state) {
		// Transmit Byte.
		case TRANSMIT:
			// Output the TX buffer.
			if( SwUartTXBitCount < 8 ) {            
				if( SwUartTXData & 0x01 ) {           // If the LSB of the TX buffer is 1:
					GPIO_HIGH(usart_pins.TX_port, usart_pins.TX_pin);                       // Send a logic 1 on the TX_PIN.
				}
				else {                                // Otherwise:
					GPIO_LOW(usart_pins.TX_port, usart_pins.TX_pin);                 // Send a logic 0 on the TX_PIN.
				}
				SwUartTXData = SwUartTXData >> 1;     // Bitshift the TX buffer and
				SwUartTXBitCount++;                   // increment TX bit counter.
			}
	
			//Send stop bit.
			else {
				GPIO_HIGH(usart_pins.TX_port, usart_pins.TX_pin);                         // Output a logic 1.
				state = TRANSMIT_STOP_BIT;
			}
		break;
	
		// Go to idle after stop bit was sent.
		case TRANSMIT_STOP_BIT:
			TIM4_ITConfig(TIM1_IT_UPDATE, DISABLE);          // Stop the timer interrupts.
			state = IDLE;                         // Go back to idle.
		 // ENABLE_EXTERNAL0_INTERRUPT( );        // Enable reception again.
		break;
	
		//Receive Byte.
		case RECEIVE:
		//GPIO_TOGGLE(S3_PORT,S3_PIN); // FOR TIMING CORRECTION
			usart_initTim4(USART_DELAY_VAL);     // Count one period after the falling edge is trigged.
			TIM4_SetCounter(10);
			TIM4_ITConfig(TIM1_IT_UPDATE, ENABLE);
			//Receiving, LSB first.
			if( SwUartRXBitCount < 8 ) {
					SwUartRXBitCount++;
					SwUartRXData = (SwUartRXData>>1);   // Shift due to receiving LSB first.
					if( (usart_pins.RX_port->IDR&usart_pins.RX_pin) != 0 ) {
							SwUartRXData |= 0x80;           // If a logical 1 is read, let the data mirror this.
					}
			}
	
			//Done receiving
			else {
					state = DATA_PENDING;               // Enter DATA_PENDING when one byte is received.
					TIM4_ITConfig(TIM1_IT_UPDATE, DISABLE);         // Disable this interrupt.       
					GPIO_Init( usart_pins.RX_port, usart_pins.RX_pin, GPIO_MODE_IN_PU_IT);     // Enable interrupt to receive more bytes.
					state = IDLE;
					usart_byte_received(SwUartRXData);
			}
		break;
	
		// Unknown state.
		default:        
			state = IDLE;                           // Error, should not occur. Going to a safe state.
		}
	}

	/**
  * @brief  Transmits the byte
  * @param 	c : byte to transmit
  * @retval : None
  */		
	void usart_send(uint8_t c)
{
  while( state != IDLE )
  {
    ;                               // Don't send while busy receiving or transmitting.
  }
	// Set state
  state = TRANSMIT;
	// Disable reception.
  GPIO_Init( usart_pins.RX_port, usart_pins.RX_pin, GPIO_MODE_IN_PU_NO_IT);  
	// Put byte into TX buffer.
  SwUartTXData = c;             
  SwUartTXBitCount = 0;         
	usart_initTim4(USART_DELAY_VAL);
  GPIO_LOW(usart_pins.TX_port, usart_pins.TX_pin);      
	// Enable timer interrupt
  TIM4_ITConfig(TIM1_IT_UPDATE, ENABLE);        
}
	/**
  * @brief  Transmits the string
  * @param 	str : pointer to a string
  * @retval : None
  */
void usart_sendString( const unsigned char *str )
{
  while( *str != '\0' )
  {
    usart_send( *str++ );
  }
}


