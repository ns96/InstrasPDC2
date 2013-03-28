#ifndef __communication_h_
#define __communication_h_
	typedef enum
	{
			C_IDLE,							// IDLE state
			C_PENDING		// Command received and needs to be processed
	}CommunicationStates_t;
	/* Public function prototypes ---------------------------------------------*/
	void usart_byte_received(uint8_t c);
#endif