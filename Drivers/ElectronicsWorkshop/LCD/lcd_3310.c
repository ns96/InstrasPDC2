#include <stdio.h>
#include "stm8s.h"
#include "lcd_3310.h"
/**Includes ------------------------------------------------ */
#include "font_6x8.h"
#include "spi.h"

/**Private defines------------------------------------------ */
#define lcd_3310_delay del();

/*Defines macros for controlling the RST pin*/
#define GPIO_HIGH(a,b) 		a->ODR|=b
#define GPIO_LOW(a,b)		a->ODR&=~b
#define RST_LOW GPIO_LOW(lcd_pins.RST_port,lcd_pins.RST_pin)
#define RST_HIGH GPIO_HIGH(lcd_pins.RST_port,lcd_pins.RST_pin)

/**Private variables------------------------------------------ */
uint8_t invertText=0;
lcd_3310_pinConfig lcd_pins;

/**Function implementation------------------------------------ */
void lcd_3310_invert(uint8_t val){
	invertText=val;
}
void del(){
			volatile uint16_t i;
			for (i=10000;i>1;i--);
}
	/**
  * @brief  Initializes LCD display
  * @param _lcd_pins: lcd_3310_pinConfig structure
	* defining the GPIO pins connected to LCD
  * @retval : None
  */
	void lcd_3310_init(lcd_3310_pinConfig _lcd_pins){
		//disable inversion
		invertText=0;
		lcd_pins=_lcd_pins;
		lcd_3310_GPIO_init();
		lcd_3310_SPI_init();
		//RST low
		GPIO_LOW(lcd_pins.RST_port,lcd_pins.RST_pin);
		lcd_3310_delay;
		//RST high
		GPIO_HIGH(lcd_pins.RST_port,lcd_pins.RST_pin);
		//Function set: active mode, horrizontal addressing, extended instruction set
		lcd_3310_write_byte(0x21,0);
		//Set Vop=70
		lcd_3310_write_byte(0xc6,0);  
		//Temperature control: coefficient 2
		lcd_3310_write_byte(0x06,0);  
		//Bias system: BS0, BS1
		lcd_3310_write_byte(0x13,0);  
		//Function set:active mode, horrizontal addressing
		lcd_3310_write_byte(0x20,0);
		//Display control: normal mode
		lcd_3310_write_byte(0x0c,0);
		//Clear LCD
		lcd_3310_clear();	
	}
	/**
  * @brief  Draws a progress bar
  * @param x: x coordinate of the progressbar in pixels
	* @param y: y coordinate of the progressbar in lines (8 pix.)
	* @param width: width of the progressbar in pixels
	* @param val: progress of the progressbar. Can be 0-100
  * @retval : None
  */
	void lcd_3310_progressBar(uint8_t x,uint8_t y,uint8_t width,uint8_t val){
		uint8_t i,img,temp;
		//lcd_3310_gotoxy(x,(48-y)/8);
		lcd_3310_gotoXY(x,y);
				temp=val;
		for (i=0;i<width;i++){
			if (i<val/(100/(width-4)))
				img=0xBD;	
			else
				img=0x81;
			if ((i==0)||(i==width-1))
				img=0xff;
			if ((i==1)||(i==width-2))
				img=0x81;
			//img=img<<(48-y)%8;
			lcd_3310_write_byte(img,1);
		}
	}

	/**
  * @brief  Draws a string on LCD in current position
  * @param str: pointer to a null terminated string
  * @retval : None
  */
	void lcd_3310_drawText(uint8_t *str){
		while (*str){
			lcd_3310_putChar(*str++);
		}
	}
	
	/**
  * @brief  Draws a string on LCD in set position
	* @param x: x coordinate in pixels
	* @param y: y coordinate in lines
	* @param str: pointer to a null terminated string
  * @retval : None
  */
	void lcd_3310_drawTextXY(uint8_t x,uint8_t y,uint8_t *str){
		lcd_3310_gotoXY(x,y);
		while (*str){
			lcd_3310_putChar(*str++);
		}
	}

	/**
  * @brief  Draws a character on LCD
	* @param chr: character to be printed
  * @retval : None
  */
	void lcd_3310_putChar(uint8_t chr)
	{	
		uint8_t i,character;
		uint8_t *pFontArray;  
		pFontArray = (uint8_t *)lcd_3310_font;
		chr -= lcd_3310_font_start;
	
		for (i=0; i<6; i++){
			character = pFontArray[chr*6+i+1];
			if (invertText>0)
			character=~character;
			lcd_3310_write_byte( character , 1);
		}
	}

	/**
  * @brief  Draws a character on LCD in set position
	* @param x: x coordinate in pixels
	* @param y: y coordinate in lines
	* @param chr: character to be printed
  * @retval : None
  */
	void lcd_3310_putCharXY(uint8_t x, uint8_t y,uint8_t chr)
	{
		lcd_3310_gotoXY(x,y);	
		lcd_3310_putChar(chr);
	}

	/**
  * @brief  Moves the cursor to set position
	* @param x: x coordinate in pixels
	* @param y: y coordinate in lines
  * @retval : None
  */
	void lcd_3310_gotoXY(uint8_t x, uint8_t y)
	{
		//Set column
		lcd_3310_write_byte(0x40 | y, 0);
		//Set row
			lcd_3310_write_byte(0x80 | x, 0);
			lcd_3310_delay;
	}

	/**
  * @brief  Clears the screen
	* @param : None
  * @retval : None
  */
	void lcd_3310_clear(void){
		lcd_3310_fill(0);
	}
	
	/**
  * @brief  Fills LCD with pattern
	* @param pattern: single byte pattern
  * @retval : None
  */
	void lcd_3310_fill(uint8_t pattern){
		unsigned int i;
			lcd_3310_write_byte(0x0c, 0);			
			lcd_3310_write_byte(0x80, 0); 
		lcd_3310_delay;
					
			for (i=0; i<504; i++){
				lcd_3310_write_byte(pattern, 1);
		}
	}

	/**
  * @brief  Displays an image from the buffer
	* @param buff: pointer to a buffer representing an image
  * @retval : None
  */
	void lcd_3310_splash(const uint8_t *buff){
			unsigned int i;
		lcd_3310_write_byte(0x0c, 0);			
		lcd_3310_write_byte(0x80, 0); 
		lcd_3310_delay;
			for (i=0; i<504; i++){
				lcd_3310_write_byte(buff[i], 1);
		}
	}

	/**
  * @brief  Initializes GPIO pins for LCD
	* @note	Currently supports only STM8S series microcontrollers
  * @retval : None
  */
	void lcd_3310_GPIO_init(void){
	
		/* Configure SPI1 RST as output push-pull */		
			GPIO_Init( lcd_pins.RST_port, lcd_pins.RST_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
			
		/* Configure SPI1 CE as output push-pull */
		GPIO_Init( lcd_pins.CE_port, lcd_pins.CE_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
	
		/* Configure SPI1 DC as output push-pull */
		GPIO_Init( lcd_pins.DC_port, lcd_pins.DC_pin, GPIO_MODE_OUT_PP_HIGH_FAST);	
	}

/**
  * @brief  Writes a byte to LCD
  * @param data: data byte to be written
  * @param DC: Sets the type of byte.
	* 1 - Data byte, 0 - Command byte
  * @retval : None
  */
	void lcd_3310_write_byte(uint8_t byte,uint8_t DC){
		//CE low
		GPIO_LOW(lcd_pins.CE_port,lcd_pins.CE_pin);
		if (DC)
			//DC high
			GPIO_HIGH(lcd_pins.DC_port,lcd_pins.DC_pin);	
		else
			//DC low
			GPIO_LOW(lcd_pins.DC_port,lcd_pins.DC_pin);
		spi_sendData(byte);
	}
	
	/**
  * @brief  Initializes SPI module used communicating
	* with LCD.
	* @note Currently supports only software SPI
  * @param : None
  * @retval : None
  */
	void lcd_3310_SPI_init(void){
			Tspi_pinConfig spi_config;
			
			spi_config.MOSI_pin=lcd_pins.DIN_pin;
			spi_config.MOSI_port=lcd_pins.DIN_port;		
			spi_config.SCK_pin=lcd_pins.CLK_pin;
			spi_config.SCK_port=lcd_pins.CLK_port;
			
			spi_init(spi_config );
	}

