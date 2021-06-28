/*
 * Thread.cpp
 *
 *  Created on: Aug 12, 2019
 *      Author: OS1
 */

#include "Thread.h"
#include "PCB.h"
#include "Timer.h"
#include <iostream.h>
#include "List.h"



void dispatch(){
#ifndef BCC_BLOCK_IGNORE
	lockAll
#endif
	Timer::contextOnDemand = 1;
	Timer::timer();
#ifndef BCC_BLOCK_IGNORE
	unlockAll
#endif
}

Thread::Thread(StackSize stackSize,Time timeSlice){
	lock
	myPCB = new PCB(this,stackSize,timeSlice);
	unlock
}

Thread::~Thread(){
	lock
	delete myPCB;
	unlock
}

void Thread::start(){
	lock
	myPCB->start();
	unlock
}

void Thread::waitToComplete(){
	myPCB->waitToComplete();
}

ID Thread::getId(){
	return myPCB->id;
}

ID Thread::getRunningId(){
	return PCB::running->id;
}

Thread* Thread::getThreadById(ID id){
	return PCB::globalPCBList->getById(id);
}


