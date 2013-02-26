/**
  ******************************************************************************
  * @file    spi.c 
  * @author  Vaidas Zakarka
  * @version V1.0.0
  * @date    02-February-2013
  * @brief   Software SPI driver
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 ElectronicsWorkshop.eu</center></h2>
  ******************************************************************************
  */ 
	
	/* Includes ------------------------------------------------------------------*/
		#include "stm8s.h"
		#include "spi.h"
	/* Private defines -----------------------------------------------------------*/
		#define GPIO_HIGH(a,b) 		a->ODR|=b
		#define GPIO_LOW(a,b)		a->ODR&=~b
		#define SCK_HIGH	GPIO_HIGH(spi_pins.SCK_port,spi_pins.SCK_pin)		
		#define SCK_LOW	GPIO_LOW(spi_pins.SCK_port,spi_pins.SCK_pin)
		#define MOSI_HIGH	GPIO_HIGH(spi_pins.MOSI_port,spi_pins.MOSI_pin)
		#define MOSI_LOW	GPIO_LOW(spi_pins.MOSI_port,spi_pins.MOSI_pin)
	/* Private function prototypes -----------------------------------------------*/
		void spi_GPIO_init(void);
	/* Public variables ----------------------------------------------------------*/
		Tspi_pinConfig spi_pins;
	/* ---------------------------------------------------------------------------*/
	
	/**
  * @brief  Initializes the software SPI
  * @param _spi_pins: Tspi_pinConfig structure
	* defining the GPIO pins for SPI connection
  * @retval : None
  */
		void spi_init(Tspi_pinConfig _spi_pins){
			spi_pins=_spi_pins;
			spi_GPIO_init();
		}
			
	/**
  * @brief  Transmits data trough software SPI
  * @param byte: data byte to transmit
  * @retval : None
  */
		void spi_sendData(uint8_t byte){
			uint8_t d=byte;
			uint8_t i;
			for (i=8;i>0;i--){
				SCK_LOW;
				if ((d&(1<<(i-1)))!=0)
					MOSI_HIGH;
				else
					MOSI_LOW;
				SCK_HIGH;
			}
			MOSI_HIGH;
		}		

	/* Private functions ---------------------------------------------------------*/		
	/**
  * @brief  Initializes the gpio for software SPI
  * @param 	: None
  * @retval : None
  */
	void spi_GPIO_init(void){
		
		/* Configure SPI1 MOSI as output */
		GPIO_Init( spi_pins.MOSI_port, spi_pins.MOSI_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
	
		/* Configure SPI1 SCK as output */
		GPIO_Init( spi_pins.SCK_port, spi_pins.SCK_pin, GPIO_MODE_OUT_PP_HIGH_FAST);	
		
		MOSI_HIGH;
		SCK_HIGH;
		
	}