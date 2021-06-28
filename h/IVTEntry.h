/*
 * IVTEntry.h
 *
 *  Created on: Aug 22, 2019
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "Event.h"

typedef void interrupt (*pInterrupt)(...);

class IVTEntry{
public:
	IVTEntry(IVTNo ivt,pInterrupt newRoutine);
	~IVTEntry();

	static IVTEntry* getIVT(IVTNo ivtNo);

	void signalEvent();

	void callOldRoutine();

private:
	friend class KernelEv;
	static IVTEntry* table[256];
	KernelEv* event;
	pInterrupt oldRoutine;
	IVTNo ivtNo;
};


#endif /* IVTENTRY_H_ */
