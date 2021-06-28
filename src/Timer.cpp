/*
 * Timer.cpp

 *
 *  Created on: Aug 12, 2019
 *      Author: OS1
 */

#include "Timer.h"
#include "SCHEDULE.H"
#include <iostream.h>
#include <dos.h>
#include "Thread.h"
#include "PCB.h"
#include "State.h"
#include "List.h"
#include "Alone.h"

//za semafore
#include "KernSem.h"
#include "ListSem.h"

volatile int Timer::counter = 20;
volatile pInterrupt Timer::oldRoutine = 0;
volatile unsigned int Timer::contextOnDemand = 0;
volatile unsigned int Timer::request = 0;
volatile unsigned int Timer::lockFlag = 1;

unsigned tss,tsp,tbp;

void Timer::setNewRoutine(){
#ifndef BCC_BLOCK_IGNORE
	lockAll
	oldRoutine = getvect(0x08);
	setvect(0x08,timer);
	setvect(0x60,oldRoutine);
	PCB::globalPCBList = new List();
	PCB::aloneThread = new Alone();
	PCB::alonePCB = PCB::getPCB((Thread*)PCB::aloneThread);
	PCB::aloneThread->start();
	PCB::mainThread = PCB::createMain();
	PCB::running = PCB::getPCB((Thread*)PCB::mainThread);
	PCB::running->state = ACTIVE;
	PCB::running->stack = 0;
	unlockAll
#endif
}

void Timer::restoreOldRoutine(){
#ifndef BCC_BLOCK_IGNORE
	lockAll
	delete PCB::globalPCBList;
	delete PCB::aloneThread;
	delete PCB::mainThread;
	//za semafore
	delete KernelSem::listSem;
	setvect(0x08,oldRoutine);
	unlockAll
#endif
}

extern void tick();

void interrupt Timer::timer(...){

	if(!contextOnDemand){
	#ifndef BCC_BLOCK_IGNORE
			asm int 60h;
	#endif
			tick();
			KernelSem::listSem->updateSemaphore();
	}

	if((contextOnDemand==0) && (counter!=0)) counter--;
	if(((counter==0)&&(PCB::running->quant!=0))||(contextOnDemand==1)){
		if(lockFlag){
			request = 0;
#ifndef BCC_BLOCK_IGNORE
			asm{
				mov tss, ss
				mov tsp, sp
				mov tbp, bp
			}
#endif

			PCB::running->ss = tss;
			PCB::running->sp = tsp;
			PCB::running->bp = tbp;

//			cout<<"Bio je kontekst, Thread "<<PCB::running->id<<endl;
//						asm cli;

			if(PCB::running->state==ACTIVE && PCB::running!=PCB::alonePCB){
				PCB::running->state = READY;
				Scheduler::put((PCB*)PCB::running);
			}
			PCB::running = Scheduler::get();
			if(PCB::running==0) PCB::running = PCB::alonePCB;

			PCB::running->state = ACTIVE;
//			cout<<"Menja se kontekst, Thread "<<PCB::running->id<<endl;
//						asm cli;
			tss = PCB::running->ss;
			tsp = PCB::running->sp;
			tbp = PCB::running->bp;

			counter = PCB::running->quant;

#ifndef BCC_BLOCK_IGNORE
			asm{
				mov ss, tss
				mov sp, tsp
				mov bp, tbp
			}
#endif
		}else{
			request = 1;
		}
	}
	contextOnDemand = 0;
}



