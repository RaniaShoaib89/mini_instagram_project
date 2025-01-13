#include <iostream>
using namespace std;

#include "ListNode.h"
#pragma once
#define QUEUE_H

template <typename T>
class Queue
{
	ListNode<T>* front;
	ListNode<T>* back;


public:
	Queue()
	{
		front = back = nullptr;

	}

	bool empty()
	{
		return front == nullptr;
	}
	void push(T data)
	{
		ListNode<T>* newnode = new ListNode<T>(data);
		if (front == nullptr)
		{
			front = back =  newnode;
			return; 
		}

	    back->next = newnode;
		back = newnode;

	    


		
	}

	void pop()
	{
		if (front == nullptr)
		{
			
			return;
		}

		ListNode<T>* temp = front;
		front = front->next;
		delete temp;
	}

	T Front()
	{
		if (front == nullptr)
		{
			throw runtime_error("Queue is empty. No top element.");
		}
		return front->data;
	}
	Queue(const Queue<T>& original) : front(nullptr), back(nullptr) {
		if (original.front == nullptr) {
			return; 
		}

		
		ListNode<T>* current = original.front;
		while (current != nullptr) {
			this->push(current->data); 
			current = current->next;
		}
	}

	void display()
	{
		ListNode<T>* temp = front;

		while (temp != nullptr)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}

		cout << endl;
	}


};

