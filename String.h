#pragma once
#include<iostream>
#include<fstream>
#include "Node.h"
using namespace std;

class String {
public:
	int Size;
	Node* head;
	String() {
		head = NULL;
		Size = 0;
	}
	String(const char* ch) {
		head = NULL;
		for (int i = 0; ch[i] != '\0'; i++)
			insertLast(ch[i]);

	}
	~String() {
		delete head;
		head = NULL;
	}
	void insertLast(char data) {
		Node* newNode = new Node(data);
		Size++;
		if (head == NULL) {
			head = newNode;
		}
		else {
			Node* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}
	char deleteLast() {
		char ch = '\0';
		if (head == NULL)
			return ch;
		else if (head->next == NULL) {
			ch = head->data;
			delete head;
			head = NULL;
			Size--;
			return ch;
		}
		else {
			Node* temp = head;
			Size--;
			while (temp->next->next != NULL) {
				temp = temp->next;
			}
			ch = temp->next->data;
			delete (temp->next);
			temp->next = NULL;
			return ch;
		}
	}
	int getSize() {
		return Size;
	}
	void PrintFile(const char* fileName) {
		fstream outFile(fileName, ios::out);

		if (!outFile) {
			cerr << "File couldn't be saved\n";
			exit(1);
		}

		Node* temp = head;
		while (temp != NULL) {
			outFile << temp->data;
			temp = temp->next;
		}

		outFile.close();
	}
	
	void ReadFile(const char* fileName) {
		head = NULL;
		fstream inFile(fileName, ios::in);
		if (!inFile) {
			cerr << "File can't be read\n";
			exit(1);
		}
		char ch;
		while (inFile.get(ch)) {
			this->insertLast(ch);
		}

		inFile.close();
	}
};

ostream& operator<<(ostream& output, const String& RHS) {
	Node* temp = RHS.head;
	while (temp != NULL) {
		cout << temp->data;
		temp = temp->next;
	}
	return output;
}