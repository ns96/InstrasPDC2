#ifndef __lcd_ili9341_h_
#define __lcd_ili9341_h_

//TFT resolution 240*320
#define MIN_X	0
#define MIN_Y	0
#define MAX_X	239
#define MAX_Y	319
/* Public type definitions ------------------------------------------------*/	
	typedef struct {
		uint32_t RST_pin;
		GPIO_TypeDef* RST_port;
		uint32_t CE_pin;
		GPIO_TypeDef* CE_port;
		uint32_t DC_pin;
		GPIO_TypeDef* DC_port;
		uint32_t DIN_pin;
		GPIO_TypeDef* DIN_port;
		uint32_t CLK_pin;
		GPIO_TypeDef* CLK_port;
	} lcd_ili9341_pinConfig;

/* Public function prototypes ---------------------------------------------*/
	//hardware-level procedures
	void lcd_ili9341_init(lcd_ili9341_pinConfig _lcd_pins);
	void lcd_ili9341_GPIO_init(void);
	void lcd_ili9341_SPI_init(void);
	void lcd_ili9341_write_byte(uint8_t data,uint8_t DC);
	//low-level procedures
	void lcd_ili9341_clear(void);
	void lcd_ili9341_fill(uint8_t pattern);
	void lcd_ili9341_gotoXY(uint8_t x, uint8_t y);	
	void lcd_ili9341_invert(uint8_t val);
	void lcd_ili9341_putChar(uint8_t chr);
	//higher level procedures
	void lcd_ili9341_putCharXY(uint8_t x, uint8_t y,uint8_t chr);
	void lcd_ili9341_drawText(uint8_t *str);
	void lcd_ili9341_drawTextXY(uint8_t x,uint8_t y,uint8_t *data);
	void lcd_ili9341_drawInt(uint32_t data);
	void lcd_ili9341_drawIntXY(uint8_t x,uint8_t y,uint32_t data);
	void lcd_ili9341_progressBar(uint8_t x,uint8_t y,uint8_t width,uint8_t val);
	void lcd_ili9341_splash(const uint8_t *buff);
	void LCD_ILI9341_init1 (void);
uint8_t LCD_ILI9341_readID(void);
void LCD_ILI9341_fillScreen(void);
void LCD_ILI9341_setPixel(uint16_t poX, uint16_t poY,uint16_t color);
/*void LCD_ILI9341_fillScreen(uint16_t XL, uint16_t XR, uint16_t YU, uint16_t YD, uint16_t color);*/
#endif
