/*
 * ListSem.h
 *
 *  Created on: Aug 20, 2019
 *      Author: OS1
 */

#ifndef LISTSEM_H_
#define LISTSEM_H_

class KernelSem;

class ListSem{
public:
	ListSem();
	~ListSem();

	void addSemaphore(KernelSem* item) volatile;
	void updateSemaphore() volatile;
	//novo dodato
	void deleteSemaphore(KernelSem* item) volatile;
private:
	struct Node{
		KernelSem* data;
		Node* next;
	};
	Node* head;
	Node* tail;
};



#endif /* LISTSEM_H_ */
