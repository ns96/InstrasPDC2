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
		#include "usart.h"
		#include "global.h"
		#include "communication.h"
	/* Private defines -----------------------------------------------------------*/
		#define GPIO_HIGH(a,b) 		a->ODR|=b
		#define GPIO_LOW(a,b)		a->ODR&=~b
		//#define USART_DELAY ;
		#define BAUD	9600
		#define USART_DELAY_VAL	(1000000/BAUD)
	/* Private function prototypes -----------------------------------------------*/

	/* Public variables ----------------------------------------------------------*/
		Tusart_pinConfig usart_pins;
	/*************/
	/* ---------------------------------------------------------------------------*/
	/**
  * @brief  Initializes the uart driver
  * @param _usart_pins: Tusart_pinConfig structure containing pin definitions
  * @retval : None
  */	
	void usart_init(Tusart_pinConfig _usart_pins){
		NVIC_InitTypeDef NVIC_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		usart_pins=_usart_pins;
		 
  /* USARTx configured as follow:
  - BaudRate = 9600 baud  
  - Word Length = 8 Bits
  - Stop Bit = 1 Stop Bit
  - Parity = No Parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
/* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE);

  /* Enable USART clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 		
		
	 /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);	
		
	 /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = usart_pins.TX_pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
		
	/* Configure USART Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = usart_pins.RX_pin;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
	/* USART configuration */
  USART_Init(USART1, &USART_InitStructure);
	/* Enable USART receive data register not empty interrupt*/
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
			/* Enable the TIM1 Trigger and commutation interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	/* Enable USART */
  USART_Cmd(USART1, ENABLE);
	
	
//		// initialize TX pin
//		GPIO_Init( usart_pins.TX_port, usart_pins.TX_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
//		// initialize RX pin
//		GPIO_Init( usart_pins.RX_port, usart_pins.RX_pin, GPIO_MODE_IN_PU_IT);		
//		// disable TIM4 update interrupt
//		TIM4_ITConfig(TIM4_IT_UPDATE, DISABLE);//
//		// initialize TIM4
//		usart_initTim4(USART_DELAY_VAL);
//		// Initialize interrupt on RX pin
//		EXTI_SetExtIntSensitivity(_usart_pins.RX_exti_port,EXTI_SENSITIVITY_FALL_ONLY);
//		// Global enable interrupts
//		enableInterrupts();
	}

	
		//			usart_byte_received(SwUartRXData);


	/**
  * @brief  Transmits the byte
  * @param 	c : byte to transmit
  * @retval : None
  */		
	void usart_send(uint8_t c)
{
   USART_SendData(USART1, c);
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


