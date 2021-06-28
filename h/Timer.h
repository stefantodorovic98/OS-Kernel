/*
 * Timer.h
 *
 *  Created on: Aug 12, 2019
 *      Author: OS1
 */

#ifndef TIMER_H_
#define TIMER_H_


#define lockAll asm{\
					pushf;\
					cli;\
				}
#define unlockAll asm popf;

//#define lock Timer::lockFlag = 0;
//#define unlock Timer::lockFlag = 1;\
//		if(Timer::request){dispatch();}

#define lock Timer::lockFlag--;
#define unlock Timer::lockFlag++;\
		if(Timer::request && Timer::lockFlag){dispatch();}


typedef void interrupt (*pInterrupt)(...);

class Timer{
public:

	static volatile int counter;
	static volatile pInterrupt oldRoutine;
	static volatile unsigned int contextOnDemand;
	static volatile unsigned int request;
	static volatile unsigned int lockFlag;

	static void setNewRoutine();
	static void restoreOldRoutine();
	static void interrupt timer(...);

};




#endif /* TIMER_H_ */
