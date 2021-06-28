/*
 * PCB.h
 *
 *  Created on: Aug 12, 2019
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "State.h"
#include "Thread.h"
#include "Alone.h"

class List;

class PCB{
public:
	unsigned ss;
	unsigned sp;
	unsigned bp;
	unsigned* stack;
	Time quant;
	StackSize size;
	State state;
	Thread* myThread;

	List* list;
	int id;

	//za potrebe semafora
	Time time;
	unsigned deblockValue;

	volatile static PCB* running;
	volatile static Thread* mainThread;

	//staticka javna lista pcb koji ce posluziti za manipulaciju s id
	volatile static List* globalPCBList;

	//Nit koja ce raditi kada su sve blokirane
	volatile static PCB* alonePCB;
	volatile static Alone* aloneThread;


	PCB(Thread* thread,StackSize stackSize,Time timeSlice);
	~PCB();

	void allocate();
	void start();


	static void wrapper();
	static Thread* createMain();
	static PCB* getPCB(Thread* t);

	void waitToComplete();
};



#endif /* PCB_H_ */
