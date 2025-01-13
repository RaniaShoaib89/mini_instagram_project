#pragma once
#define LISTNODE_H

template <typename T>
class ListNode
{

public:

	T data;
	ListNode* next;

	ListNode(T data)
	{
		this->data = data;
		next = nullptr;
	}

};

