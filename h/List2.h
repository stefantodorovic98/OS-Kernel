/*
 * List2.h
 *
 *  Created on: Aug 20, 2019
 *      Author: OS1
 */

#ifndef LIST2_H_
#define LIST2_H_

#include "Semaphor.h"

class PCB;
class KernelSem;

class List2{
public:
	List2(KernelSem* s);
	~List2();

	void block(PCB* item, Time time);
	void unblock();

	void restoreToScheduler();

	void updateTime();

private:
	struct Node{
		PCB* data;
		Node* next;
		Time time;
	};
	Node* head;
	Node* tail;
	KernelSem* sem;
};



#endif /* LIST2_H_ */
