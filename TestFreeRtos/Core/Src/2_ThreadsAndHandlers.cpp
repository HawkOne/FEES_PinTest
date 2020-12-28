/***************************************************************************************************
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *												   												   *
 *      FFFFFFFFFFFFFFFFFFFFFFEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE   SSSSSSSSSSSSSSS       *
 *      F::::::::::::::::::::FE::::::::::::::::::::EE::::::::::::::::::::E SS:::::::::::::::S      *
 *      F::::::::::::::::::::FE::::::::::::::::::::EE::::::::::::::::::::ES:::::SSSSSS::::::S      *
 *      FF::::::FFFFFFFFF::::FEE::::::EEEEEEEEE::::EEE::::::EEEEEEEEE::::ES:::::S     SSSSSSS      *
 *        F:::::F       FFFFFF  E:::::E       EEEEEE  E:::::E       EEEEEES:::::S                  *
 *        F:::::F               E:::::E               E:::::E             S:::::S                  *
 *        F::::::FFFFFFFFFF     E::::::EEEEEEEEEE     E::::::EEEEEEEEEE    S::::SSSS               *
 * ----   F:::::::::::::::F     E:::::::::::::::E     E:::::::::::::::E     SS::::::SSSSS     ---- *
 * -::-   F:::::::::::::::F     E:::::::::::::::E     E:::::::::::::::E       SSS::::::::SS   -::- *
 * ----   F::::::FFFFFFFFFF     E::::::EEEEEEEEEE     E::::::EEEEEEEEEE          SSSSSS::::S  ---- *
 *        F:::::F               E:::::E               E:::::E                         S:::::S      *
 *        F:::::F               E:::::E       EEEEEE  E:::::E       EEEEEE            S:::::S      *
 *      FF:::::::FF           EE::::::EEEEEEEE:::::EEE::::::EEEEEEEE:::::ESSSSSSS     S:::::S      *
 *      F::::::::FF           E::::::::::::::::::::EE::::::::::::::::::::ES::::::SSSSSS:::::S      *
 *      F::::::::FF           E::::::::::::::::::::EE::::::::::::::::::::ES:::::::::::::::SS       *
 *      FFFFFFFFFFF           EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE SSSSSSSSSSSSSSS         *
 *												   												   *
 *                  __    __     __     __   __    __  __ __       __    ___                       *
 *                 |_ |  |_ \_/||__)|  |_   |_ \_/|__)|_ |__)||\/||_ |\ | |  /\ |                  *
 *                 |  |__|__/ \||__)|__|__  |__/ \|   |__| \ ||  ||__| \| | /--\|__                *
 *                    __     __  __ __  __  __ __    __   ___ __       ___ __                      *
 *                   |_ |\/||__)|_ |  \|  \|_ |  \  (_  /\ | |_ |  |  | | |_                       *
 *                   |__|  ||__)|__|__/|__/|__|__/  __)/--\| |__|__|__| | |__                      *
 *                                                                                                 *
 *												    											   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *												   												   *
 *											FEES Project			 					           *
 *		    			URL: https://github.com/ferrandi/DEIB-DAER-project		                   *
 *				 					Politecnico di Milano - DEIB                                   *
 *			    						   Stefano Ampolo	    			                       *
 *		 			  ***********************************************************                  *
 *        		 	   		Copyright (c) 2018-2019 Politecnico di Milano				   		   *
 *                                                                                                 *
 *     This file is part of the FEES framework.                                                    *
 *                                                                                                 *
 *     The FEES framework is free software; you can redistribute it and/or modify                  *
 *     it under the terms of the GNU General Public License as published by                        *
 *     the Free Software Foundation; either version 3 of the License, or                           *
 *     (at your option) any later version.                                                         *
 *                                                                                                 *
 *     This program is distributed in the hope that it will be useful,                             *
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of                              *
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                               *
 *     GNU General Public License for more details.                                                *
 *                                                                                                 *
 *     You should have received a copy of the GNU General Public License                           *
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.                       *
 *                                                                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * FILE: 2_Threads&Handlers.cpp  - Former GpiosAndFunctions
 * DESCRIPTION: This file(s) Define and describe the core of the Housekeeping of the FEES System
 *
 *  Created on: 14 mar 2019
 *      Author: Stefano Ampolo
 */

#include "1_HardwareAndDrivers.hpp"
#include "2_ThreadsAndHandlers.hpp"
#include "3_ApplicationAndFSM.hpp"

#include <stdlib.h>
#include <cstdlib>
#include <sys/types.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <ctime>
#include <limits.h>



#include <iostream>
#include <cstdint>
#include <thread>


#include "main.h"
#include "cmsis_os.h"

using namespace std;


bool GPIO[34];

bool Flag_Telecom_Active=0;
bool Flag_Analog_Active=0;
bool Flag_GPS_Active=0;
bool Flag_Iridium_Active=0;
bool Flag_Radex_Active=0;
bool Flag_RaspberryPi_WD_Active=0;
bool Flag_ADCS_Active=0;
bool Flag_BatteryManagement_Active=0;
bool Flag_Hardware_Watchdog_Active=0;
bool Flag_Transmission_Watchdog_Active=0;

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

PCD_HandleTypeDef hpcd_USB_OTG_FS;



void Update_Pin_Mask(state_t NewState){
	switch(NewState){

	    case RECOVER_PREV_STATE:
	    	Pin_Mask_All_OFF();
	    	break;

	    case IN_VECTOR:
	    	Pin_Mask_InVector();
	    	break;

	    case WAIT_FIRST_TIMER:
	    	Pin_Mask_Wait();
	    	break;

	    case DETUMBLE_SECOND_TIMER:
   	    	Pin_Mask_Detumble();
	    	 break;

	    case NOMINAL:
	    	Pin_Mask_Nominal();
	    	break;

	    case TRANSMISSION:
	    	Pin_Mask_Transmission();
	    	break;

	    case RADEX_MODE:
	    	Pin_Mask_RADEX();
	    	break;

	    default:
	    	Pin_Mask_All_OFF();
	    	break;
	}
	return;
}

void Pin_Mask_All_OFF(){

	//	PAYLOAD CONTROL

	/******************************| TELECOM DEVICE-PAYLOAD       (PC13)*(GPIO 0 )   ******/
	//TELECOM_PowerON();
	TELECOM_PowerOFF();
	//TELECOM_PowerRESET();

	/******************************| Analog_DEVICES-PAYLOAD       (PE0)*(GPIO 2 )    ********/
	//Analog_PowerON();
	Analog_PowerOFF();
	//Analog_PowerRESET();

	/******************************| GPS DEVICE-PAYLOAD           (PE2)*( GPIO 1 )   *******/
	//GPS_PowerON();
	GPS_PowerOFF();
	//GPS_PowerRESET();

	/******************************| Iridium Trasmitter PAYLOAD   (PE3)*(GPIO 29)    ******/
	//Iridium_PowerON();
	Iridium_PowerOFF();
	//Iridium_PowerRESET();

	// IRIDIUM	CONTROL
	GpioReset(SDB_0);
	GpioReset(SDB_1);
	GpioReset(SDB_2);
	GpioReset(SDB_3);
	GpioReset(SDB_4);
	GpioReset(SDB_5);
	GpioReset(SDB_6);
	GpioReset(SDB_7);
	/******************************| RAD-Experiment PAYLOAD    (PE1)*( GPIO 5 )  ******/
	//Radex_PowerON();
	Radex_PowerOFF();
	//Radex_PowerRESET();

	// RADEX SIGNAL
	GpioReset(RADFET_OWB);	//Radex One-Wire Temp-Signal

	//Radex_SignalRESET();   // Signal GPIO 6 - This RESETS THE 32BitAdc


	/*********************************** RASPBERRY-Pi CONTROL - (GPIO 3 - 4)  ******/
	//RaspberryPi_PowerON();
	RaspberryPi_PowerOFF();
	//RaspberryPi_PowerRESET();
	//GpioReset(RASPY_ON);   // GPIO 3
	//GpioReset(RASPY_KEEP); 	//KeepON(AliveSignal)  - GPIO 4

	/******************************	MagnetoTorquerControl - ADCS SYSTEM   	*******/
	//ADCS_ON();
	ADCS_OFF();
	/*
	// PWM - GPIO  CONTROL
	GpioReset(PWM_X_GPIO);
	GpioReset(PWM_Y_GPIO);
	GpioReset(PWM_Z_GPIO);
	// PWM DIRECTION CONTROL
	GpioReset(DIR_X);
	GpioReset(DIR_Y);
	GpioReset(DIR_Z);
	*/

	/******************************	BATTERY THERMAL Control SYSTEM  (PWM 4)(GPIO 14)*/
	// BATTERY HEATER PWM - GPIO 14
	//BatteryThermal_Management_ON();
	BatteryThermal_Management_OFF();
	//GpioReset(BATTERY_HEATER_GPIO);

	/******************************	WatchDog  Control 	***************************/
	GpioReset(WATCHDOG);

	/******************************	EXTERNAL GPIO  Control ************************/
	//GpioSet(EX_GPIO_1);
	GpioReset(EX_GPIO_1);

	//GpioSet(EX_GPIO_2);
	GpioReset(EX_GPIO_2);

	//GpioSet(EX_GPIO_3);
	GpioReset(EX_GPIO_3);

	//GpioSet(EX_GPIO_4);
	GpioReset(EX_GPIO_4);


	/******************************	LED - TELECOM WATCHDOG  Control  (GPIO 19) ****/
	GpioReset(LED); // Led - Attivo Basso
	

	/******************************	PSD SELECTOR  Control  ******************* ****/
	GpioReset(PSD_0);
	GpioReset(PSD_1);
	GpioReset(PSD_2);
	GpioReset(PSD_3);

}
void Pin_Mask_InVector(){
	Pin_Mask_All_OFF();
}
void Pin_Mask_Wait(){

	//	PAYLOAD CONTROL

	/******************************| TELECOM DEVICE-PAYLOAD       (PC13)*(GPIO 0 )   ******/
	//TELECOM_PowerON();
	TELECOM_PowerOFF();
	//TELECOM_PowerRESET();

	/******************************| Analog_DEVICES-PAYLOAD       (PE0)*(GPIO 2 )    ********/
	//Analog_PowerON();
	Analog_PowerOFF();
	//Analog_PowerRESET();

	/******************************| GPS DEVICE-PAYLOAD           (PE2)*( GPIO 1 )   *******/
	//GPS_PowerON();
	GPS_PowerOFF();
	//GPS_PowerRESET();

	/******************************| Iridium Trasmitter PAYLOAD   (PE3)*(GPIO 29)    ******/
	//Iridium_PowerON();
	Iridium_PowerOFF();
	//Iridium_PowerRESET();
	// IRIDIUM	CONTROL
	GpioReset(SDB_0);
	GpioReset(SDB_1);
	GpioReset(SDB_2);
	GpioReset(SDB_3);
	GpioReset(SDB_4);
	GpioReset(SDB_5);
	GpioReset(SDB_6);
	GpioReset(SDB_7);

	/******************************| RAD-Experiment PAYLOAD    (PE1)*( GPIO 5 )  ******/
	//Radex_PowerON();
	Radex_PowerOFF();
	//Radex_PowerRESET();

	// RADEX SIGNAL
	GpioReset(RADFET_OWB);	//Radex One-Wire Temp-Signal

	//Radex_SignalRESET();   // Signal GPIO 6 - This RESETS THE 32BitAdc


	/*********************************** RASPBERRY-Pi CONTROL - (GPIO 3 - 4)  ******/
	//RaspberryPi_PowerON();
	RaspberryPi_PowerOFF();
	//RaspberryPi_PowerRESET();
	//GpioReset(RASPY_ON);   // GPIO 3
	//GpioReset(RASPY_KEEP); 	//KeepON(AliveSignal)  - GPIO 4

	/******************************	MagnetoTorquerControl - ADCS SYSTEM   	*******/
	//ADCS_ON();
	ADCS_OFF();
	/*
	// PWM - GPIO  CONTROL
	GpioReset(PWM_X_GPIO);
	GpioReset(PWM_Y_GPIO);
	GpioReset(PWM_Z_GPIO);
	// PWM DIRECTION CONTROL
	GpioReset(DIR_X);
	GpioReset(DIR_Y);
	GpioReset(DIR_Z);
	*/

	/******************************	BATTERY THERMAL Control SYSTEM  (PWM 4)(GPIO 14)*/
	// BATTERY HEATER PWM - GPIO 14
	BatteryThermal_Management_ON();
	//BatteryThermal_Management_OFF();
	//GpioReset(BATTERY_HEATER_GPIO);

	/******************************	WatchDog  Control 	***************************/
	GpioReset(WATCHDOG);

	/******************************	EXTERNAL GPIO  Control ************************/
	//GpioSet(EX_GPIO_1);
	GpioReset(EX_GPIO_1);

	//GpioSet(EX_GPIO_2);
	GpioReset(EX_GPIO_2);

	//GpioSet(EX_GPIO_3);
	GpioReset(EX_GPIO_3);

	//GpioSet(EX_GPIO_4);
	GpioReset(EX_GPIO_4);


	/******************************	LED - TELECOM WATCHDOG  Control  (GPIO 19) ****/
	GpioReset(LED); // Led - Attivo Basso

	/******************************	PSD SELECTOR  Control  ******************* ****/
	GpioReset(PSD_0);
	GpioReset(PSD_1);
	GpioReset(PSD_2);
	GpioReset(PSD_3);

}
void Pin_Mask_Detumble(){

	//	PAYLOAD CONTROL

	/******************************| TELECOM DEVICE-PAYLOAD       (PC13)*(GPIO 0 )   ******/
	//TELECOM_PowerON();
	TELECOM_PowerOFF();
	//TELECOM_PowerRESET();

	/******************************| Analog_DEVICES-PAYLOAD       (PE0)*(GPIO 2 )    ********/
	//Analog_PowerON();
	Analog_PowerOFF();
	//Analog_PowerRESET();

	/******************************| GPS DEVICE-PAYLOAD           (PE2)*( GPIO 1 )   *******/
	//GPS_PowerON();
	GPS_PowerOFF();
	//GPS_PowerRESET();

	/******************************| Iridium Trasmitter PAYLOAD   (PE3)*(GPIO 29)    ******/
	//Iridium_PowerON();
	Iridium_PowerOFF();
	//Iridium_PowerRESET();
	// IRIDIUM	CONTROL
	GpioReset(SDB_0);
	GpioReset(SDB_1);
	GpioReset(SDB_2);
	GpioReset(SDB_3);
	GpioReset(SDB_4);
	GpioReset(SDB_5);
	GpioReset(SDB_6);
	GpioReset(SDB_7);

	/******************************| RAD-Experiment PAYLOAD    (PE1)*( GPIO 5 )  ******/
	//Radex_PowerON();
	Radex_PowerOFF();
	//Radex_PowerRESET();

	// RADEX SIGNAL
	GpioReset(RADFET_OWB);	//Radex One-Wire Temp-Signal

	//Radex_SignalRESET();   // Signal GPIO 6 - This RESETS THE 32BitAdc


	/*********************************** RASPBERRY-Pi CONTROL - (GPIO 3 - 4)  ******/
	//RaspberryPi_PowerON();
	RaspberryPi_PowerOFF();
	//RaspberryPi_PowerRESET();
	//GpioReset(RASPY_ON);   // GPIO 3
	//GpioReset(RASPY_KEEP); 	//KeepON(AliveSignal)  - GPIO 4

	/******************************	MagnetoTorquerControl - ADCS SYSTEM   	*******/
	ADCS_ON();
	//ADCS_OFF();
	/*
	// PWM - GPIO  CONTROL
	GpioReset(PWM_X_GPIO);
	GpioReset(PWM_Y_GPIO);
	GpioReset(PWM_Z_GPIO);
	// PWM DIRECTION CONTROL
	GpioReset(DIR_X);
	GpioReset(DIR_Y);
	GpioReset(DIR_Z);
	*/

	/******************************	BATTERY THERMAL Control SYSTEM  (PWM 4)(GPIO 14)*/
	// BATTERY HEATER PWM - GPIO 14
	BatteryThermal_Management_ON();
	//BatteryThermal_Management_OFF();
	//GpioReset(BATTERY_HEATER_GPIO);

	/******************************	WatchDog  Control 	***************************/
	GpioReset(WATCHDOG);

	/******************************	EXTERNAL GPIO  Control ************************/
	//GpioSet(EX_GPIO_1);
	GpioReset(EX_GPIO_1);

	//GpioSet(EX_GPIO_2);
	GpioReset(EX_GPIO_2);

	//GpioSet(EX_GPIO_3);
	GpioReset(EX_GPIO_3);

	//GpioSet(EX_GPIO_4);
	GpioReset(EX_GPIO_4);


	/******************************	LED - TELECOM WATCHDOG  Control  (GPIO 19) ****/
	GpioReset(LED); // Led - Attivo Basso


	/******************************	PSD SELECTOR  Control  ******************* ****/
	GpioReset(PSD_0);
	GpioReset(PSD_1);
	GpioReset(PSD_2);
	GpioReset(PSD_3);

}
void Pin_Mask_Nominal(){

	//	PAYLOAD CONTROL

	/******************************| TELECOM DEVICE-PAYLOAD       (PC13)*(GPIO 0 )   ******/
	TELECOM_PowerON();
	//TELECOM_PowerOFF();
	//TELECOM_PowerRESET();

	/******************************| Analog_DEVICES-PAYLOAD       (PE0)*(GPIO 2 )    ********/
	Analog_PowerON();
	//Analog_PowerOFF();
	//Analog_PowerRESET();

	/******************************| GPS DEVICE-PAYLOAD           (PE2)*( GPIO 1 )   *******/
	GPS_PowerON();
	//GPS_PowerOFF();
	//GPS_PowerRESET();

	/******************************| Iridium Trasmitter PAYLOAD   (PE3)*(GPIO 29)    ******/
	//Iridium_PowerON();
	Iridium_PowerOFF();
	//Iridium_PowerRESET();
	// IRIDIUM	CONTROL
#ifdef ARDUPILOT
	GpioReset(SDB_0);
	GpioReset(SDB_1);
	GpioReset(SDB_2);
	GpioReset(SDB_3);
	GpioReset(SDB_4);
	GpioReset(SDB_5);
	GpioReset(SDB_6);
	GpioReset(SDB_7);
#endif // ADUPILOT

	/******************************| RAD-Experiment PAYLOAD    (PE1)*( GPIO 5 )  ******/
	//Radex_PowerON();
	Radex_PowerOFF();
	//Radex_PowerRESET();

	// RADEX SIGNAL
#ifdef ARDUPILOT
	GpioReset(RADFET_OWB);	//Radex One-Wire Temp-Signal
#endif // ADUPILOT

	//Radex_SignalRESET();   // Signal GPIO 6 - This RESETS THE 32BitAdc


	/*********************************** RASPBERRY-Pi CONTROL - (GPIO 3 - 4)  ******/
	//RaspberryPi_PowerON();
	RaspberryPi_PowerOFF();
	//RaspberryPi_PowerRESET();
	//GpioReset(RASPY_ON);   // GPIO 3
	//GpioReset(RASPY_KEEP); 	//KeepON(AliveSignal)  - GPIO 4

	/******************************	MagnetoTorquerControl - ADCS SYSTEM   	*******/
	ADCS_ON();
	//ADCS_OFF();
	/*
	// PWM - GPIO  CONTROL
	GpioReset(PWM_X_GPIO);
	GpioReset(PWM_Y_GPIO);
	GpioReset(PWM_Z_GPIO);
	// PWM DIRECTION CONTROL
	GpioReset(DIR_X);
	GpioReset(DIR_Y);
	GpioReset(DIR_Z);
	*/

	/******************************	BATTERY THERMAL Control SYSTEM  (PWM 4)(GPIO 14)*/
	// BATTERY HEATER PWM - GPIO 14
	BatteryThermal_Management_ON();
	//BatteryThermal_Management_OFF();
	//GpioReset(BATTERY_HEATER_GPIO);

	/******************************	WatchDog  Control 	***************************/
#ifdef ARDUPILOT
	GpioReset(WATCHDOG);
#endif // ADUPILOT

	/******************************	EXTERNAL GPIO  Control ************************/
#ifdef ARDUPILOT
	//GpioSet(EX_GPIO_1);
	GpioReset(EX_GPIO_1);

	//GpioSet(EX_GPIO_2);
	GpioReset(EX_GPIO_2);

	//GpioSet(EX_GPIO_3);
	GpioReset(EX_GPIO_3);

	//GpioSet(EX_GPIO_4);
	GpioReset(EX_GPIO_4);
#endif // ADUPILOT


	/******************************	LED - TELECOM WATCHDOG  Control  (GPIO 19) ****/
#ifdef ARDUPILOT
	GpioReset(LED); // Led - Attivo Basso
#endif // ADUPILOT

	/******************************	PSD SELECTOR  Control  ******************* ****/
#ifdef ARDUPILOT
	GpioReset(PSD_0);
	GpioReset(PSD_1);
	GpioReset(PSD_2);
	GpioReset(PSD_3);
#endif // ADUPILOT
}

void Pin_Mask_Transmission(){

	//	PAYLOAD CONTROL

	/******************************| TELECOM DEVICE-PAYLOAD       (PC13)*(GPIO 0 )   ******/
	TELECOM_PowerON();
	//TELECOM_PowerOFF();
	//TELECOM_PowerRESET();

	/******************************| Analog_DEVICES-PAYLOAD       (PE0)*(GPIO 2 )    ********/
	Analog_PowerON();
	//Analog_PowerOFF();
	//Analog_PowerRESET();

	/******************************| GPS DEVICE-PAYLOAD           (PE2)*( GPIO 1 )   *******/
	GPS_PowerON();
	//GPS_PowerOFF();
	//GPS_PowerRESET();

	/******************************| Iridium Trasmitter PAYLOAD   (PE3)*(GPIO 29)    ******/
	Iridium_PowerON();
	//Iridium_PowerOFF();
	//Iridium_PowerRESET();
	// IRIDIUM	CONTROL
#ifdef ARDUPILOT
	GpioReset(SDB_0);
	GpioReset(SDB_1);
	GpioReset(SDB_2);
	GpioReset(SDB_3);
	GpioReset(SDB_4);
	GpioReset(SDB_5);
	GpioReset(SDB_6);
	GpioReset(SDB_7);
#endif // ADUPILOT

	/******************************| RAD-Experiment PAYLOAD    (PE1)*( GPIO 5 )  ******/
	//Radex_PowerON();
	Radex_PowerOFF();
	//Radex_PowerRESET();

	// RADEX SIGNAL
#ifdef ARDUPILOT
	GpioReset(RADFET_OWB);	//Radex One-Wire Temp-Signal
#endif // ADUPILOT

	//Radex_SignalRESET();   // Signal GPIO 6 - This RESETS THE 32BitAdc


	/*********************************** RASPBERRY-Pi CONTROL - (GPIO 3 - 4)  ******/
	RaspberryPi_PowerON();
	//RaspberryPi_PowerOFF();
	//RaspberryPi_PowerRESET();
	//GpioReset(RASPY_ON);   // GPIO 3
	//GpioReset(RASPY_KEEP); 	//KeepON(AliveSignal)  - GPIO 4

	/******************************	MagnetoTorquerControl - ADCS SYSTEM   	*******/
	//ADCS_ON();
	ADCS_OFF();
	/*
	// PWM - GPIO  CONTROL
	GpioReset(PWM_X_GPIO);
	GpioReset(PWM_Y_GPIO);
	GpioReset(PWM_Z_GPIO);
	// PWM DIRECTION CONTROL
	GpioReset(DIR_X);
	GpioReset(DIR_Y);
	GpioReset(DIR_Z);
	*/

	/******************************	BATTERY THERMAL Control SYSTEM  (PWM 4)(GPIO 14)*/
	// BATTERY HEATER PWM - GPIO 14
	BatteryThermal_Management_ON();
	//BatteryThermal_Management_OFF();
	//GpioReset(BATTERY_HEATER_GPIO);

	/******************************	WatchDog  Control 	***************************/
	//GpioReset(WATCHDOG);

	/******************************	EXTERNAL GPIO  Control ************************/
#ifdef ARDUPILOT
	//GpioSet(EX_GPIO_1);
	GpioReset(EX_GPIO_1);

	//GpioSet(EX_GPIO_2);
	GpioReset(EX_GPIO_2);

	//GpioSet(EX_GPIO_3);
	GpioReset(EX_GPIO_3);

	//GpioSet(EX_GPIO_4);
	GpioReset(EX_GPIO_4);
#endif // ADUPILOT

	/******************************	LED - TELECOM WATCHDOG  Control  (GPIO 19) ****/
#ifdef ARDUPILOT
	GpioReset(LED); // Led - Attivo Basso
#endif // ADUPILOT


	/******************************	PSD SELECTOR  Control  ******************* ****/
#ifdef ARDUPILOT
	GpioReset(PSD_0);
	GpioReset(PSD_1);
	GpioReset(PSD_2);
	GpioReset(PSD_3);
#endif // ADUPILOT

}
void Pin_Mask_RADEX(){

	//	PAYLOAD CONTROL

	/******************************| TELECOM DEVICE-PAYLOAD       (PC13)*(GPIO 0 )   ******/
	TELECOM_PowerON();
	//TELECOM_PowerOFF();
	//TELECOM_PowerRESET();

	/******************************| Analog_DEVICES-PAYLOAD       (PE0)*(GPIO 2 )    ********/
	//Analog_PowerON();
	Analog_PowerOFF();
	//Analog_PowerRESET();

	/******************************| GPS DEVICE-PAYLOAD           (PE2)*( GPIO 1 )   *******/
	GPS_PowerON();
	//GPS_PowerOFF();
	//GPS_PowerRESET();

	/******************************| Iridium Trasmitter PAYLOAD   (PE3)*(GPIO 29)    ******/
	//Iridium_PowerON();
	Iridium_PowerOFF();
	//Iridium_PowerRESET();
	// IRIDIUM	CONTROL
#ifdef ARDUPILOT
	GpioReset(SDB_0);
	GpioReset(SDB_1);
	GpioReset(SDB_2);
	GpioReset(SDB_3);
	GpioReset(SDB_4);
	GpioReset(SDB_5);
	GpioReset(SDB_6);
	GpioReset(SDB_7);
#endif // ADUPILOT

	/******************************| RAD-Experiment PAYLOAD    (PE1)*( GPIO 5 )  ******/
	Radex_PowerON();
	//Radex_PowerOFF();
	//Radex_PowerRESET();

	// RADEX SIGNAL
	RADEX(); // STARTING THE RADEX FUNCION

	//GpioReset(RADFET_OWB);	//Radex One-Wire Temp-Signal

	//Radex_SignalRESET();   // Signal GPIO 6 - This RESETS THE 32BitAdc


	/*********************************** RASPBERRY-Pi CONTROL - (GPIO 3 - 4)  ******/
	//RaspberryPi_PowerON();
	RaspberryPi_PowerOFF();
	//RaspberryPi_PowerRESET();
	//GpioReset(RASPY_ON);   // GPIO 3
	//GpioReset(RASPY_KEEP); 	//KeepON(AliveSignal)  - GPIO 4

	/******************************	MagnetoTorquerControl - ADCS SYSTEM   	*******/
	ADCS_ON();
	//ADCS_OFF();
	/*
	// PWM - GPIO  CONTROL
	GpioReset(PWM_X_GPIO);
	GpioReset(PWM_Y_GPIO);
	GpioReset(PWM_Z_GPIO);
	// PWM DIRECTION CONTROL
	GpioReset(DIR_X);
	GpioReset(DIR_Y);
	GpioReset(DIR_Z);
	*/

	/******************************	BATTERY THERMAL Control SYSTEM  (PWM 4)(GPIO 14)*/
	// BATTERY HEATER PWM - GPIO 14
	BatteryThermal_Management_ON();
	//BatteryThermal_Management_OFF();
	//GpioReset(BATTERY_HEATER_GPIO);

	/******************************	WatchDog  Control 	***************************/
#ifdef ARDUPILOT
	GpioReset(WATCHDOG);
#endif // ADUPILOT

	/******************************	EXTERNAL GPIO  Control ************************/
#ifdef ARDUPILOT
	//GpioSet(EX_GPIO_1);
	GpioReset(EX_GPIO_1);

	//GpioSet(EX_GPIO_2);
	GpioReset(EX_GPIO_2);

	//GpioSet(EX_GPIO_3);
	GpioReset(EX_GPIO_3);

	//GpioSet(EX_GPIO_4);
	GpioReset(EX_GPIO_4);
#endif // ADUPILOT


	/******************************	LED - TELECOM WATCHDOG  Control  (GPIO 19) ****/
#ifdef ARDUPILOT
	GpioReset(LED); // Led - Attivo Basso
#endif // ADUPILOT


	/******************************	PSD SELECTOR  Control  ******************* ****/
#ifdef ARDUPILOT
	GpioReset(PSD_0);
	GpioReset(PSD_1);
	GpioReset(PSD_2);
	GpioReset(PSD_3);
#endif // ADUPILOT

}

void GpioSet(GPIO_TypeDef* GPIO_PORT , uint16_t GPIO_PIN , int pin){
	GPIO[pin]=1;  // Update of the GPIO Status Array

	#ifdef BAREMETAL
		HAL_GPIO_WritePin(GPIO_PORT, GPIO_PIN, 1);
	#endif // BAREMETAL

	#ifdef CHIBIOS
		palSetPad(GPIO_PORT, GPIO_PIN)
	#endif // CHIBIOS

	#ifdef ARDUPILOT
		hal.gpio->write(pin, 1 );  //Ardupilot Hal Function
	#endif // ARDUPILOT

	#ifdef FREERTOS

	#endif // FREERTOS

  //STUB FUNCTION PRINT
  //cout << " GPIO N " << pin << " set to HIGH - 1 \n";
}

void GpioReset(GPIO_TypeDef* GPIO_PORT , uint16_t GPIO_PIN , int pin){
  GPIO[pin]=0;  // Update of the GPIO Status Array

#ifdef BAREMETAL
  HAL_GPIO_WritePin(GPIO_PORT, GPIO_PIN, 0);
#endif // BAREMETAL

#ifdef CHIBIOS
  palClearPad(GPIO_PORT, GPIO_PIN)
#endif // CHIBIOS

#ifdef ARDUPILOT
  hal.gpio->write(pin, 0 );  //Ardupilot Hal Function
#endif // ARDUPILOT

#ifdef FREERTOS

  #endif // CHIBIOS

  //STUB FUNCTION PRINT
  //cout << " GPIO N " << pin << " set to LOW - 0 \n";
}

// User-friendly -STUB Functions
void print_PinMask(){

								  cout << "\r    __________________________________________________" << endl ;
								  cout << "\r   |                                                  |" << endl ;
								  cout << "\r   |   --- --- ---  The GPIO MASK IS :  --- --- ---   |" << endl ;
								  cout << "\r   |                                                  |" << endl ;
	for(int i=0 ; i<34 ; i++){
		if(i<10){if( (i%2) == 0){ cout << "\r   | - Gpio (0" << i << ") set to " << noboolalpha << GPIO[i] ;	}
				 if( (i%2) != 0){ cout << "   | - Gpio (0" << i << ") set to " << noboolalpha << GPIO[i] << "  - |" << endl ; }}
			else{if( (i%2) == 0){ cout << "\r   | - Gpio (" << i << ") set to " << noboolalpha << GPIO[i] ;}
				 if( (i%2) != 0){ cout << "   | - Gpio (" << i << ") set to " << noboolalpha << GPIO[i] << "  - |" << endl ; }}}
								  cout << "\r   |__________________________________________________|" << endl << endl ;
}
void print_ThreadsAndManagers(){
						  	   cout << endl << "\r |^^^^   FEES POWER and Threads  ^^^^|" << endl;
	    if(Flag_Telecom_Active)		 { cout << "\r |   - Telecom Module Power ON	     |" << endl ;}
	    						else { cout << "\r |   - Telecom Module Power OFF	     |" << endl ;}
	    if(Flag_Analog_Active)		 { cout << "\r |   - The Analog Power ON           |" << endl ;}
	    						else { cout << "\r |   - The Analog Power OFF          |" << endl ;}
	    if(Flag_GPS_Active)			 { cout << "\r |   - GPS Module Power ON           |" << endl ;}
	    						else { cout << "\r |   - GPS Module Power OFF          |" << endl ;}
	    if(Flag_Iridium_Active)		 { cout << "\r |   - Iridium Module Power ON       |" << endl ;}
	    						else { cout << "\r |   - Iridium Module Power OFF      |" << endl ;}
	    if(Flag_Radex_Active)		 { cout << "\r |   - RADiation EXperiment ON       |" << endl ;}
	    						else { cout << "\r |   - RADiation EXperiment OFF      |" << endl ;}
	   if(Flag_RaspberryPi_WD_Active){ cout << "\r |   - Raspberry Pi Power ON         |" << endl ;}
	    						else { cout << "\r |   - Raspberry Pi Power OFF        |" << endl ;}
	    							   cout << "\r |                                   |" << endl;
	    if( Flag_ADCS_Active )		 { cout << "\r |   - ADCS Thread is  ACTIVE        |" << endl ;}
	    						else { cout << "\r |   - ADCS Thread is NOT ACTIVE     |" << endl ;}
	if(Flag_BatteryManagement_Active){ cout << "\r |   - Battery PID Th  ACTIVE        |" << endl ;}
	    						else { cout << "\r |   - Battery PID Th NOT ACTIVE     |" << endl ;}
	if(Flag_Hardware_Watchdog_Active){ cout << "\r |   - Hardware WD Th  ACTIVE        |" << endl ;}
	    						else { cout << "\r |   - Hardware WD Th NOT ACTIVE     |" << endl ;}
 if(Flag_Transmission_Watchdog_Active){cout << "\r |   - TMTC WD Thread  ACTIVE        |" << endl ;}
								else { cout << "\r |   - TMTC WD Thread NOT ACTIVE     |" << endl ;}
									   cout << "\r |___________________________________|" << endl;
}

// // // POWER MANAGEMENT Functions
void System_Reboot(){
	// Da scrivere qui una routine che spenga prima tutti i devices-Payloads,
	// Salvi in memoria FeRam (statica) tutto il buffer-ram e poi faccia un restart della STM32. Fermando il thread hardware watchdog
 Analog_PowerOFF();
 GPS_PowerOFF();
 TELECOM_PowerOFF();
 Iridium_PowerOFF();
 Radex_PowerOFF();
 RaspberryPi_PowerOFF();

// -> Memory Save --> RamBuffer
// Watchdog (?)
// return0;
}

/******************************| TELECOM DEVICE-PAYLOAD       (PC13)*(GPIO 0 )   ******/
void TELECOM_PowerON(){
	// ACTUAL CHIBIOS FUNCTION
	// hal.gpio->write( 0 , 1 );
	GPIO[0]=1;
	Flag_Telecom_Active=TRUE;

	// STUB PART
	cout << " GPS POWER ON " << endl;
}
void TELECOM_PowerOFF(){
	// ACTUAL CHIBIOS FUNCTION
	// hal.gpio->write( 0 , 0 );
	GPIO[0]=0;
	Flag_Telecom_Active=0;

	// STUB PART
	cout << " GPS POWER ON " << endl;
}
void TELECOM_PowerRESET(){
	TELECOM_PowerON();
	FEES_Delay( 50 );
	TELECOM_PowerOFF();
	FEES_Delay( 50 );
	TELECOM_PowerON();
}

/******************************| Analog_DEVICES-PAYLOAD       (PE0)*(GPIO 2 )    ********/
void Analog_PowerON(){

	// ACTUAL CHIBIOS FUNCTION
	// hal.gpio->write( 2 , 1 );
	GPIO[2]=1;
	Flag_Analog_Active=TRUE;

	// STUB PART
	cout << " Turning ANALOG POWER ON " << endl;

}
void Analog_PowerOFF(){

	// ACTUAL CHIBIOS FUNCTION
	// hal.gpio->write( 2 , 0 );
	GPIO[2]=0;
	Flag_Analog_Active=0;
	// STUB PART
	cout << " Turning ANALOG POWER OFF " << endl;

}
void Analog_PowerRESET(){
	Analog_PowerON();
	FEES_Delay( 50 );
	Analog_PowerOFF();
	FEES_Delay( 50 );
	Analog_PowerON();
}

/******************************| GPS DEVICE-PAYLOAD           (PE2)*( GPIO 1 )   *******/
void GPS_PowerON(){
	// ACTUAL CHIBIOS FUNCTION
	// hal.gpio->write( 1 , 1 );
	GPIO[1]=1;
	Flag_GPS_Active=1;

	// STUB PART
	cout << " GPS POWER ON " << endl;
}
void GPS_PowerOFF(){
	// ACTUAL CHIBIOS FUNCTION
	// hal.gpio->write( 1 , 0 );
	GPIO[1]=0;
	Flag_GPS_Active=0;

	// STUB PART
	cout << " Turning ANALOG POWER ON " << endl;
}
void GPS_PowerRESET(){
	GPS_PowerON();
	FEES_Delay( 50 );
	GPS_PowerOFF();
	FEES_Delay( 50 );
	GPS_PowerON();
}

/******************************| Iridium Trasmitter PAYLOAD   (PE3)*(GPIO 29)    ******/
void Iridium_PowerON(){
	// ACTUAL CHIBIOS FUNCTION
	// hal.gpio->write( 29 , 1 );
	GPIO[29]=1;
	Flag_Iridium_Active= TRUE;

	// STUB PART
	cout << " Iridium POWER ON " << endl;
}
void Iridium_PowerOFF(){
	// ACTUAL CHIBIOS FUNCTION
	// hal.gpio->write( 29 , 0 );
	GPIO[29]=0;
	Flag_Iridium_Active= 0;

	// STUB PART
	cout << " Iridium POWER ON " << endl;
}
void Iridium_PowerRESET(){
	Iridium_PowerON();
	FEES_Delay( 50 );
	Iridium_PowerOFF();
	FEES_Delay( 50 );
	Iridium_PowerON();
}

/*********************************** RAD-Experiment PAYLOAD    (PE1)*( GPIO 5 )  ******/
void Radex_PowerON(){
	// ACTUAL CHIBIOS FUNCTION
	// hal.gpio->write( 5 , 1 );
	GPIO[5]=1;
	Flag_Radex_Active = TRUE;

	// STUB PART
	cout << " RadEX POWER ON " << endl;
}
void Radex_PowerOFF(){
	// ACTUAL CHIBIOS FUNCTION
	// hal.gpio->write( 5 , 0 );
	GPIO[5]=0;
	Flag_Radex_Active= FALSE;

	// STUB PART
	cout << " RadEX POWER OFF " << endl;
}
void Radex_PowerRESET(){
	Iridium_PowerON();
	FEES_Delay( 50 );
	Iridium_PowerOFF();
	FEES_Delay( 50 );
	Iridium_PowerON();
}
void Radex_SignalRESET(){
	// ACTUAL CHIBIOS FUNCTION
	// hal.gpio->write( 6 , 1 );
	GPIO[6]=1;


	// STUB PART
	cout << " Radex ADC32bit ON " << endl;

	FEES_Delay( 50 );

	// ACTUAL CHIBIOS FUNCTION
	// hal.gpio->write( 6 , 0 );
	GPIO[6]=0;


	// STUB PART
	cout << " Radex ADC32bit OFF " << endl;

	FEES_Delay( 50 );

	// ACTUAL CHIBIOS FUNCTION
	// hal.gpio->write( 6 , 1 );
	GPIO[6]=1;

	// STUB PART
	cout << " Radex ADC32bit ON " << endl;

}

// RADEX FUNCTION
void RADEX(){
	//This function will contain the RADEX Experiment
	Flag_Radex_Active=1;

	// This is the STUB PART
	cout << "The RadEX Execution has been Called." << endl;
}

/**********| RASPBERRY-Pi CONTROL - (GPIO 3 - 4)  ******     ******/
void RaspberryPi_PowerON(){  // GPIO 3
	// ACTUAL CHIBIOS FUNCTION
		// hal.gpio->write( 3 , 1 );
		GPIO[3]=1;
		RaspberryPi_Watchdog(); // Fa partire il Thread-Watchdog

		// STUB PART
		cout << " RASPBERRY Pi POWER ON " << endl;
}
void RaspberryPi_PowerOFF(){
		// ACTUAL CHIBIOS FUNCTION
		// hal.gpio->write( 3 , 0 );
		GPIO[3]=0;


		// STUB PART
		cout << " RASPBERRY Pi POWER OFF " << endl;
}
void RaspberryPi_PowerRESET(){
	RaspberryPi_PowerON();
	FEES_Delay( 50 );
	RaspberryPi_PowerOFF();
	FEES_Delay( 50 );
	RaspberryPi_PowerON();
}
//GpioReset(RASPY_ON);
//RASPY_KEEP-on thread); 	//KeepON(AliveSignal)  - GPIO 4
void RaspberryPi_Watchdog(){ // Questa funzione fa partire il Thread tiene acceso il RaspberryPi
	Flag_RaspberryPi_WD_Active = TRUE;
	cout << "  Thread Watchdog Raspberry Pi Lanciato! " << endl;
}

/**********| MagnetoTorquerControl - ADCS SYSTEM  ***** 	******/
// Attitude Determination and Control System
void ADCS_ON(){
	Flag_ADCS_Active = 1;
	// ACTUAL FUNCTION STILL TO BE WRITTEN

	//STUB PART:
	cout<< "The Attitude Control System is Active" << endl;
}
void ADCS_OFF(){
	Flag_ADCS_Active=0;
	// ACTUAL FUNCTION STILL TO BE WRITTEN

	//STUB PART:
	cout<< "The Attitude Control System is Disattivated" << endl;
}

/**********| BATTERY THERMAL Control SYSTEM  (PWM 4)(GPIO 14)*/
// BATTERY HEATER PWM - GPIO 14
	// Battery Thermal Management
void BatteryThermal_Management_ON(){
	Flag_BatteryManagement_Active=1;
	// ACTUAL FUNCTION STILL TO BE WRITTEN
	// Fa partire il Thread con il Regolatore P-I-D che pilota il PWM4 - Gpio14
	Flag_BatteryManagement_Active= TRUE;
	cout << "  Battery ThermalManagement Thread Lanciato! " << endl;

}
void BatteryThermal_Management_OFF(){
	Flag_BatteryManagement_Active=0;
	// ACTUAL FUNCTION STILL TO BE WRITTEN
	// Ferma il Thread con il Regolatore P-I-D
	Flag_BatteryManagement_Active= FALSE;

	//STUB PART:
	cout << "  Battery ThermalManagement Thread Spento " << endl;

}

/**********| WatchDog  Control 	**********************		******/
void Hardware_Watchdog_ON(){ // Questa funzione fa partire il Thread che gestisce il Watchdog Hardware

	Flag_Hardware_Watchdog_Active = TRUE;
	cout << "  Thread Watchdog Hardware Lanciato! " << endl;
}

void Hardware_Watchdog_OFF(){ // Questa funzione ferma Thread che gestisce il Watchdog Hardware

	Flag_Hardware_Watchdog_Active = FALSE;
	cout << "  Thread Watchdog Hardware Fermato! " << endl;
	cout << "  Sistema in Spegnimento ...  " << endl;
}



/**********| LED - TELECOM WATCHDOG  Control  (GPIO 19) *** ******/
void Transmission_Watchdog_ON(){ // Questa funzione fa partire il Thread che gestisce Led-Watchdog
	Flag_Transmission_Watchdog_Active = TRUE;
	cout << "  Thread Watchdog Transmission-Module Lanciato! " << endl;
}
void Transmission_Watchdog_OFF(){ // Questa funzione Ferma il Thread che gestisce Led-Watchdog
	Flag_Transmission_Watchdog_Active = FALSE;
	cout << "  Thread Watchdog Transmission-Module Fermato! " << endl;
}


// Complex Systems - Thread Functions
void thread_ADCS(){
	if(Flag_ADCS_Active == 1){
		// ADCS Algorithm Zone

	}

}
void thread_BatteryPID(){
	if(Flag_BatteryManagement_Active==1){
		// PID Function Zone

	}

}

// Watchdog Thread Functions
void thread_HardwareWD(){ 		// GPIO 20
	// ACTUAL CHIBIOS FUNCTION
	while(1){
		if(Flag_Hardware_Watchdog_Active==1){
			//hal.gpio->write( 20 , 1 );
			//std::this_thread::sleep_for(std::chrono::milliseconds(50));
			//hal.gpio->write( 20, 0 );
			//std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}}
}

void thread_TransmissionWD(){ 	// GPIO 19
	// ACTUAL CHIBIOS FUNCTION
	while(1){
		if(Flag_Transmission_Watchdog_Active==1){
				//hal.gpio->write( 19 , 1 );
				//std::this_thread::sleep_for(std::chrono::milliseconds(50));
				//hal.gpio->write( 19, 0 );
				//std::this_thread::sleep_for(std::chrono::milliseconds(50));
				}
			}
	// Inserire la funzione
	// Trasmetti BEACON
	// Cerca GroundStationBeacon --> fsm.beacon_received=TRUE; //se trovata
}


// FEES TESTING RELATED FUNCTIONS


// Thread for FiniteStateMachine update-handling
void thread_Fsm(){ // 1Hz Thread loop
	while(1){
    	fsm.event_Handler();
		// Sleep this thread for 1000 MilliSeconds (to time all 1 second)
    	FEES_Delay( 50);
	}
}


// Thread for user Screen Visualization
void thread_UserShell(){ // 24hrz Thread loop
	while(1)
		{
		print_SystemTime();
    	fsm.print_State();
    	fsm.print_Variables();
    	print_ThreadsAndManagers();
		print_PinMask();

		fsm.print_Menu();
		// Sleep this thread for 100 MilliSeconds
		FEES_Delay( 100 );

	}
}


void pintoggle(char port , int pin){
	GPIO_TypeDef * PORT__BASE;
	uint16_t pin_number=0;

	switch (port){
		case 'a': PORT__BASE = GPIOA;
		break;
		case 'b': PORT__BASE = GPIOB;
		break;
		case 'c': PORT__BASE = GPIOC;
		break;
		case 'd': PORT__BASE = GPIOD;
		break;
		case 'e': PORT__BASE = GPIOE;
		break;
		default: PORT__BASE = GPIOA;
		break;
		}
	switch (pin){
		case 0: pin_number = 0x0001;
		break;
		case 1: pin_number = 0x0002;
		break;
		case 2: pin_number = 0x0004;
		break;
		case 3: pin_number = 0x0008;
		break;
		case 4: pin_number = 0x0010;
		break;
		case 5: pin_number = 0x0020;
		break;
		case 6: pin_number = 0x0040;
		break;
		case 7: pin_number = 0x0080;
		break;
		case 8: pin_number = 0x0100;
		break;
		case 9: pin_number = 0x0200;
		break;
		case 10: pin_number = 0x0400;
		break;
		case 11: pin_number = 0x0800;
		break;
		case 12: pin_number = 0x1000;
		break;
		case 13: pin_number = 0x2000;
		break;
		case 14: pin_number = 0x4000;
		break;
		case 15: pin_number = 0x8000;
		break;
	}
	HAL_GPIO_WritePin(PORT__BASE, pin_number, 1);
	osDelay(10);
    HAL_GPIO_WritePin(PORT__BASE, pin_number, 0);
    osDelay(10);
}

void Hardware_Watchdog_Refresh(){
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, 1);
	  osDelay(100);
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, 0);
	  osDelay(100);
}

void TestPins(){

      // GPIO DI DIREZIONE
	 pintoggle('b',1);	// EX_GPIO1
 	 pintoggle('b',12);	// EX_GPIO2
 	 pintoggle('a',3);	// EX_GPIO3
 	 pintoggle('a',10);	// EX_GPIO4

      	  // PWM_ CONTROL
    pintoggle('c',8);  // PWM_HEATER - BATTERY

    pintoggle('a',0);  // PWM_HEATER - BATTERY
    pintoggle('a',1);  // PWM_HEATER - BATTERY
    pintoggle('a',2);  // PWM_HEATER - BATTERY

         // GPIO DI DIREZIONE
    pintoggle('e',7);	// Dir_X
    pintoggle('e',8);	// Dir_Y
    pintoggle('e',9);	// Dir_Z

    	//GPIO DI CONTROLLO
    //    pintoggle('b',5);	// WATCHDOG
    pintoggle('d',12); 	// TMTC_WD
    pintoggle('e',0);	// ANA_PWR_ON
    pintoggle('e',1);	// RAD_PWR_ON
    pintoggle('e',3);	// SBD_PWR_ON
    pintoggle('e',2);	// GPS_PWR_ON
    pintoggle('e',6);	// RSBY_PWR_ON
    pintoggle('b',0);	// RSBY_KEEP_EN


         //CS_SPI_SENSORI
    pintoggle('e',4);  	// CS_NAND
    pintoggle('e',5);  	// CS_LORA
    pintoggle('a',4);	// CS_RADFET
    pintoggle('e',11);	// EN_ADC1
    pintoggle('e',13);	// EN_ADC2
    pintoggle('e',12);	// EN_ADC3
    pintoggle('c',9);  	// EXT_SPI_EN
    pintoggle('d',10);	// CS_EEPROM
    pintoggle('d',11);	// CS_FRAM
    pintoggle('c',4);  	// CS_PSD1_AMP
    pintoggle('c',5);   // CS_PSD2_AMP
    pintoggle('e',10);  // CS_GYRO
    pintoggle('d',14);  // CS_GYRO2

    osDelay(250);
}

void TestBusses(){
		// TEST SERIALE
	uint8_t BufferPrint1[20]={"Seriale UNO 1!\n"};
	uint8_t BufferPrint2[20]={"Seriale DUE 2!\n"};
	uint8_t BufferPrint3[20]={"Seriale TRE 3!\n"};
	uint8_t BufferPrint6[20]={"Seriale SEI 6!\n"};

	HAL_UART_Transmit(&huart1, BufferPrint1, 20, 100);
	HAL_UART_Transmit(&huart2, BufferPrint2, 20, 100);
	HAL_UART_Transmit(&huart3, BufferPrint3, 20, 100);
	HAL_UART_Transmit(&huart6, BufferPrint6, 20, 100);
    osDelay(1);

    uint8_t Buffer[15]={ 0xFF, 0xFF, 0xFF,0x00,0x00,0xFF,0xFF,0x00,0xFF,0x00, 0x55, 0xAA, 0x80, 0x80, 0xAA};

    	// TEST I2C Busses
    HAL_I2C_Init(&hi2c1);
    HAL_I2C_Init(&hi2c2);

    HAL_I2C_Master_Transmit(&hi2c1, 0x11, Buffer, 15, 100);
    HAL_I2C_Master_Transmit(&hi2c2, 0x22, Buffer, 15, 100);
    osDelay(1);

        // TEST SPI
    HAL_SPI_Init(&hspi1);
    HAL_SPI_Init(&hspi2);
    HAL_SPI_Init(&hspi3);

    HAL_SPI_Transmit(&hspi1, Buffer, 10, 100);
    HAL_SPI_Transmit(&hspi2, Buffer, 10, 100);
    HAL_SPI_Transmit(&hspi3, Buffer, 10, 100);
    osDelay(1);
}

void PWM_STARTERS_T2_3_VariablePWM(){
	int i=1;
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

	// variable PWM in TIM2_Chann3

	/* Infinite loop */
	for(;;)
	{
		osDelay(1);
		TIM_OC_InitTypeDef sConfigOC = {0};
		sConfigOC.OCMode = TIM_OCMODE_PWM1;
		if(i==101){i=1;}
		sConfigOC.Pulse = i-1;
		sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
		sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
		if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK){ Error_Handler();} // variable PWM in TIM2_Chann3
		i=i+10;
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
		osDelay(1);

		/*osDelay(100);
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
		osDelay(100);

		  htim3.Init.Period = 0xFFFF; //

		  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
		  osDelay(100);
		  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
		  osDelay(100);

		  htim3.Init.Period = 0x1; //

		  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
		  osDelay(250);
		  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
		  osDelay(1000);*/
	}
}

void Crescendo_PWM_BATTERY(){
	  int i=1;
	  while(i<11){
		  TIM_MasterConfigTypeDef sMasterConfig = {0};
		  TIM_OC_InitTypeDef sConfigOC = {0};
		  htim3.Instance = TIM3;
		  if(i==1){htim3.Init.Prescaler  = 160-1;}
		  if(i==2){htim3.Init.Prescaler  = 150-1;}
		  if(i==3){htim3.Init.Prescaler  = 140-1;}
		  if(i==4){htim3.Init.Prescaler  = 130-1;}
		  if(i==5){htim3.Init.Prescaler  = 120-1;}
		  if(i==6){htim3.Init.Prescaler  = 110-1;}
		  if(i==7){htim3.Init.Prescaler  = 100-1;}
		  if(i==8){htim3.Init.Prescaler  = 90-1;}
		  if(i==9){htim3.Init.Prescaler  = 80-1;}
		  if(i==10){htim3.Init.Prescaler = 70-1;}

		  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
		  htim3.Init.Period = 100-1;
		  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
		  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK){Error_Handler();}

		  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
		  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
		  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK){ Error_Handler();}

		  sConfigOC.OCMode = TIM_OCMODE_PWM1;
		  sConfigOC.Pulse = 50-1;
		  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
		  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
		  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK){ Error_Handler();}
		  i++;
		  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
		  osDelay(100);
		  }
	  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
}

void Diminuendo_PWM_BATTERY(){
	  int i=0;
	  while(i<11){
		  TIM_MasterConfigTypeDef sMasterConfig = {0};
		  TIM_OC_InitTypeDef sConfigOC = {0};
		  htim3.Instance = TIM3;
		  if(i==1){htim3.Init.Prescaler  = 70-1;}
		  if(i==2){htim3.Init.Prescaler  = 80-1;}
		  if(i==3){htim3.Init.Prescaler  = 90-1;}
		  if(i==4){htim3.Init.Prescaler  = 100-1;}
		  if(i==5){htim3.Init.Prescaler  = 110-1;}
		  if(i==6){htim3.Init.Prescaler  = 120-1;}
		  if(i==7){htim3.Init.Prescaler  = 130-1;}
		  if(i==8){htim3.Init.Prescaler  = 140-1;}
		  if(i==9){htim3.Init.Prescaler  = 150-1;}
		  if(i==10){htim3.Init.Prescaler = 160-1;}

		  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
		  htim3.Init.Period = 100-1;
		  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
		  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK){Error_Handler();}

		  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
		  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
		  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK){ Error_Handler();}

		  sConfigOC.OCMode = TIM_OCMODE_PWM1;
		  sConfigOC.Pulse = 50-1;
		  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
		  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
		  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK){ Error_Handler();}
		  i++;
		  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
		  osDelay(100);
		  }
	  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
}



