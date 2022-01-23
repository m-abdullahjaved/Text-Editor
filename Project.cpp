#include <iostream>
#include <Windows.h>
#include <conio.h>
#include<iomanip>

#include "Stack.h"  // Stack ADT
#include "String.h" // String ADT

using namespace std;

void openFile(); // For Opening Existing File
void newFile(); // For Creating New File
void editFile(String&); // For edting Text in File

void mainMenu() {
	int choice = 0;
	do {
		system("cls");
		cout << setfill('_') << setw(25) << "_\n\n";
		cout << "Stack Based Text Editor\n";
		cout << setfill('_') << setw(25) << "_\n\n";
		cout << "1. Open File\n2. Create a New File\n3. Exit\n";
		cout << "\n\nEnter Choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			openFile();
			break;
		case 2:
			newFile();
			break;
		case 3:
			exit(0);
			break;
		default:
			cout << "Invalid Choice\n";
			break;
		}
	} while (choice != 3);
}

void openFile() {
	String Paragraph;
	char fileName[50];
	cout << "Enter File Name: ";
	cin >> fileName;
	system("cls");
	Paragraph.ReadFile(fileName);
	editFile(Paragraph);

	Paragraph.PrintFile(fileName);
	system("cls");
	cout << "Saving";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".";
}

void newFile() {
	String Paragraph;
	char fileName[50];
	system("cls");
	editFile(Paragraph);
	system("cls");
	cout << "Enter File Name: ";
	cin >> fileName;
	Paragraph.PrintFile(fileName);
	cout << "Saving";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".";
}

void editFile(String& Paragraph) {
	Stack undo;
	Stack temp;
	
	// **** This will run in case of existing file **** //
	Node* current = Paragraph.head;
	for (int i = 0; i < Paragraph.getSize(); i++) {
		cout << current->data;
		undo.push(current->data);
		current = current->next;
	}
	// **** This will run in case of existing file **** //

	char ch;
	while (true) {
		ch = getch();
		if (ch == 26 || ch == 8) { // undo
			if (!undo.isEmpty()) {
				temp.push(undo.peek());
				undo.pop();
				Paragraph.deleteLast();
				cout << "\b \b";
			}
		}
		else if (ch == 25) { // redo
			if (!temp.isEmpty()) {
				cout << temp.peek();
				Paragraph.insertLast(temp.peek());
				undo.push(temp.peek());
				temp.pop();
			}
		}
		else if (ch == 13 || ch == 19) {
			break;
		}
		else {
			cout << ch;
			Paragraph.insertLast(ch);
			undo.push(ch);
		}
	}
}

int main() {
	system("Color 70");
	mainMenu();
	return 0;
}