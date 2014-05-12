#ifndef __usart_h_
#define __usart_h_
#include "stm32f0xx_gpio.h"
	/* Public type definitions ------------------------------------------------*/
	typedef uint32_t EXTI_Port_TypeDef ;
	typedef struct {
		uint32_t TX_pin;
		GPIO_TypeDef* TX_port;
		uint32_t RX_pin;
		GPIO_TypeDef* RX_port;	
		EXTI_Port_TypeDef RX_exti_port;		
	} Tusart_pinConfig;
	
	/* Public function prototypes ---------------------------------------------*/
	void usart_init(Tusart_pinConfig _usart_pins);
	void usart_send(uint8_t c);
	void usart_sendString( const unsigned char *str );
#endif
	
	