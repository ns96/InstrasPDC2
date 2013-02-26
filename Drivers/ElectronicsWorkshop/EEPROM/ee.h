#ifndef __ee_h_
#define __ee_h_
	/* Public function prototypes ---------------------------------------------*/
	void ee_init(void);
	uint8_t ee_read(uint32_t address);
	void ee_write(uint32_t address,uint8_t value);
	void ee_readBuff(uint32_t address,uint8_t *buff,uint16_t size);
	void ee_writeBuff(uint32_t address,uint8_t *buff,uint16_t size);
#endif