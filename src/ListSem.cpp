/*
 * ListSem.cpp
 *
 *  Created on: Aug 20, 2019
 *      Author: OS1
 */

#include "ListSem.h"
#include "List2.h"
#include "KernSem.h"

#include "iostream.h"

ListSem::ListSem(){
	head = 0;
	tail = 0;
}

ListSem::~ListSem(){
	Node* temp = head;

	while(temp!=0){
		Node* clr = temp;
		temp = temp->next;
		delete clr;
	}
	head = 0; tail = 0;
}

void ListSem::addSemaphore(KernelSem* item)volatile{
	Node* temp = new Node();
	temp->data = item;
	temp->next = 0;

	if(head==0) head = temp;
	else tail->next = temp;
	tail = temp;
}

void ListSem::updateSemaphore() volatile{
	Node* temp = head;

	while(temp){
		temp->data->list->updateTime();
		temp=temp->next;
	}
}

void ListSem::deleteSemaphore(KernelSem* item) volatile{
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




