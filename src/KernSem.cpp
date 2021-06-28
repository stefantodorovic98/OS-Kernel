/*
 * KernSem.cpp
 *
 *  Created on: Aug 20, 2019
 *      Author: OS1
 */

#include "KernSem.h"
#include "List2.h"
#include "Timer.h"
#include "Thread.h"
#include "PCB.h"
#include "ListSem.h"

#include "iostream.h"


static int autoId = 0;

volatile ListSem* KernelSem::listSem = new ListSem();

KernelSem::KernelSem(int ini){
	init = ini;
	id = autoId;
	autoId++;
	list = new List2(this);
	listSem->addSemaphore(this);
}

KernelSem::~KernelSem(){
	lock
	list->restoreToScheduler();
	listSem->deleteSemaphore(this);
	delete list;
	unlock
}

int KernelSem::wait(Time maxTimeToWait){
	lock
	init = init - 1;
	if(init<0){
		PCB::running->state = BLOCKED;
		PCB::running->time = maxTimeToWait;
		list->block((PCB*)PCB::running,maxTimeToWait);
		unlock
		dispatch();
		return PCB::running->deblockValue;
	}
	unlock
	return 1;
}

int KernelSem::signal(int n){
	lock
	if(n<0){
		unlock
		return n;
	}else if(n==0){
		init = init + 1;
		if(init<=0) list->unblock();
		unlock
		return 0;
	}else{
		if(init<0){
			int t = -init;
			int m = 0;
			if(n>t) m = t;
			else m = n;

			for(int i=0;i<m;i++) list->unblock();
			init = init + n;
			unlock
			return m; //broj odblokiranih niti
		}else{
			init = init + n;
			unlock
			return 0;
		}
	}
}

int KernelSem::val() const{
	lock
	int ret = init;
	unlock
	return ret;
}

void KernelSem::incInit(){
	init++;
}

