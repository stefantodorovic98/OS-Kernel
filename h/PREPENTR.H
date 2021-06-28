/*
 * PREPENTR.H
 *
 *  Created on: Aug 22, 2019
 *      Author: OS1
 */

#ifndef PREPENTR_H_
#define PREPENTR_H_

#include "IVTEntry.h"

#define PREPAREENTRY(ivtNo,callOld)\
void interrupt interrupt##ivtNo(...);\
IVTEntry ivtEntry##ivtNo(ivtNo,interrupt##ivtNo);\
void interrupt interrupt##ivtNo(...){\
	if(callOld) ivtEntry##ivtNo.callOldRoutine();\
	ivtEntry##ivtNo.signalEvent();\
}


#endif /* PREPENTR_H_ */
