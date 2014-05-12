#ifndef __spi_h_
#define __spi_h_
#include "stm32f0xx_gpio.h"
	/* Public type definitions ------------------------------------------------*/
	typedef struct {
		uint32_t MOSI_pin;
		GPIO_TypeDef* MOSI_port;
		uint32_t MISO_pin;
		GPIO_TypeDef* MISO_port;		
		uint32_t SCK_pin;
		GPIO_TypeDef* SCK_port;		
	} Tspi_pinConfig;
	
	/* Public function prototypes ---------------------------------------------*/
	void spi_init(Tspi_pinConfig _spi_pins);
	uint8_t spi_sendData(uint8_t byte);
#endif