#ifndef __spi_h_
#define __spi_h_
	/* Public type definitions ------------------------------------------------*/
	typedef struct {
		u32 MOSI_pin;
		GPIO_TypeDef* MOSI_port;
		u32 MISO_pin;
		GPIO_TypeDef* MISO_port;		
		u32 SCK_pin;
		GPIO_TypeDef* SCK_port;		
	} Tspi_pinConfig;
	
	/* Public function prototypes ---------------------------------------------*/
	void spi_init(Tspi_pinConfig _spi_pins);
	uint8_t spi_sendData(uint8_t byte);
#endif