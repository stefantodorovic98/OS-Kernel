/*
 * Event.cpp
 *
 *  Created on: Aug 22, 2019
 *      Author: OS1
 */

#include "Event.h"
#include "Timer.h"
#include "Thread.h"
#include "KernelEv.h"

Event::Event(IVTNo ivtNo){
	lock
	myImpl = new KernelEv(ivtNo);
	unlock
}

Event::~Event(){
	lock
	delete myImpl;
	unlock
}

void Event::wait(){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}


