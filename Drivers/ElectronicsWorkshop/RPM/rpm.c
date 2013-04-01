	/**
  ******************************************************************************
  * @file    rpm.c 
  * @author  Vaidas Zakarka
  * @version V1.0.0
  * @date    02-February-2013
  * @brief   RPM measurement driver. Uses TIM1 with 20ms reload
	* period  as time base. 
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2013 ElectronicsWorkshop.eu</center></h2>
  ******************************************************************************
  */ 
	
	/* Includes ------------------------------------------------------------------*/
	#include "stm8s.h"
	#include "rpm.h"
	#include "board_stv307.h"
	#include "global.h"
	#include "communication.h"
	/* Private defines -----------------------------------------------------------*/
	/* Private function prototypes -----------------------------------------------*/
	
	/* Public variables ----------------------------------------------------------*/
	Trpm_pinConfig rpm_pins;
	uint32_t rpm_current=0,rpm_old=0;
	uint8_t rpmNoSignal=0,rpmSpinCNT=0;
	uint16_t rpm_min=0;
	uint16_t rpm_max=65000;
	uint16_t rpm_pulses=0;
	/* Private functions ---------------------------------------------------------*/
	
	/**
  * @brief  Initializes the GPIO pin and interrupt
  * @param _rpm_pins: Trpm_pinConfig structure, containing pin and port definitions
  * @retval : None
  */
	void rpm_init(Trpm_pinConfig _rpm_pins,uint16_t min,uint16_t max){
		rpm_pins=_rpm_pins;
		rpm_min=min;
		rpm_max=max;
		/* Configure RPM pin as floating input with interrupt*/
		GPIO_Init( rpm_pins.RPM_port, rpm_pins.RPM_pin, GPIO_MODE_IN_FL_IT);	
		
		/* Initialize the Interrupt sensitivity */
		EXTI_SetExtIntSensitivity(rpm_pins.RPM_exti, EXTI_SENSITIVITY_FALL_ONLY);
		EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_FALL_ONLY);
		
		/* Enable global interrupts */
		enableInterrupts();
	}
	
	/**
  * @brief  checks if RPM signal was lost
  * @param  : None
  * @retval : None
  */
	void rpm_callback(void){
		static uint16_t TIM_old=0;
		// If 1000ms has passed(50*20ms)
		if ((TIM1_cnt-TIM_old)>=50){
			TIM_old=TIM1_cnt;
			if (rpmNoSignal<5){
				rpmNoSignal++;
			}
			else{
				rpm=0;
			}
			if (rpmSpinCNT>0)
				rpmSpinCNT--;
		}
	}

	void rpm_timerInterruptHandler(void){
		rpm_p=rpm_pulses/mainConfig.numReflectors*RPM_PULSE_MEASUREMENT_FREQ*60;
		rpm_pulses=0;	
	}

	/**
  * @brief  Interrupt handler function for RPM metering
	* call to this function must be added to corresponding interrupt handler
  * @param  : None
  * @retval : None
  */
  void rpm_interruptHandler(void){		
	//	static uint8_t rpm_started=0,rpm_cnt=0,tmp=0,tmp1=0;
	//	static uint32_t rpm_val=0;

		/*check if the number of pulses does not exceed
			limiting values, calculated using max rpm value
			end max reflector count
		*/
		if (rpm_pulses<RPM_PULSE_COUNT_MAX){
			rpm_pulses++;
		}
		else
			rpm_pulses=0xFFFF;
	/*		
			tmp=TIM1->CNTRH;
		tmp1=TIM1->CNTRL;
		rpm_current=40000*TIM1_cnt;
		rpm_current+=((uint32_t)tmp<<8);
		rpm_current+=((uint32_t)tmp1);
		if (rpm_started){
			if (rpm_current>rpm_old){
				if (rpm_cnt<10){
					rpm_val+=(uint32_t)120000000/((uint32_t)(rpm_current-rpm_old));
					rpm_cnt++;
				}
				else
				{
					rpm=rpm_val/rpm_cnt/mainConfig.numReflectors;
					rpm_cnt=0;
					rpm_val=0;
				}
			}
			rpm_started=0;
		}
		else{				
			rpm_started=1;
		}
		rpm_old=rpm_current;*/
		rpmNoSignal=0;
		rpmSpinCNT=PUMP_DELAY;
	}
	
	
	
	
	
	
	
	
	
	
	
	