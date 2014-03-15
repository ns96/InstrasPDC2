#ifndef __exgpio_h_
#define __exgpio_h_
	/* Public type definitions ------------------------------------------------*/	
	typedef struct {
		u32 D0_pin;
		GPIO_TypeDef* D0_port;
		u32 D1_pin;
		GPIO_TypeDef* D1_port;		
		u32 D2_pin;
		GPIO_TypeDef* D2_port;		
		u32 D3_pin;
		GPIO_TypeDef* D3_port;		
		u32 D4_pin;
		GPIO_TypeDef* D4_port;		
		u32 D5_pin;
		GPIO_TypeDef* D5_port;				
	} TEXGPIO_Config;
	#define D0 1
	#define D1 2
	#define D2 4
	#define D3 8
	#define D4 16
	#define D5 32	
	/* Public function prototypes ---------------------------------------------*/
			void EXGPIO_init(TEXGPIO_Config _exgpio_config);
			void EXGPIO_set(uint8_t pin,uint8_t state);
			void EXGPIO_toggle(uint8_t pin);
#endif