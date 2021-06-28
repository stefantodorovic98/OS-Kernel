/*
 * List.h
 *
 *  Created on: Aug 13, 2019
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_

#include "Thread.h"

class PCB;

class List{

public:
	List();
	~List();

	void add(PCB* item);
	void add(PCB* item) volatile;
	void restoreToScheduler();


	void deletePCB(PCB* item) volatile;

	Thread* getById(ID id);
	Thread* getById(ID id) volatile;
private:
	struct Node{
		PCB* data;
		Node* next;
	};
	Node* head;
	Node* tail;

};





#endif /* LIST_H_ */
