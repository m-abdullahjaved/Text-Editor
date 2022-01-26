#pragma once
#include<iostream>
#include "Node.h"

class Stack {
public:
	Node* top;
	Stack() {
		top = NULL;
	}
	Stack(const Stack& Obj) {
		top = NULL;
		Node* temp = Obj.top;
		Stack Stk;
		while (temp != NULL) {
			Stk.push(temp->data);
			temp = temp->next;
		}
		while (!Stk.isEmpty()) {
			this->push(Stk.peek());
			Stk.pop();
		}
	}
	~Stack() {
		delete top;
		top = NULL;
	}
	void push(char dat) {
		Node* newNode = new Node(dat);
		newNode->next = top;
		top = newNode;
	}
	void pop() {
		if (top != NULL) {
			Node* temp = top;
			top = top->next;
			temp->next = NULL;
			delete temp;
		}
	}
	bool isEmpty() {
		return top == NULL;
	}
	char peek() {
		if (top != NULL)
			return top->data;
		else
			return '\0';
	}
	void operator=(const Stack& Obj) {
		Node* temp = Obj.top;
		Stack Stk;
		while (temp != NULL) {
			Stk.push(temp->data);
			temp = temp->next;
		}
		while (!Stk.isEmpty()) {
			this->push(Stk.peek());
			Stk.pop();
		}
	}
};

