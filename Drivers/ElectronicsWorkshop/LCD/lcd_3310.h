#ifndef __lcd_3310_h_
#define __lcd_3310_h_
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
	} lcd_3310_pinConfig;

/* Public function prototypes ---------------------------------------------*/
	//hardware-level procedures
	void lcd_3310_init(lcd_3310_pinConfig _lcd_pins);
	void lcd_3310_GPIO_init(void);
	void lcd_3310_SPI_init(void);
	void lcd_3310_write_byte(uint8_t data,uint8_t DC);
	//low-level procedures
	void lcd_3310_clear(void);
	void lcd_3310_fill(uint8_t pattern);
	void lcd_3310_gotoXY(uint8_t x, uint8_t y);	
	void lcd_3310_invert(uint8_t val);
	void lcd_3310_putChar(uint8_t chr);
	//higher level procedures
	void lcd_3310_putCharXY(uint8_t x, uint8_t y,uint8_t chr);
	void lcd_3310_drawText(uint8_t *str);
	void lcd_3310_drawTextXY(uint8_t x,uint8_t y,uint8_t *data);
	void lcd_3310_drawInt(uint32_t data);
	void lcd_3310_drawIntXY(uint8_t x,uint8_t y,uint32_t data);
	void lcd_3310_progressBar(uint8_t x,uint8_t y,uint8_t width,uint8_t val);
	void lcd_3310_splash(const uint8_t *buff);

#endif
