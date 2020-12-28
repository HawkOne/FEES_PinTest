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
 * File:FiniteStateMachine.h
 *
 *  Created on: 10 apr 2019
 *      Author: Stefano
 */

#ifndef APPLICATIONSANDFSM_HPP
#define APPLICATIONSANDFSM_HPP

#define TRUE true
#define FALSE false



#include "1_HardwareAndDrivers.hpp"
#include "2_ThreadsAndHandlers.hpp"
#include "3_ApplicationAndFSM.hpp"




enum state_t {
	RECOVER_PREV_STATE = 0, 	// First State after BOOT.
    IN_VECTOR, 					// FEES inside the vector, both Switches still connected
    WAIT_FIRST_TIMER, 			// FEES out of the launcher - First Timer on, 30'
    DETUMBLE_SECOND_TIMER, 		// FEES Detumbling , Second Timer on, Angular speed limit to be decided.
    NOMINAL, 					// FEES NOMINAL STATE - Everything Good.
    TRANSMISSION, 				// FEES Transmission State, Everything else is off.
    RADEX_MODE, 				// FEES RADEX MODE - Programmed Experiment.
};



// DEFINIZIONE DELLE CONSTANTI (IMPOSTAZIONI DI MISSIONE)
const int CONST_SILENZIO_RADIO = 3600 ; // 30 min  --> Requisito di silenzio radio
const int DETHUMBLING_TIMER  = 600 ; 	// 10 min  --> Timer massimo di Dethumbling
const int CONST_RADEX_TIMER = 300;  	// 5 min --> Timer Time-Out del Rad-ex
const int CONST_TRX_TIMER = 300;		// 5 min --> Timer Time-Out Trasmissione
const float CONST_angular_velocity_Limit = 50;	// Valore di Angular_velocity_Limite (per concludere il dethumbling)



void Main_FEES();

void criticalMemoryRead();

void TripleMemoryCheck();

void ParityBitCheck();





class finiteStateMachine {

public:

	void set(state_t a);
	void setPrev(state_t a);
	state_t get();
	state_t getPrev();


	void print_State();
	void print_Menu();
	void print_StateList();
	void print_Variables();
	void event_Handler();
	void human_event_Handler(int a);
	float sample_angular_velocity();


	bool switch_vector;
	bool beacon_received;
	bool radex_scheduled;
	bool radex_finished;
	bool transmission_finished;


	float first_timer;
	float second_timer;
	float timer_for_radex;
	float trx_timer;
	float radex_timer;
	float angular_velocity;

	// Constructor - Destructor
	finiteStateMachine();
	virtual ~finiteStateMachine();

private:
	state_t state;
	state_t previous_state;
};




#endif 	/* APPLICATIONSANDFSM_HPP */

