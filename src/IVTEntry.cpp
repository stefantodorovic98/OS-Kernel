/*
 * IVTEntry.cpp
 *
 *  Created on: Aug 22, 2019
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "Timer.h"
#include "Thread.h"
#include <dos.h>
#include "KernelEv.h"

IVTEntry* IVTEntry::table[256];

IVTEntry::IVTEntry(IVTNo ivtn,pInterrupt newRoutine){
ivtNo = 0; oldRoutine = 0; event = 0;
#ifndef BCC_BLOCK_IGNORE
	lockAll
	ivtNo = ivtn;
	oldRoutine = getvect(ivtNo);
	setvect(ivtNo,newRoutine);
	table[ivtNo] = this;
	unlockAll
#endif
}

IVTEntry::~IVTEntry(){
#ifndef BCC_BLOCK_IGNORE
	lockAll
	table[ivtNo] = 0;
	oldRoutine();
	setvect(ivtNo,oldRoutine);
	unlockAll
#endif
}

IVTEntry* IVTEntry::getIVT(IVTNo ivtNo){
	return table[ivtNo];
}

void IVTEntry::signalEvent(){
	if(event==0) return;
	event->signal();
	dispatch();
}

void IVTEntry::callOldRoutine(){
	if(oldRoutine==0) return;
	oldRoutine();
}


