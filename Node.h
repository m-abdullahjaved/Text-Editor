#pragma once
#include<iostream>

class Node {
public:
	char data;
	Node* next;
	Node(char dat) {
		data = dat;
		next = NULL;
	}
};