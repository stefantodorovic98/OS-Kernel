/*
 * Semaphor.cpp
 *
 *  Created on: Aug 20, 2019
 *      Author: OS1
 */

#include "Semaphor.h"
#include "Thread.h"//zbog dispatch u unlock
#include "Timer.h"
#include "KernSem.h"

Semaphore::Semaphore(int init){
	lock
	myImpl = new KernelSem(init);
	unlock
}

Semaphore::~Semaphore(){
	lock
	delete myImpl;
	unlock
}

int Semaphore::wait(Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
}

int Semaphore::signal(int n){
	return myImpl->signal(n);
}

int Semaphore::val() const{
	return myImpl->val();
}



