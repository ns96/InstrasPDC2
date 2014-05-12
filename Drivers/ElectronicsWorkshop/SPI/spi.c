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
	static void SPI_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
  
  /* Enable the SPI periph */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  
  /* Enable SCK, MOSI, MISO and NSS GPIO clocks */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB , ENABLE);
  
  GPIO_PinAFConfig(spi_pins.SCK_port, GPIO_PinSource5, GPIO_AF_0);
  GPIO_PinAFConfig(spi_pins.MOSI_port, GPIO_PinSource7, GPIO_AF_0);
  GPIO_PinAFConfig(spi_pins.MISO_port, GPIO_PinSource6, GPIO_AF_0);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;

  /* SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = spi_pins.SCK_pin;
  GPIO_Init(spi_pins.SCK_port, &GPIO_InitStructure);

  /* SPI  MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  spi_pins.MOSI_pin;
  GPIO_Init(spi_pins.MOSI_port, &GPIO_InitStructure);

  /* SPI MISO pin configuration */
  GPIO_InitStructure.GPIO_Pin = spi_pins.MISO_pin;
  GPIO_Init(spi_pins.MISO_port, &GPIO_InitStructure);
  
  /* SPI configuration -------------------------------------------------------*/
  SPI_I2S_DeInit(SPI1);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
   
  /* Configure the SPI interrupt priority */
  NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	/* Initializes the SPI communication */
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPI1, &SPI_InitStructure);
	
	/* Enable the SPI peripheral */
  SPI_Cmd(SPI1, ENABLE);
	
	
}
	/**
  * @brief  Initializes the software SPI
  * @param _spi_pins: Tspi_pinConfig structure
	* defining the GPIO pins for SPI connection
  * @retval : None
  */
		void spi_init(Tspi_pinConfig _spi_pins){
			spi_pins=_spi_pins;
			SPI_Config();
			//spi_GPIO_init();
		}
			
	/**
  * @brief  Transmits data trough software SPI
  * @param byte: data byte to transmit
  * @retval : None
  */
		uint8_t spi_sendData(uint8_t byte){
			SPI_SendData8(SPI1,byte);
			return 0;
			uint8_t d=byte;
			uint8_t received=0;
			uint8_t i;
			for (i=8;i>0;i--){
				SCK_LOW;
				if ((d&(1<<(i-1)))!=0)
					MOSI_HIGH;
				else
					MOSI_LOW;
				SCK_HIGH;
				
			//	if ((spi_pins.MISO_port->IDR&spi_pins.MISO_pin)==0)
				//	received|=(1<<(i-1));
			}
			MOSI_HIGH;
			return 0;//received;
		}		

	/* Private functions ---------------------------------------------------------*/		
	/**
  * @brief  Initializes the gpio for software SPI
  * @param 	: None
  * @retval : None
  */
	void spi_GPIO_init(void){
		GPIO_InitTypeDef        GPIO_InitStructure;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		
		GPIO_InitStructure.GPIO_Pin = spi_pins.MOSI_pin;
		GPIO_Init(spi_pins.MOSI_port, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = spi_pins.SCK_pin;
		GPIO_Init(spi_pins.SCK_port, &GPIO_InitStructure);
		
		/* Configure SPI1 MOSI as output */
	//	GPIO_Init( spi_pins.MOSI_port, spi_pins.MOSI_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
	
		/* Configure SPI1 SCK as output */
	//	GPIO_Init( spi_pins.SCK_port, spi_pins.SCK_pin, GPIO_MODE_OUT_PP_HIGH_FAST);	
		
		/* Configure SPI1 MISO as input */
		//GPIO_Init( spi_pins.MISO_port, spi_pins.MISO_pin, GPIO_MODE_IN_PU_NO_IT);
		MOSI_HIGH;
		SCK_HIGH;
		

		
	}