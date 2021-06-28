/*
 * KernSem.h
 *
 *  Created on: Aug 20, 2019
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_

#include "Semaphor.h"

class List2;
class ListSem;

class KernelSem{
public:
	KernelSem(int ini);
	~KernelSem();

	int wait(Time maxTimeToWait);
	int signal(int n);

	int val() const;

	List2* list;
	void incInit();

	volatile static ListSem* listSem;

private:
	int init;
	int id;
};



#endif /* KERNSEM_H_ */
