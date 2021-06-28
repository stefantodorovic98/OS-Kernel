/*
 * KernelEv.h
 *
 *  Created on: Aug 22, 2019
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "Event.h"

class PCB;

class KernelEv{
public:
	KernelEv(IVTNo ivt);
	~KernelEv();

	void wait();
	void signal();

private:
	int val;
	IVTNo ivtNo;
	PCB* owner;
};



#endif /* KERNELEV_H_ */
