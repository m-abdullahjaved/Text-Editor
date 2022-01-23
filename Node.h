#pragma once
#include<iostream>
// Node Class used in Stack and String ADT
class Node {
public:
	char data;
	Node* next;
	Node(char dat) {
		data = dat;
		next = NULL;
	}
};