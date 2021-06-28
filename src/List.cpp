/*
 * List.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: OS1
 */

#include "List.h"
#include "SCHEDULE.h"
#include <iostream.h>
#include "PCB.h"

List::List(){
	head=0;
	tail=0;
}

List::~List(){
	Node* temp = head;

	while(temp!=0){
		Node* prev = temp;
		temp = temp->next;
		delete prev;
	}

	head = 0; tail = 0;
}

void List::add(PCB* item){
	Node* temp = new Node();
	temp->data = item;
	temp->next = 0;

	if(head == 0) head = temp;
	else tail->next = temp;
	tail = temp;
}

void List::add(PCB* item) volatile{
	Node* temp = new Node();
		temp->data = item;
		temp->next = 0;

		if(head == 0) head = temp;
		else tail->next = temp;
		tail = temp;
}

void List::restoreToScheduler(){
	Node* temp = head;

	while(temp!=0){
			Node* prev = temp;
			temp = temp->next;
			prev->data->state = READY;
			Scheduler::put(prev->data);
			delete prev;
	}

	head = 0; tail = 0;
}

Thread* List::getById(ID id){
	Node* temp = head;

	while(temp!=0){
		if(temp->data->id==id)
			return temp->data->myThread;
		temp=temp->next;
	}

	return 0;
}
Thread* List::getById(ID id) volatile{
	Node* temp = head;

		while(temp!=0){
			if(temp->data->id==id)
				return temp->data->myThread;
			temp=temp->next;
		}

		return 0;
}

void List::deletePCB(PCB* item) volatile{
	Node* temp = head;
	Node* prev = 0;

	if(temp!=0 && temp->data == item){
		head = head->next;
		if(head == 0) tail = 0;
		delete temp;
		return;
	}

	while(temp!=0 && temp->data!=item){
		prev = temp; temp = temp->next;
	}

	if(temp==0) return;

	if(temp==tail){
		tail = prev;
		prev->next = 0;
	}else{
		prev->next = temp->next;
	}

	delete temp;
}

