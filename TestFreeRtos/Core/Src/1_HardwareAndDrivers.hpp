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
 *
 */

//============================================================================
// Name        : 1_Hardware&Drivers.h  - Former GpioMapper.h  - Former PinMap.h
// Author      : Stefano Ampolo
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : this file is needed to link The Schematics to the GPIO system
//
// DA MODIFICARE IL FILE HWDEFINITION di ARDUPILOT.
//============================================================================

#ifndef MAPPER_H
#define MAPPER_H

void FEES_Delay( int a);
void FEES_print(int a , char *PrintBuffer );
void print_SystemTime();


void gpioPrintAll();
void gpioPrintStates();
void gpioPrintON();
void gpioPrintOFF();
void gpioPrint(int i);


#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <time.h>
#include <thread>
#include <ctime>
#include <limits.h>

#include <iostream>
#include <cstdint>
#include <thread>

#include "main.h"
#include "cmsis_os.h"

#include "string.h"

#include "main.h"
#include "cmsis_os.h"

//FEES RELATED INCLUDES

#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#include <limits.h>


//using namespace std;


// // // DEFINES DI PORT - MAPPING

#define		UHF_RESET		0
#define		GPS_PWR_ON		1
#define		ANA_PWR_ON		2
#define		RSBY_ON			3
#define		RSBY_KEEP_EN	4
#define		RAD_PWR_ON		5
#define		RAD_RESET		6

#define		PSD1_SEL0	7
#define		PSD1_SEL1	8
#define		PSD2_SEL0	9
#define		PSD2_SEL1	10

#define		DIR_X_COIL		11
#define		DIR_Y_COIL		12
#define		DIR_Z_COIL		13

#define		RADFET_OWB		14
#define		TMTC_MCU_WD		15
#define 	HW_WATCHDOG		16

// IRIDIUM - SBD (GPIO 18-26)
#define		SBD_PWR_ON		17  // Iridium Pwr On
#define		SBD_SER_DCD		18		// DCD
#define		SBD_SER_DSR		19		// DSR
#define		SBD_SER_DTR		20		// DTR
#define		SBD_SER_CTS 	21		// CTS
#define		SBD_SER_RTS 	22		// RTS
#define		SBD_ON_OFF		23		// ON_OFF
#define		SBD_SER_RI		24		// RI
#define		SBD_SER_NET 	25		// NET

#define EX_GPIO1	26 	//B1
#define	EX_GPIO2	27	//B12
#define	EX_GPIO3	28  //A3
#define	EX_GPIO4	29	//A10
#define EX_SPI_EN 	30	//C9

// Communication
#define EN_ADC1		31	//E11
#define EN_ADC2		32	//E13
#define EN_ADC3		33	//E12

#define CS_RADFET	34  //A4
#define CS_NAND		35	//E4
#define CS_LORA		36	//E5
#define CS_EEPROM	37	//D10
#define CS_FRAM		38	//D11
#define CS_GYRO		39	//E10
#define CS_GYRO2	40	//D14
#define INT_GYRO	41	//D13
#define INT_GYRO2	42	//D15
// Reostati
#define CS_PSD1_AMP	43 	//C4
#define CS_PSD2_AMP 44	//C5

// B2 GROUNDED impostare sempre down!



// // // Struttura dati per pins -> pinstm

typedef struct {
	//char* name;
    char port;
	int number;
	bool state;
} pinstm ;


pinstm GPIO[46]{
	//GPIO[ 0 ].name=  "UHF_RESET",
	GPIO[ 0 ].port=  'C' ,
	GPIO[ 0 ].number= 13 ,
	GPIO[ 0 ].state=  0 ,

	//GPIO[ 1 ].name= "GPS_PWR_ON",
	GPIO[ 1 ].port=  'E' ,
	GPIO[ 1 ].number= 2 ,
	GPIO[ 1 ].state=  0 ,

	//GPIO[ 2 ].name= "ANA_PWR_ON"   ,
	GPIO[ 2 ].port= 'E'   ,
	GPIO[ 2 ].number= 0  ,
	GPIO[ 2 ].state=   0 ,


	//GPIO[ 3 ].name=  "RSBY_ON" ,
	GPIO[ 3 ].port=   'E' ,
	GPIO[ 3 ].number=  6,
	GPIO[ 3 ].state=   0,

	//GPIO[ 4 ].name= "RSBY_KEEP_EN" ,
	GPIO[ 4 ].port=   'B' ,
	GPIO[ 4 ].number=  0,
	GPIO[ 4 ].state=   0,

	//GPIO[ 5 ].name= "RAD_PWR_ON"   ,
	GPIO[ 5 ].port=  'E'  ,
	GPIO[ 5 ].number= 1 ,
	GPIO[ 5 ].state=  0 ,

	//GPIO[ 6 ].name= "RAD_RESET"   ,
	GPIO[ 6 ].port=  'C'  ,
	GPIO[ 6 ].number= 15 ,
	GPIO[ 6 ].state=  0 ,

	//GPIO[ 7 ].name=  "PSD1_SEL0"  ,
	GPIO[ 7 ].port=  'C'  ,
	GPIO[ 7 ].number= 1 ,
	GPIO[ 7 ].state=  0 ,

	//GPIO[ 8 ].name=  "PSD1_SEL1"  ,
	GPIO[ 8 ].port=   'C' ,
	GPIO[ 8 ].number=  0,
	GPIO[ 8 ].state=   0,

	//GPIO[ 9 ].name=  "PSD2_SEL0"  ,
	GPIO[ 9 ].port=    'C',
	GPIO[ 9 ].number=  3,
	GPIO[ 9 ].state=   0,

	//GPIO[ 10 ].name=  "PSD2_SEL1"   ,
	GPIO[ 10 ].port=   'C' ,
	GPIO[ 10 ].number=  2,
	GPIO[ 10 ].state=   0,

	//GPIO[ 11 ].name=  "DIR_X_COIL"  ,
	GPIO[ 11 ].port=   'E' ,
	GPIO[ 11 ].number=  7,
	GPIO[ 11 ].state=   0,

	//GPIO[ 12 ].name=  "DIR_Y_COIL"  ,
	GPIO[ 12 ].port=   'E' ,
	GPIO[ 12 ].number=  8,
	GPIO[ 12 ].state=   0,

	//GPIO[ 13 ].name=  "DIR_Z_COIL"  ,
	GPIO[ 13 ].port=   'E',
	GPIO[ 13 ].number=  9,
	GPIO[ 13 ].state=   0,

	//GPIO[ 14 ].name=   "RADFET_OWB" ,
	GPIO[ 14 ].port=   'C' ,
	GPIO[ 14 ].number=  14,
	GPIO[ 14 ].state=   0,

	//GPIO[ 15 ].name=  "TMTC_MCU_WD"  ,
	GPIO[ 15 ].port=   'D' ,
	GPIO[ 15 ].number=  12,
	GPIO[ 15 ].state=   0,

	//	GPIO[ 16 ].name=  "HW_WATCHDOG" ,
	GPIO[ 16 ].port=   'B' ,
	GPIO[ 16 ].number=  5,
	GPIO[ 16 ].state=   0,

	//	GPIO[ 17 ].name=   "SBD_PWR_ON" ,
	GPIO[ 17 ].port=    'E',
	GPIO[ 17 ].number=  3,
	GPIO[ 17 ].state=   0,

	//	GPIO[ 18 ].name=  "SBD_SER_DCD"  ,
	GPIO[ 18 ].port=   'D' ,
	GPIO[ 18 ].number=  0,
	GPIO[ 18 ].state=   0,

	//	GPIO[ 19 ].name=  "SBD_SER_DSR"  ,
	GPIO[ 19 ].port=   'D' ,
	GPIO[ 19 ].number=  1,
	GPIO[ 19 ].state=   0,

	//	GPIO[ 20 ].name=  "SBD_SER_DTR"  ,
	GPIO[ 20 ].port=   'D' ,
	GPIO[ 20 ].number=  2,
	GPIO[ 20 ].state=   0,

	//	GPIO[ 21 ].name=   "SBD_SER_CTS" ,
	GPIO[ 21 ].port=   'D',
	GPIO[ 21 ].number=  3,
	GPIO[ 21 ].state=   0,

	//	GPIO[ 22 ].name=   "SBD_SER_RTS"  ,
	GPIO[ 22 ].port=    'D',
	GPIO[ 22 ].number=  4,
	GPIO[ 22 ].state=   0,

	//	GPIO[ 23 ].name=   "SBD_ON_OFF" ,
	GPIO[ 23 ].port=    'D',
	GPIO[ 23 ].number=  7,
	GPIO[ 23 ].state=   0,

	//	GPIO[ 24 ].name=   "SBD_SER_RI" ,
	GPIO[ 24 ].port=   'E' ,
	GPIO[ 24 ].number=  14,
	GPIO[ 24 ].state=   0,

	//	GPIO[ 25 ].name=   "SBD_SER_NET" ,
	GPIO[ 25 ].port=    'E',
	GPIO[ 25 ].number=  15,
	GPIO[ 25 ].state=   0,

	//	GPIO[ 26 ].name=   "EX_GPIO1" ,
	GPIO[ 26 ].port=    'B',
	GPIO[ 26 ].number=  1,
	GPIO[ 26 ].state=   0,

	//	GPIO[ 27 ].name=   "EX_GPIO2" ,
	GPIO[ 27 ].port=    'B',
	GPIO[ 27 ].number=  12,
	GPIO[ 27 ].state=   0,

	//	GPIO[ 28 ].name=   "EX_GPIO3" ,
	GPIO[ 28 ].port=    'A',
	GPIO[ 28 ].number=  3,
	GPIO[ 28 ].state=   0,

	//	GPIO[ 29 ].name=   "EX_GPIO4" ,
	GPIO[ 29 ].port=    'A',
	GPIO[ 29 ].number=  10,
	GPIO[ 29 ].state=   0,

	//	GPIO[ 30 ].name=   "EX_SPI_EN" ,
	GPIO[ 30 ].port=   'C' ,
	GPIO[ 30 ].number=  9,
	GPIO[ 30 ].state=   0,

	//	GPIO[ 31 ].name=   "EN_ADC1" ,
	GPIO[ 31 ].port=   'E' ,
	GPIO[ 31 ].number=  11,
	GPIO[ 31 ].state=   0,

	//	GPIO[ 32 ].name=   "EN_ADC2" ,
	GPIO[ 32 ].port=   'E' ,
	GPIO[ 32 ].number=  13,
	GPIO[ 32 ].state=   0,

	//	GPIO[ 33 ].name=   "EN_ADC3" ,
	GPIO[ 33 ].port=   'E' ,
	GPIO[ 33 ].number=  12,
	GPIO[ 33 ].state=   0,

	//	GPIO[ 34 ].name=   "CS_RADFET" ,
	GPIO[ 34 ].port=   'A' ,
	GPIO[ 34 ].number=  4,
	GPIO[ 34 ].state=   0,

	//	GPIO[ 35 ].name=   "CS_NAND" ,
	GPIO[ 35 ].port=   'E' ,
	GPIO[ 35 ].number=  4,
	GPIO[ 35 ].state=   0,

	//	GPIO[ 36 ].name=   "CS_LORA" ,
	GPIO[ 36 ].port=   'E' ,
	GPIO[ 36 ].number=  5,
	GPIO[ 36 ].state=   0,

	//	GPIO[ 37 ].name=   "CS_EEPROM" ,
	GPIO[ 37 ].port=   'D' ,
	GPIO[ 37 ].number=  10,
	GPIO[ 37 ].state=   0,

	//	GPIO[ 38 ].name=   "CS_FRAM" ,
	GPIO[ 38 ].port=   'D' ,
	GPIO[ 38 ].number=  11,
	GPIO[ 38 ].state=   0,

	//	GPIO[ 39 ].name=   "CS_GYRO" ,
	GPIO[ 39 ].port=   'E' ,
	GPIO[ 39 ].number=  10,
	GPIO[ 39 ].state=   0,

	//	GPIO[ 40 ].name=   "CS_GYRO2" ,
	GPIO[ 40 ].port=   'D' ,
	GPIO[ 40 ].number=  14,
	GPIO[ 40 ].state=   0,

	//	GPIO[ 41 ].name=   "INT_GYRO" ,
	GPIO[ 41 ].port=   'D' ,
	GPIO[ 41 ].number=  13,
	GPIO[ 41 ].state=   0,

	//	GPIO[ 42 ].name=   "INT_GYRO2" ,
	GPIO[ 42 ].port=   'D' ,
	GPIO[ 42 ].number=  15,
	GPIO[ 42 ].state=   0,

	//	GPIO[ 43 ].name=   "CS_PSD1_AMP" ,
	GPIO[ 43 ].port=   'C' ,
	GPIO[ 43 ].number=  4,
	GPIO[ 43 ].state=   0,

	//	GPIO[ 44 ].name=   "CS_PSD2_AMP" ,
	GPIO[ 44 ].port=   'C' ,
	GPIO[ 44 ].number=  5,
	GPIO[ 44 ].state=   0,
};

