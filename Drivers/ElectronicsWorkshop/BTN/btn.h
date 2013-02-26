#ifndef __btn_h_
	#define __btn_h_
	/* Public defines ---------------------------------------------------------*/
	#define btnEnter	1<<0
	#define btnExit		1<<1
	#define btnUp			1<<2
	#define btnDown		1<<3
	/* Public type definitions ------------------------------------------------*/
	typedef struct {
		u32 Enter_pin;
		GPIO_TypeDef* Enter_port;
		u32 Exit_pin;
		GPIO_TypeDef* Exit_port;		
		u32 Up_pin;
		GPIO_TypeDef* Up_port;		
		u32 Down_pin;
		GPIO_TypeDef* Down_port;		
	} Tbtn_pinConfig;
	/* Public function prototypes ---------------------------------------------*/
	void btn_init(Tbtn_pinConfig _pin_cfg);
	uint8_t btn_getState(void);
#endif
		