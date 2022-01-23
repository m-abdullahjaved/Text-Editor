#pragma once
#include<iostream>
#include "Node.h"

class Stack {
private:
	Node* top;
public:
	Stack() {
		top = NULL;
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
};