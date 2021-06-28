/*
 * Alone.h
 *
 *  Created on: Aug 14, 2019
 *      Author: OS1
 */

#ifndef ALONE_H_
#define ALONE_H_

#include "Thread.h"

class Alone : public Thread{
public:
	Alone():Thread(),number(0){};
	~Alone(){

	}
	void start();
protected:
	void run();
private:
	int number;
};

#endif /* ALONE_H_ */
