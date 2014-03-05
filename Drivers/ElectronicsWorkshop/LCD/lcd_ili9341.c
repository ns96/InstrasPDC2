#include <stdio.h>
#include "stm8s.h"
#include "lcd_ili9341.h"
/**Includes ------------------------------------------------ */
#include "font_6x8.h"
#include "spi.h"
#include "global.h"
/**Private defines------------------------------------------ */
#define lcd_ili9341_delay lcd_ili9341_del();

/*Defines macros for controlling the RST pin*/
#define GPIO_HIGH(a,b) 		a->ODR|=b
#define GPIO_LOW(a,b)		a->ODR&=~b
#define RST_LOW GPIO_LOW(lcd_ili9341_pins.RST_port,lcd_ili9341_pins.RST_pin)
#define RST_HIGH GPIO_HIGH(lcd_ili9341_pins.RST_port,lcd_ili9341_pins.RST_pin)

#define LCD_ILI9341_DC_HIGH	GPIO_HIGH(lcd_ili9341_pins.DC_port,lcd_ili9341_pins.DC_pin)
#define LCD_ILI9341_DC_LOW	GPIO_LOW(lcd_ili9341_pins.DC_port,lcd_ili9341_pins.DC_pin)
#define LCD_ILI9341_CS_HIGH	GPIO_HIGH(lcd_ili9341_pins.CE_port,lcd_ili9341_pins.CE_pin)
#define LCD_ILI9341_CS_LOW	GPIO_LOW(lcd_ili9341_pins.CE_port,lcd_ili9341_pins.CE_pin)
#define LCD_ILI9341_SPI_SendByte(x)	spi_sendData(x)

#define LCD_ILI9341_RST_HIGH	RST_HIGH
#define LCD_ILI9341_RST_LOW	RST_LOW


/**Private variables------------------------------------------ */
uint8_t invertText=0;
lcd_ili9341_pinConfig lcd_ili9341_pins;

/**Function implementation------------------------------------ */
void lcd_ili9341_invert(uint8_t val){
	invertText=val;
}
// HIGH LEVEL ROUTINES================================================

/**
  * @brief  Draws a progress bar
  * @param x: x coordinate of the progressbar in pixels
	* @param y: y coordinate of the progressbar in lines (8 pix.)
	* @param width: width of the progressbar in pixels
	* @param val: progress of the progressbar. Can be 0-100
  * @retval : None
  */
	void lcd_ili9341_progressBar(uint8_t x,uint8_t y,uint8_t width,uint8_t val){
	
	}

	/**
  * @brief  Draws a string on LCD in current position
  * @param str: pointer to a null terminated string
  * @retval : None
  */
	void lcd_ili9341_drawText(uint8_t *str){
		while (*str){
			lcd_ili9341_putChar(*str++);
		}
	}
	
	/**
  * @brief  Draws a string on LCD in set position
	* @param x: x coordinate in pixels
	* @param y: y coordinate in lines
	* @param str: pointer to a null terminated string
  * @retval : None
  */
	void lcd_ili9341_drawTextXY(uint8_t x,uint8_t y,uint8_t *str){
		lcd_ili9341_gotoXY(x,y);
		while (*str){
			lcd_ili9341_putChar(*str++);
		}
	}
/**
  * @brief  Draws a character on LCD in set position
	* @param x: x coordinate in pixels
	* @param y: y coordinate in lines
	* @param chr: character to be printed
  * @retval : None
  */
	void lcd_ili9341_putCharXY(uint8_t x, uint8_t y,uint8_t chr)
	{
		lcd_ili9341_gotoXY(x,y);	
		lcd_ili9341_putChar(chr);
	}

//==========================================LOW LEVEL ROUTINES===================
	void lcd_ili9341_del(){
			volatile uint16_t i,j;
			for (i=10000;i>1;i--)
				for (j=14;j>1;j--);
	}


	/**
  * @brief  Initializes LCD display
  * @param _lcd_ili9341_pins: lcd_ili9341_pinConfig structure
	* defining the GPIO pins connected to LCD
  * @retval : None
  */
	void lcd_ili9341_init(lcd_ili9341_pinConfig _lcd_pins){
		//disable inversion
		invertText=0;
		lcd_ili9341_pins=_lcd_pins;
		lcd_ili9341_GPIO_init();
		lcd_ili9341_SPI_init();
		LCD_ILI9341_init1();
		//Clear LCD
	//	lcd_ili9341_clear();	
	}
	
	/**
  * @brief  Draws a character on LCD
	* @param chr: character to be printed
  * @retval : None
  */
	void lcd_ili9341_putChar(uint8_t chr)
	{	
		uint8_t i,character;
		uint8_t *pFontArray;  
		pFontArray = (uint8_t *)lcd_3310_font;
		chr -= lcd_3310_font_start;
	
				 LCD_ILI9341_DC_HIGH;
    LCD_ILI9341_CS_LOW;
		for (i=0; i<6; i++){
			character = pFontArray[chr*6+i+1];
			if (invertText>0)
			character=~character;
			//lcd_3310_write_byte( character , 1);
        LCD_ILI9341_SPI_SendByte(0xf8);
        LCD_ILI9341_SPI_SendByte(0x10);


		}
		    LCD_ILI9341_CS_HIGH;
	}

	

	/**
  * @brief  Moves the cursor to set position
	* @param x: x coordinate in pixels
	* @param y: y coordinate in lines
  * @retval : None
  */
	void lcd_ili9341_gotoXY(uint8_t x, uint8_t y)
	{

	}

	/**
  * @brief  Clears the screen
	* @param : None
  * @retval : None
  */
	void lcd_ili9341_clear(void){
		lcd_ili9341_fill(0);
	}
	
	/**
  * @brief  Fills LCD with pattern
	* @param pattern: single byte pattern
  * @retval : None
  */
	void lcd_ili9341_fill(uint8_t pattern){
		
	}

	/**
  * @brief  Displays an image from the buffer
	* @param buff: pointer to a buffer representing an image
  * @retval : None
  */
	void lcd_ili9341_splash(const uint8_t *buff){

	}

	/**
  * @brief  Initializes GPIO pins for LCD
	* @note	Currently supports only STM8S series microcontrollers
  * @retval : None
  */
	void lcd_ili9341_GPIO_init(void){
	
		/* Configure SPI1 RST as output push-pull */		
			GPIO_Init( lcd_ili9341_pins.RST_port, lcd_ili9341_pins.RST_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
			
		/* Configure SPI1 CE as output push-pull */
		GPIO_Init( lcd_ili9341_pins.CE_port, lcd_ili9341_pins.CE_pin, GPIO_MODE_OUT_PP_HIGH_FAST);
	
		/* Configure SPI1 DC as output push-pull */
		GPIO_Init( lcd_ili9341_pins.DC_port, lcd_ili9341_pins.DC_pin, GPIO_MODE_OUT_PP_HIGH_FAST);	
	}

/**
  * @brief  Writes a byte to LCD
  * @param data: data byte to be written
  * @param DC: Sets the type of byte.
	* 1 - Data byte, 0 - Command byte
  * @retval : None
  */
	void lcd_ili9341_write_byte(uint8_t byte,uint8_t DC){		
		if (DC)
			//DC high
			LCD_ILI9341_DC_HIGH;
		else
			//DC low
			LCD_ILI9341_DC_LOW;
		//CE low
		LCD_ILI9341_CS_LOW;
		//Send byte
		LCD_ILI9341_SPI_SendByte(byte);
	}
	//-----------------------------------------------------------
	void lcd_ili9341_sendData(uint16_t vdata)
{
    uint8_t data1 = vdata>>8;
    uint8_t data2 = vdata&0xff;
    LCD_ILI9341_DC_HIGH;
    LCD_ILI9341_CS_LOW;
    LCD_ILI9341_SPI_SendByte(data1);
    LCD_ILI9341_SPI_SendByte(data2);
    LCD_ILI9341_CS_HIGH;
}
void lcd_ili9341_WRITE_Package(uint16_t *vdata, uint8_t howmany)
{
    uint16_t    data1 = 0;
    uint8_t   data2 = 0;
    uint8_t count=0;
    LCD_ILI9341_DC_HIGH;
    LCD_ILI9341_CS_LOW;

    for(count=0;count<howmany;count++)
    {
        data1 = vdata[count]>>8;
        data2 = vdata[count]&0xff;
        LCD_ILI9341_SPI_SendByte(data1);
        LCD_ILI9341_SPI_SendByte(data2);
    }
    LCD_ILI9341_CS_HIGH;
}

uint8_t LCD_ILI9341_Read_Register(uint8_t Addr, uint8_t xParameter)
{
    uint8_t vdata=0;
    lcd_ili9341_write_byte(0xd9,0);                                                      /* ext command                  */
    lcd_ili9341_write_byte(0x10+xParameter,1);                                        /* 0x11 is the first Parameter  */
    LCD_ILI9341_DC_LOW;
    LCD_ILI9341_CS_LOW;
    LCD_ILI9341_SPI_SendByte(Addr);
    LCD_ILI9341_DC_HIGH;
    vdata = LCD_ILI9341_SPI_SendByte(0);
    LCD_ILI9341_CS_HIGH;
    return vdata;
}
#define WRITE_DATA(x) lcd_ili9341_write_byte(x,1)
#define sendCMD(x) lcd_ili9341_write_byte(x,0)
void LCD_ILI9341_init1 (void)
{
	 uint8_t i=0, LCD_ILI9341Driver=0;
	 uint16_t x=0;
   // lcd_ili9341_SPI_init();
    LCD_ILI9341_CS_HIGH;
    LCD_ILI9341_DC_HIGH;
   

	//LCD_ILI9341_RST_LOW;
	//lcd_ili9341_delay(1000);
	LCD_ILI9341_RST_HIGH;
//lcd_ili9341_delay(1000);
    for(i=0;i<3;i++)
		//while(1)
    {
        LCD_ILI9341Driver = LCD_ILI9341_readID();
				lcd_ili9341_delay(100);
    }
		
		 lcd_ili9341_delay(500);
    sendCMD(0x01);	//software reset
    lcd_ili9341_delay(200);
		sendCMD(0xCF);
    WRITE_DATA(0x00);
    WRITE_DATA(0x8B);
    WRITE_DATA(0X30);

    sendCMD(0xED);
    WRITE_DATA(0x67);
    WRITE_DATA(0x03);
    WRITE_DATA(0X12);
    WRITE_DATA(0X81);

    sendCMD(0xE8);
    WRITE_DATA(0x85);
    WRITE_DATA(0x10);
    WRITE_DATA(0x7A);

    sendCMD(0xCB);
    WRITE_DATA(0x39);
    WRITE_DATA(0x2C);
    WRITE_DATA(0x00);
    WRITE_DATA(0x34);
    WRITE_DATA(0x02);

    sendCMD(0xF7);
    WRITE_DATA(0x20);

    sendCMD(0xEA);
    WRITE_DATA(0x00);
    WRITE_DATA(0x00);

    sendCMD(0xC0);                                                      /* Power control                */
    WRITE_DATA(0x1B);                                                   /* VRH[5:0]                     */

    sendCMD(0xC1);                                                      /* Power control                */
    WRITE_DATA(0x10);                                                   /* SAP[2:0];BT[3:0]             */

    sendCMD(0xC5);                                                      /* VCM control                  */
    WRITE_DATA(0x3F);
    WRITE_DATA(0x3C);

    sendCMD(0xC7);                                                      /* VCM control2                 */
    WRITE_DATA(0XB7);

    sendCMD(0x36);                                                      /* Memory Access Control        */
    WRITE_DATA(0x08);

    sendCMD(0x3A);
    WRITE_DATA(0x55);

    sendCMD(0xB1);
    WRITE_DATA(0x00);
    WRITE_DATA(0x1B);

    sendCMD(0xB6);                                                      /* Display Function Control     */
    WRITE_DATA(0x0A);
    WRITE_DATA(0xA2);


    sendCMD(0xF2);                                                      /* 3Gamma Function Disable      */
    WRITE_DATA(0x00);

    sendCMD(0x26);                                                      /* Gamma curve selected         */
    WRITE_DATA(0x01);

    sendCMD(0xE0);                                                      /* Set Gamma                    */
    WRITE_DATA(0x0F);
    WRITE_DATA(0x2A);
    WRITE_DATA(0x28);
    WRITE_DATA(0x08);
    WRITE_DATA(0x0E);
    WRITE_DATA(0x08);
    WRITE_DATA(0x54);
    WRITE_DATA(0XA9);
    WRITE_DATA(0x43);
    WRITE_DATA(0x0A);
    WRITE_DATA(0x0F);
    WRITE_DATA(0x00);
    WRITE_DATA(0x00);
    WRITE_DATA(0x00);
    WRITE_DATA(0x00);

    sendCMD(0XE1);                                                      /* Set Gamma                    */
    WRITE_DATA(0x00);
    WRITE_DATA(0x15);
    WRITE_DATA(0x17);
    WRITE_DATA(0x07);
    WRITE_DATA(0x11);
    WRITE_DATA(0x06);
    WRITE_DATA(0x2B);
    WRITE_DATA(0x56);
    WRITE_DATA(0x3C);
    WRITE_DATA(0x05);
    WRITE_DATA(0x10);
    WRITE_DATA(0x0F);
    WRITE_DATA(0x3F);
    WRITE_DATA(0x3F);
    WRITE_DATA(0x0F);

    sendCMD(0x11);                                                      /* Exit Sleep                   */
    lcd_ili9341_delay(120);
    sendCMD(0x29);                                                      /* Display on                   */
     LCD_ILI9341_fillScreen();
		 for (x=0;x<100;x++)
		 LCD_ILI9341_setPixel(x,10,0xf810);
		 lcd_ili9341_putChar('a');
	while(1){
		
	}
}

uint8_t LCD_ILI9341_readID(void)
{
    uint8_t i=0;
    uint8_t vdata[3] ;
    uint8_t ID[3] = {0x00, 0x93, 0x41};
    uint8_t ToF=1;
    for(i=0;i<3;i++)
    {
        vdata[i]=LCD_ILI9341_Read_Register(0xd3,i+1);
        if(vdata[i] != ID[i])
        {
            ToF=0;
        }
    }
    if(!ToF)                                                            /* data!=ID                     */
    {
		
    /*    Serial.print("Read LCD_ILI9341 ID failed, ID should be 0x09341, but read ID = 0x");
        for(i=0;i<3;i++)
        {
            Serial.print(data[i],HEX);
        }
        Serial.println();*/
    }
    return ToF;
}


void LCD_ILI9341_setCol(uint16_t StartCol,uint16_t EndCol)
{
    sendCMD(0x2A);                                                      /* Column Command address       */
    LCD_ILI9341_sendData(StartCol);
    LCD_ILI9341_sendData(EndCol);
}

void LCD_ILI9341_setPage(uint16_t StartPage,uint16_t EndPage)
{
    sendCMD(0x2B);                                                      /* Column Command address       */
    LCD_ILI9341_sendData(StartPage);
    LCD_ILI9341_sendData(EndPage);
}/*
void LCD_ILI9341_fillScreen(uint16_t XL, uint16_t XR, uint16_t YU, uint16_t YD, uint16_t color)
{
    unsigned long  XY=0;
    unsigned long i=0;
    uint8_t Hcolor = color>>8;
    uint8_t Lcolor = color&0xff;		

    if(XL > XR)
    {
        XL = XL^XR;
        XR = XL^XR;
        XL = XL^XR;
    }
    if(YU > YD)
    {
        YU = YU^YD;
        YD = YU^YD;
        YU = YU^YD;
    }
    XL = constrain(XL, MIN_X,MAX_X);
    XR = constrain(XR, MIN_X,MAX_X);
    YU = constrain(YU, MIN_Y,MAX_Y);
    YD = constrain(YD, MIN_Y,MAX_Y);

    XY = (XR-XL+1);
    XY = XY*(YD-YU+1);

    LCD_ILI9341_setCol(XL,XR);
    LCD_ILI9341_setPage(YU, YD);
    LCD_ILI9341_sendCMD(0x2c);                                                  

    LCD_ILI9341_DC_HIGH;
    LCD_ILI9341_CS_LOW;


    for(i=0; i < XY; i++)
    {
        LCD_ILI9341_SPI_SendByte(Hcolor);
        LCD_ILI9341_SPI_SendByte(Lcolor);
    }

    LCD_ILI9341_CS_HIGH;
}*/
//****************************************
void LCD_ILI9341_fillScreen(void)
{
	uint16_t i=0;
    LCD_ILI9341_setCol(0, 239);
    LCD_ILI9341_setPage(0, 319);
    sendCMD(0x2c);                                                  /* start to write to display ra */
                                                                        /* m                            */

    LCD_ILI9341_DC_HIGH;
    LCD_ILI9341_CS_LOW;
    for(i=0; i<38400; i++)
    {
        LCD_ILI9341_SPI_SendByte(0);
        LCD_ILI9341_SPI_SendByte(0);
        LCD_ILI9341_SPI_SendByte(0);
        LCD_ILI9341_SPI_SendByte(0);
    }
    LCD_ILI9341_CS_HIGH;
}

void LCD_ILI9341_setXY(uint16_t poX, uint16_t poY)
{
    LCD_ILI9341_setCol(poX, poX);
    LCD_ILI9341_setPage(poY, poY);
    sendCMD(0x2c);
}
void LCD_ILI9341_setPixel(uint16_t poX, uint16_t poY,uint16_t color)
{
    LCD_ILI9341_setXY(poX, poY);
    LCD_ILI9341_sendData(color);
}

void LCD_ILI9341_drawChar( uint8_t ascii, uint8_t poX, uint16_t poY,uint8_t size, uint16_t fgcolor)
{
	uint8_t temp;
  /*  if((ascii>=32)&&(ascii<=127))
    {
        ;
    }
    else
    {
        ascii = '?'-32;
    }
    for (int i =0; i<FONT_X; i++ ) {
        temp = pgm_read_byte(&simpleFont[ascii-0x20][i]);
        for(uint8_t f=0;f<8;f++)
        {
            if((temp>>f)&0x01)
            {
                fillRectangle(poX+i*size, poY+f*size, size, size, fgcolor);
            }
        }
    }*/
}

void LCD_ILI9341_drawString(char *string,uint16_t poX, uint16_t poY, uint16_t size,uint16_t fgcolor)
{
  /*  while(*string)
    {
        drawChar(*string, poX, poY, size, fgcolor);
        *string++;

        if(poX < MAX_X)
        {
            poX += FONT_SPACE*size;                                     // Move cursor right            
        }
    }*/
}
//-----------------------------------------------
	/**
  * @brief  Initializes SPI module used communicating
	* with LCD.
	* @note Currently supports only software SPI
  * @param : None
  * @retval : None
  */
	void lcd_ili9341_SPI_init(void){
			Tspi_pinConfig spi_config;
			
			spi_config.MOSI_pin=lcd_ili9341_pins.DIN_pin;
			spi_config.MOSI_port=lcd_ili9341_pins.DIN_port;		
			spi_config.SCK_pin=lcd_ili9341_pins.CLK_pin;
			spi_config.SCK_port=lcd_ili9341_pins.CLK_port;
			spi_config.MISO_port=LCD_MISO_PORT;
			spi_config.MISO_pin=LCD_MISO_PIN;
			
			spi_init(spi_config );
	}

