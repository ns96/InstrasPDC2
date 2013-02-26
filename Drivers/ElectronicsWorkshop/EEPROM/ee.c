	/**
  ******************************************************************************
  * @file    ee.c 
  * @author  Vaidas Zakarka
  * @version V1.0.0
  * @date    02-February-2013
  * @brief   EEPROM memory driver
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 ElectronicsWorkshop.eu</center></h2>
  ******************************************************************************
  */ 
	
	/* Includes ------------------------------------------------------------------*/
	#include "stm8s.h"
	#include "global.h"
	#include "ee.h"
	
	/* Public functions ---------------------------------------------------------*/
	
	/**
  * @brief  Initializes the EEPROM memory. Sets the flash
	* programming time and Unlocks the DATA memory section.
  * @retval : None
  */
	void ee_init(void){
		/* Define flash programming Time*/
		FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
	
		/* Unlock flash data eeprom memory */
		FLASH_Unlock(FLASH_MEMTYPE_DATA);
		/* Wait until Data EEPROM area unlocked flag is set*/
		while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET)
			;
	}
	
	/**
  * @brief  Reads single byte from memory
	* @param address : address to read
  * @retval : None
  */	
	uint8_t ee_read(uint32_t address){
		uint8_t ret=0;
		ret=FLASH_ReadByte(address);
		return ret;
	}
	
	/**
  * @brief  Writes single byte to memory
	* @param address : address to write to
	* @param value : byte to write
  * @retval : None
  */	
	void ee_write(uint32_t address,uint8_t value){
		FLASH_ProgramByte((uint32_t)address,(uint8_t)value);
	}
	
	/**
  * @brief  Reads buffer of bytes from memory
	* @param address : address of the first byte
	* @param buff : pointer to a data buffer
	* @param size : number of bytes to read
  * @retval : None
  */	
	void ee_readBuff(uint32_t address,uint8_t *buff,uint16_t size){
		uint16_t i;
		disableInterrupts();
		FLASH_Unlock(FLASH_MEMTYPE_DATA);
		for (i=0;i<size;i++){
			buff[i]=ee_read(address+i);				
		}	
		FLASH_Lock(FLASH_MEMTYPE_DATA);
		enableInterrupts();
	}
	/**
  * @brief  Writes buffer of bytes to memory
	* @param address : address of the first byte
	* @param buff : pointer to a data buffer
	* @param size : number of bytes to write
  * @retval : None
  */	
	void ee_writeBuff(uint32_t address,uint8_t *buff,uint16_t size){
		uint16_t i;
			disableInterrupts();
		FLASH_Unlock(FLASH_MEMTYPE_DATA);
		for (i=0;i<size;i++){
			ee_write(address+i,buff[i]);				
		}	
			FLASH_Lock(FLASH_MEMTYPE_DATA);
		enableInterrupts();
	}
