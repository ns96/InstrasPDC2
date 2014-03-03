#ifndef __usart_h_
#define __usart_h_
	/* Public type definitions ------------------------------------------------*/
	typedef struct {
		u32 TX_pin;
		GPIO_TypeDef* TX_port;
		u32 RX_pin;
		GPIO_TypeDef* RX_port;	
		EXTI_Port_TypeDef RX_exti_port;		
	} Tusart_pinConfig;
	
	/* Public function prototypes ---------------------------------------------*/
	void usart_init(Tusart_pinConfig _usart_pins);
	void usart_send(uint8_t c);
	void RX_pin_int_handler( void );
	void Timer_interrupt_handler( void );
	void usart_sendString( const unsigned char *str );
#endif