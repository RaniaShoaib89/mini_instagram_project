#include "ListNode.h"
#include <iostream>
#pragma once
#define STACK_H
using namespace std;

template <typename T>
class Stack {
    ListNode<T>* Top;

public:
    Stack() : Top(nullptr) {}

    void push(T data) {
        ListNode<T>* newnode = new ListNode<T>(data);  
        if (Top == nullptr) {
            Top = newnode;
            return;
        }
        newnode->next = Top;  
        Top = newnode;       
    }

    void pop() {
        if (Top == nullptr) {
            cout << "Stack is empty. Cannot pop." << endl;
            return;
        }
        ListNode<T>* temp = Top;
        Top = Top->next;
        delete temp;
    }

    T top() {
        if (Top == nullptr) {
            throw runtime_error("Stack is empty. No top element.");
        }
        return Top->data;
    }

    void display() {
        if (Top == nullptr) {
            cout << "Stack is empty." << endl;
            return;
        }
        ListNode<T>* temp = Top; 
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;  
        }
        cout << endl;
    }

    bool empty()
    {
        return Top == nullptr;
    }

    Stack(const Stack<T>& original) : Top(nullptr) {
        if (original.Top == nullptr) {
            return;
        }
        Stack<T> temp;
        ListNode<T>* current = original.Top;
        while (current != nullptr) {
         
            temp.push(current->data);
            current = current->next;
        }

      
        while (!temp.empty()) {
            this->push(temp.top());
            temp.pop();
        }
    }

    ~Stack() {
        while (Top != nullptr) {
            pop();
        }
    }
};
