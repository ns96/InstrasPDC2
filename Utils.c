/**
  ******************************************************************************
  * @file    Utils.c
  * @author  Vaidas Zakarka
  * @version V1.0.0
  * @date    02-February-2013
  * @brief   Contains utilities for data type conversion
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 ElectronicsWorkshop.eu</center></h2>
  ******************************************************************************
  */ 
	/* Includes ------------------------------------------------------------------*/
	#include "Utils.h"
	
	void memfill(char *buff,char value,int count){
		int i;
		for (i=0;i<count;i++)
			buff[i]=value;
	}
	/**
	* @brief  Checks if the character provided is number
	* @param  byte: character to be evaluated
	* @retval None
	*/
	char isNum(char byte){
			if ((byte>='0')&&(byte<='9'))
					return 1;
			else
					return 0;
	}
	/**
	* @brief  Converts a null terminated string to integer
	* @param  buf: a pointer to null terminated string
	* @param  len: maximum length of the string
	* @retval converted integer value
	*/
	long atoi(char *buf,char len){
			long res=0;
			char neg=0,i=0;
			if (*buf=='-'){
				 neg=1;i++;
			}
			while(isNum(buf[i])&&(i<len)){
					res=res*10+buf[i]-'0';
					i++;
			}
			return neg ? -res:res;
	}

	/**
	* @brief  Converts an integer tp a null terminated string
	* @param  sk: integer number
	* @param  str: pointer to a null terminated string
	* @retval length of the constructed null terminated string
	*/
	unsigned char itoa(unsigned long sk,char *str)
	{
		unsigned long i=10,n=0;
		if (sk>(unsigned long)4000000000)
			return 0;
		while (i<=sk)	i*=10;
		while((i>=10)&&(n<11))
		{
			str[n]=(unsigned long)10*sk/i%10+48;
			i/=10;
			n++;
		}
		str[n]=0;
		return n;
	}