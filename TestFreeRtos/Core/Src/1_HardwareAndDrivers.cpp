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
// Name        : 1_Hardware&Drivers.cpp
// Author      : Stefano Ampolo
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Here are the Device Drivers
//
//============================================================================

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdint.h>
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

#include "string.h"

#include "main.h"
#include "cmsis_os.h"

//FEES RELATED INCLUDES

#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#include <limits.h>

#include "1_HardwareAndDrivers.hpp"




#define FREERTOS

void FEES_Delay( int a){
  #ifdef WINDOWS
  std::this_thread::sleep_for(std::chrono::milliseconds(a));
  #endif // WINDOWS

  #ifdef FREERTOS
  osDelay(a);
  #endif // FREERTOS
}

void FEES_print(int a , uint8_t PrintBuffer[] ){

  #ifdef WINDOWS
  cout << PrintBuffer;
  #endif // WINDOWS

  #ifdef FREERTOS
	switch(a){
        case 1:  HAL_UART_Transmit(&huart1,(uint8_t *) PrintBuffer, strlen(PrintBuffer), 100);
        break;
        case 2:  HAL_UART_Transmit(&huart2,(uint8_t *) PrintBuffer, strlen(PrintBuffer), 100);
        break;
        case 3:  HAL_UART_Transmit(&huart3,(uint8_t *) PrintBuffer, strlen(PrintBuffer), 100);
        break;
        case 4:  HAL_UART_Transmit(&huart6,(uint8_t *) PrintBuffer, strlen(PrintBuffer), 100);
        break;
        case 6:  HAL_UART_Transmit(&huart6,(uint8_t *) PrintBuffer, strlen(PrintBuffer), 100);
        break;
      default:   HAL_UART_Transmit(&huart2,(uint8_t *) PrintBuffer, strlen(PrintBuffer), 100);
        break;
    }
    #endif // FREERTOS
}

void print_SystemTime(){

	#ifdef FREERTOS
	// TEST SERIALE
	char PrintBuffer[]= {" System Time is: Test  "};
	// xTaskGetTickCount();

	FEES_print(1,PrintBuffer);
	FEES_print(2,PrintBuffer);
	FEES_print(3,PrintBuffer);
	FEES_print(4,PrintBuffer);
    #endif // FREERTOS

	#ifdef WINDOWS
	#include <time.h>
	#include <chrono>
	float deltaTime;
	deltaTime = (( std::clock() )) / (float) CLOCKS_PER_SEC;
	cout << "\r  System Time is:  "<< deltaTime << endl;
	#endif // WINDOWS
}


void gpioPrintAll(){
	for( int i=0; i<45 ;i++){
		//printf("GPIO[%d].name= %s \n",i, GPIO[i].name);
	    printf("GPIO[%d].port= %c \n",i, GPIO[i].port);
	    printf("GPIO[%d].number= %d \n",i, GPIO[i].number);
	    printf("GPIO[%d].state= %d \n",i, GPIO[i].state);
	    printf("\n");
	}
}

void gpioPrintStates(){
	for( int i=0; i<45 ;i++){
		    printf("GPIO[%d].state= %d \n",i, GPIO[i].state);
		}
}

void gpioPrintON(){
	for( int i=0; i<45 ;i++){
		if(GPIO[i].state==1){
		    printf("GPIO[%d].state= %d \n",i, GPIO[i].state);
		}
	}
}
void gpioPrintOFF(){
	for( int i=0; i<45 ;i++){
		if(GPIO[i].state==0){
		    printf("GPIO[%d].state= %d \n",i, GPIO[i].state);
		}
	}
}

void gpioPrint(int i){
		//printf("GPIO[%d].name= %s \n",i, GPIO[i].name);
	    printf("GPIO[%d].port= %c \n",i, GPIO[i].port);
	    printf("GPIO[%d].number= %d \n",i, GPIO[i].number);
	    printf("GPIO[%d].state= %d \n",i, GPIO[i].state);
	    printf("\n");
}





