/*
 * PCB.cpp
 *
 *  Created on: Aug 12, 2019
 *      Author: OS1
 */

#include "PCB.h"
#include <dos.h>
#include "SCHEDULE.H"
#include <iostream.h>
#include "Timer.h"
#include "List.h"

volatile PCB* PCB::running = 0;
volatile Thread* PCB::mainThread = 0;

volatile List* PCB::globalPCBList = 0;

//Nit koja ce raditi kada su sve blokirane
volatile PCB* PCB::alonePCB = 0;
volatile Alone* PCB::aloneThread = 0;

static int autoID = -1;

PCB::PCB(Thread* thread,StackSize stackSize,Time timeSlice){
	id=autoID;
	autoID++;
	myThread = thread;
	if(stackSize>65536) size=65536;
	else if(stackSize<defaultStackSize) size=defaultStackSize;
	else size=stackSize;
	size = size/sizeof(unsigned);
	quant = timeSlice;
	state = NEW;
	ss = 0; sp = 0; bp = 0;
	stack = 0;
	list = new List();
	//za potrebe semafora
	time = 0;
	deblockValue = 1;
	globalPCBList->add(this);
}

PCB::~PCB(){
	lock
	globalPCBList->deletePCB(this);
	delete[] stack;
	delete list;
	unlock
}

void PCB::allocate(){
#ifndef BCC_BLOCK_IGNORE
	stack = new unsigned[size];
	stack[size-1] = 0x200; //PSW s aktivnim I
	stack[size-2] = FP_SEG(wrapper);
	stack[size-3] = FP_OFF(wrapper);
	ss = FP_SEG(stack+size-12);
	sp = FP_OFF(stack+size-12);
	bp = FP_OFF(stack+size-12);
	state = READY;
#endif
}

void PCB::wrapper(){
	running->myThread->run();
	lock
	running->state = FINISHED;
	running->list->restoreToScheduler();
	unlock
	dispatch();
}

void PCB::start(){
	if(state!=NEW) return;
	allocate();
	Scheduler::put((PCB*)this);
}

Thread* PCB::createMain(){
	Thread* t = new Thread(defaultStackSize,defaultTimeSlice);
	return t;
}

PCB* PCB::getPCB(Thread* t){
	return t->myPCB;
}

void PCB::waitToComplete(){
	lock
	if(running==this || this->state == FINISHED || this->state == NEW){
		unlock
		return;
	}
	/*Mogu i dodatni uslovi za to da ako je this zavrsila ili je nova da ne radi nista.To je u slucaju da se
	 * vise puta poziva waitToComplete pa da nit kada zavrsi ne stavlja main nit u red,jer se nece restaurirati opet
	 */
	//cout<<"U waitToComplete smo !"<<endl;
	running->state = BLOCKED;
	list->add((PCB*)running);
	unlock
	dispatch();
}


