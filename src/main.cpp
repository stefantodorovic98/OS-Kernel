/*
 * main.cpp
 *
 *  Created on: Aug 12, 2019
 *      Author: OS1
 */
#include <iostream.h>
#include "Timer.h"
#include "Thread.h"
#include "PCB.h"

extern int userMain(int argc, char* argv[]);

int main(int argc,char* argv[]){
	Timer::setNewRoutine();
	int d = userMain(argc,argv);
	Timer::restoreOldRoutine();
	cout<<"Kraj za kraj."<<endl;
	return d;
}



