/*
 * List2.cpp
 *
 *  Created on: Aug 20, 2019
 *      Author: OS1
 */

#include "List2.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "KernSem.h"

#include "iostream.h"

List2::List2(KernelSem* s){
	sem = s;
	head = 0;
	tail = 0;
}

List2::~List2(){
	Node* temp = head;

	while(temp){
		Node* old = temp;
		temp = temp->next;
		delete old;
	}

	head = 0; tail = 0;
}

void List2::block(PCB* item,Time time){
	Node* temp = new Node();
	temp->data = item;
	temp->next = 0;
	temp->time = time;

	if(head==0) head = temp;
	else tail->next = temp;
	tail = temp;
}

void List2::unblock(){
	if(head==0) return;
	Node* temp = head;
	PCB* ret = temp->data;
	head = head->next;
	if(head==0) tail = 0;

	ret->state = READY;
	ret->deblockValue = 1;
	Scheduler::put(ret);
	//cout<<"Deblokira se Thread"<<ret->id<<endl;
	delete temp;
}

void List2::restoreToScheduler(){
	Node* temp = head;

	while(temp!=0){
		Node* prev = temp;
		temp = temp->next;
		prev->data->state = READY;
		prev->data->deblockValue = 1;
		Scheduler::put(prev->data);
		delete prev;
	}

	head = 0; tail = 0;

}

void List2::updateTime(){
	//cout<<"UPDATE TIME SEMAPHORE"<<endl;
	Node* temp = head;
	Node* prev = 0;
	Node* next = 0;
	Node* clr = 0;

	while(temp!=0){
		if(temp->time!=0){
			if(temp->data->time>0) temp->data->time--;
			if(temp->data->time==0){
				next = temp->next;
				temp->data->state = READY;
				temp->data->deblockValue = 0; //odblokirao se zbog isteka vremena
				Scheduler::put(temp->data);

				//cout<<"Isteklo je vreme za nit"<<temp->data->id<<endl;

				if(temp==head){
					clr = temp;
					head = head->next;
					temp->next = 0;
					if(head==0) tail=0;
				}else if(temp!=head && temp!=tail){
					clr = temp;
					prev->next = temp->next;
					temp->next = 0;
				}else if(temp==tail){
					clr = temp;
					prev->next = 0;
					tail = prev;
				}

				temp = next;
				delete clr;
				sem->incInit();

			}else if(temp->data->time!=0){
				prev = temp;
				temp = temp->next;
			}
		}else if(temp->time==0){
			prev = temp;
			temp = temp->next;
		}

	}
}




