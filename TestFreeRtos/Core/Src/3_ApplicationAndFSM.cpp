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
 * File:FiniteStateMachine.cpp
 *
 *  Created on: 10 apr 2019
 *      Author: Stefano
 */


#include "1_HardwareAndDrivers.hpp"
#include "2_ThreadsAndHandlers.hpp"
#include "3_ApplicationAndFSM.hpp"

#include <iostream>
#include <cstdlib>
#include <cstdint>



using namespace std;

//   States I/O Modifier
// Serve a far in modo che la Cout dia il "Nome" dello stato e non il valore numerico (enum).
std::ostream& operator<<(std::ostream& out, const state_t value) {
    const char* s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
    switch (value) {
            PROCESS_VAL(RECOVER_PREV_STATE);
            PROCESS_VAL(IN_VECTOR);
            PROCESS_VAL(WAIT_FIRST_TIMER);
            PROCESS_VAL(DETUMBLE_SECOND_TIMER);
            PROCESS_VAL(NOMINAL);
            PROCESS_VAL(TRANSMISSION);
            PROCESS_VAL(RADEX_MODE);
    }
#undef PROCESS_VAL
    return out << s;
}




void Main_FEES(){

	FEES_print( 2 ,  "System Time is: ");
	FEES_print( 2 ,  "\n ");
	FEES_print( 2 ,  "\n ");

	#ifdef WINDOWS
	startTime = clock(); // Samples the start time (needed to calculate the SystemTime)
	#endif // WINDOWS


	// fsm.print_StateList(); 	// Prints out the State list of the FEES System
	// fsm.print_Menu();		// Prints out the User-Menu for keyboard Control over the System

	FEES_print( 2 , "\n ");

	// cin.get(); 	// Keyboard Sampling


	//System Threads

	// thread threadADCS( thread_ADCS);		// Thread for Attitude Determination and Control System.
	// thread threadBatteryPID( thread_BatteryPID);	// Thread for Battery thermal management (PID control)
	// thread threadHardwareWD( thread_HardwareWD);	// Thread for cyclical reset of the Hardware Watchdog
	// thread threadTransmissionWD(thread_TransmissionWD);	// Thread for cyclical sending of the Radio Ping ( Space law requirement)

	// thread threadFSM(thread_Fsm); // This thread Handles the FiniteStateMachine and the Pinmask - it Handles the full Housekeeping of the Satellite.

	//// User - Testing Threads

	// thread threadUserShell(thread_UserShell); // This tread handles the output on screen (PC)



	while(1)
		{
		FEES_print( 2 ,  "--> Dai un comando - Esegui un evento: ");
		FEES_print( 2 ,  "\n ");
		FEES_print( 2 ,  "\n ");

		FEES_print( 2 ,  "--> Dai un comando - Esegui un evento: ");
		FEES_print( 2 ,  "\n ");
		FEES_print( 2 ,  "\n ");

		/*
		int input;
		cin >> input;
		while (!cin.good())
			{
		    cin.clear();
		    cin.ignore(INT_MAX, '\n');
		    cout << " Non e' stato inserito un valore corretto! (int)" << endl << flush ;
		    cout << "Esegui un evento: " << endl;
		    cin >> input;
			}
		fsm.human_event_Handler(input);
		*/
	    }

}


void criticalMemoryRead(){ // Funzione di stub per il recupero memoria esecuzione precedente
	//Da scrivere una funzione che legga dalle 3 memorie e che compari i dati delle 3 e che accetti solo i dati
	// convalidati come attendibili (>=2)

	// if(TripleMemoryCheck()==0){
	cout << " Memoria critica non trovata - ( Nessuno Stato precedente trovato ) -> Procedo al primo boot " << endl << endl ;
	//}
}

void TripleMemoryCheck(){// Funzione di stub per il confronto della memoria ( 2 su 3 )
	//Da scrivere una funzione che legga dalle 3 memorie e che compari i dati delle 3 e che accetti solo i dati
	// convalidati come attendibili (>=2)

	// if(TripleMemoryCheck()==0){
	cout << " Memoria critica non trovata - ( Nessuno Stato precedente trovato ) -> Procedo al primo boot " << endl << endl ;
	//}
}

void ParityBitCheck(){
	// Funzione di stub per il confronto del bit di parità.
}




finiteStateMachine::finiteStateMachine() {
	//  Auto-generated constructor stub
	this->state = RECOVER_PREV_STATE;	// La FSM inizia con lo stato "Recupera Stato precedente"

	criticalMemoryRead(); // Stub di recupero memoria precedente
	// Nel caso in cui esista una memoria di stato precedente la si imposta come stato attuale.

	//-Definizione delle variabili di oggetto

	previous_state = RECOVER_PREV_STATE;	// Quando si inizializza il sistema si parte dal recupero dello stato precedente ( o stato iniziale)

	//FLAGS
	switch_vector= FALSE;			// Flag dello Switch Meccanico Cubesat-Lanciatore  0 = Attached, 1 = Detached. (Se switch_vector==0 (FALSE)  il thread di campionamento dello switch sar� attivo.)
	beacon_received=FALSE;			// Flag di Beacon Received
	radex_scheduled=FALSE;			// Flag di Radex Scheduled
	radex_finished=FALSE;			// Flag di Radex Finished
	transmission_finished=FALSE;	// Flag di Fine Trasmissione


	//TIMERS
	first_timer= CONST_SILENZIO_RADIO ; 		// 30 min  --> Requisito di silenzio radio
	second_timer = DETHUMBLING_TIMER ; 		// 10 min  --> Timer massimo di Dethumbling
	timer_for_radex = 0;		// Timer di Scheduling del Rad-ex
	radex_timer = CONST_RADEX_TIMER;			// Timer Time-Out del Rad-ex
	trx_timer = CONST_TRX_TIMER;			// Timer Time-Out Trasmissione
	angular_velocity= 8888888;	// Valore di inizializzazione Angular_velocity
}


finiteStateMachine::~finiteStateMachine() {
	//  Auto-generated destructor stub
}


// Setters & Getters
void finiteStateMachine::set(state_t a){
	this->state=a;
	this->previous_state=a;
	Update_Pin_Mask(a);
	return;
}
void finiteStateMachine::setPrev(state_t a){
	this->previous_state=a;
	return;
}
state_t finiteStateMachine::get(){
	return this->state;
}
state_t finiteStateMachine::getPrev(){
	return this->previous_state;
}


// Printers
void finiteStateMachine::print_State(){
	cout << "\r  The current state is : " << state << endl <<endl << flush;
	return;
}
void finiteStateMachine::print_StateList(){

	cout << " The State-List is the following: " <<endl << endl;
	cout << " RECOVER_PREV_STATE " << endl;
	cout << " IN_VECTOR" << endl;
	cout << " WAIT_FIRST_TIMER" << endl;
	cout << " DETUMBLE_SECOND_TIMER" << endl;
	cout << " NOMINAL" << endl;
	cout << " TRANSMISSION" << endl;
	cout << " RADEX_MODE" << endl << endl;

	cin.get();  //system("PAUSE");
}
void finiteStateMachine::print_Menu(){

	cout << " \n   READ THIS MENU - These are the Possible Commands-Events: \n" << endl;
	cout << " 1 - Detach launcher's switches - This event starts the System " << endl;
	cout << " 2 - First Timer Finish         - This event quits the wait state  " << endl;
	cout << " 3 - Second Timer Finish -(DeltaW< Wset)- quits the Dethumbling state" << endl;
	cout << " 4 - Receive Beacon from Earth  - Enters the transmission state" << endl;
	cout << " 5 - Schedule Radex ( type in the timer duration after choosing this ) " << endl;
	cout << " 6 - Not used				  " << endl;
	cout << " 7 - SET Transmission to Finished  " << endl;
	cout << " 8 - SET RADEX to Finished  " << endl << endl << flush;
}
void finiteStateMachine::print_Variables(){
		cout << "\r --- Flags and Counters --- " << endl
			 <<	"\r  Outside the Rocket?     -->\t" << boolalpha << this->switch_vector << endl
			 << "\r  Timer 30 minutes        -->\t" << this->first_timer << endl
			 << "\r  Dethumbling timer       -->\t" << this->second_timer << endl
			 << "\r  Radex Scheduled?        -->\t" << boolalpha << this->radex_scheduled << endl
			 << "\r  Timer-Scheduler Radex   -->\t" << this->timer_for_radex << endl
			 << "\r  Radex-Out Timer         -->\t" << this->radex_timer<< endl
			 << "\r  Transmission timer      -->\t" << this->trx_timer << endl
			 << "\r  Beacon Received         -->\t" << boolalpha << this->beacon_received << endl
			 << "\r  Transmission finished   -->\t" << boolalpha << this->transmission_finished << endl
			 << "\r  Previous State          -->\t" << this->previous_state << endl << endl << flush;

}

// Handlers
void finiteStateMachine::event_Handler(){
	if((this->state==RECOVER_PREV_STATE)){
		if(this->previous_state != RECOVER_PREV_STATE){	 //If there is a Saved previous state -
			this->set(previous_state);} //This line recovers the previous state, if available.

		else if(this->switch_vector==0){this->set(IN_VECTOR);}
		else if(this->first_timer  !=0){this->set(WAIT_FIRST_TIMER);}
		else if(this->second_timer !=0){ this->set(DETUMBLE_SECOND_TIMER);}
		else if((this->first_timer==0) & (this->second_timer==0)){ this->set(NOMINAL);}
		// These 4 lines decide the current State based on the known variableS
		// If The system Resets in RADEX or Transmission  and there is no reliable previous state in memory it goes back to Nominal.
					}

	// for Timer-Handling (loop this thread at 1hz)

	if(this->state==IN_VECTOR)  {
		if(this->switch_vector!=0){this->set(WAIT_FIRST_TIMER);}
	}


	if(this->state==WAIT_FIRST_TIMER){
	     if(this->first_timer!=0){this->first_timer--;}
	     else{this->set(DETUMBLE_SECOND_TIMER);}
	}


	if(this->state==DETUMBLE_SECOND_TIMER) {
		if(this->second_timer!=0){this->second_timer--;}
		else{this->set(NOMINAL);}
	}


	//if((this->switch_vector!=0) & (this->first_timer==0) & (this->second_timer==0) & (this->state!=TRANSMISSION) & (this->state!=RADEX_MODE)){this->set(NOMINAL); } // Nominal Check



	if(this->state==NOMINAL){
		if((this->radex_scheduled==TRUE) & (this->timer_for_radex != 0)){this->timer_for_radex--;}
		if((this->radex_scheduled==TRUE) & (this->timer_for_radex == 0)) {this->set(RADEX_MODE); this->radex_timer=CONST_RADEX_TIMER; } // Imposto il Timer di Time-out all'ingresso dello stato RADEX
		if(this->beacon_received==TRUE){this->set(TRANSMISSION); this->beacon_received=false; this->trx_timer=CONST_TRX_TIMER; }  //Imposto il Timer di Time-out all'ingresso dello stato Transmission
		// qui volendo si possono inserire azioni da fare ciclicamente in Nominal Mode
	}


	if(this->state==TRANSMISSION){
		Transmission_Watchdog_ON();
		if((this->transmission_finished==true )|( this->trx_timer==0)) {this->set(NOMINAL); Transmission_Watchdog_OFF(); }
		else{this->trx_timer--;}
	}



	if(this->state==RADEX_MODE){
		if((this->radex_finished==true )|(this->radex_timer==0)){ this->set(NOMINAL); this->radex_scheduled=FALSE;}
		else{this->radex_timer--;}
	}
}


void finiteStateMachine::human_event_Handler(int a){
	switch (a){
	case 0:
		this->print_StateList();
		break;
	case 1:
		this->switch_vector= 1;
		break;
	case 2:
		this->first_timer = 0;
		break;
	case 3:
		this->second_timer = 0;
		break;
	case 4:
		//cout << " Beacon received from earth, entering Transmission mode" << endl;
		this->beacon_received=true;
		this->transmission_finished=false;
		this->trx_timer = CONST_TRX_TIMER;
		this->set(TRANSMISSION);
		break;
	case 5:
		//cout << " Scheduling Radiation Experiment " << endl << " Choose how many seconds to wait for radex" << endl;
		cin >> this->timer_for_radex ;
		this->radex_scheduled=true;
		this->radex_finished=false;
		//cout << " This is the new RadexTimer " << timer_for_radex << endl;
		break;
	case 7:
		this->transmission_finished=true;
		break;
	case 8:
		this->radex_finished=true;
		break;

	default:
		cout << " This choice is not correct. \n" <<endl;
		break;
	}
}


float finiteStateMachine::sample_angular_velocity(){
	this->angular_velocity = rand();
	return this->angular_velocity;

}


