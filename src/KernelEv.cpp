/*
 * KernelEv.cpp
 *
 *  Created on: Aug 22, 2019
 *      Author: OS1
 */

#include "KernelEv.h"
#include "PCB.h"
#include "Timer.h"
#include "Thread.h"
#include "SCHEDULE.H"
#include "IVTEntry.h"

KernelEv::KernelEv(IVTNo ivt){
	val = 0;
	ivtNo = ivt;
	owner = (PCB*)PCB::running;
	IVTEntry::getIVT(ivtNo)->event = this;
}

KernelEv::~KernelEv(){
	lock
	IVTEntry::getIVT(ivtNo)->event = 0;
	unlock
}

void KernelEv::wait(){
	lock
	if(PCB::running == owner){
		if(val==0){
			PCB::running->state = BLOCKED;
			unlock
			dispatch();
		}else{
			val = 0;
			unlock
		}
	}else{
		unlock
	}
}

void KernelEv::signal(){
	lock
	if(val==0 && owner->state==BLOCKED){
		owner->state=READY;
		Scheduler::put(owner);
	}else
		val = 1;
	unlock
}


