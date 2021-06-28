/*
 * Alone.cpp
 *
 *  Created on: Aug 14, 2019
 *      Author: OS1
 */

#include "Alone.h"
#include "SCHEDULE.H"
#include <iostream.h>
#include "PCB.h"

void Alone::run(){
	while(number<100){
		number++;
		if(number>50) number = 1;
		for(int i = 0; i < 10000; i++)
			for(int j = 0; j < 10000; j++);
	}
}

void Alone::start(){
	Thread::start();
	PCB* T=Scheduler::get();
}
