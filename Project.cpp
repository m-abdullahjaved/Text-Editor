#include <iostream>
#include <Windows.h>
#include <conio.h>
#include<iomanip>

#include "Stack.h"  // Stack ADT
#include "String.h" // String ADT

using namespace std;

void welcome();
void mainMenu(); // For Display Menu
void openFile(); // For Opening Existing File
void newFile(); // For Creating New File
void editFile(String&); // For edting Text in File

void welcome() {
	cout << "\n\n\n\n\n\n\t\t\t\t";
	cout << setw(30) << setfill('*') << " ";
	cout << "\n\n\t\t\t\t" << setw(3) << setfill(' ') << " ";
	cout << "STACK BASED TEXT EDITOR\n\n\t\t\t\t";
	cout << setfill('*') << setw(30) << " " << endl;
	Sleep(2000);
}

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
	Stack redo;
	Stack backMove;
	Stack tempPrint; // For printing text on console

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
		ch = _getch();
		if (ch == 26 || ch == 8) { // undo
			if (!undo.isEmpty()) {
				redo.push(undo.peek());
				undo.pop();
				Paragraph.deleteLast();

				tempPrint = backMove;
				while (!tempPrint.isEmpty()) {
					cout << " ";
					tempPrint.pop();
				}

				tempPrint = backMove;
				while (!tempPrint.isEmpty()) {
					cout << "\b";
					tempPrint.pop();
				}
				cout << "\b \b";
				tempPrint = backMove;
				while (!tempPrint.isEmpty()) {
					cout << tempPrint.peek();
					tempPrint.pop();
				}
				tempPrint = backMove;
				while (!tempPrint.isEmpty()) {
					cout << "\b";
					tempPrint.pop();
				}
			}
		}
		else if (ch == -32) { // forward / backward
			ch = _getch();
			if (ch == 'K') {
				if (!undo.isEmpty()) {
					cout << "\b";
					backMove.push(undo.peek());
					undo.pop();
					Paragraph.deleteLast();
				}
			}
			else if (ch == 'M') {
				if (!backMove.isEmpty()) {
					undo.push(backMove.peek());
					Paragraph.insertLast(backMove.peek());
					cout << backMove.peek();
					backMove.pop();
				}
			}
		}
		else if (ch == 25) { // redo
			if (!redo.isEmpty()) {
				cout << redo.peek();
				Paragraph.insertLast(redo.peek());
				undo.push(redo.peek());
				redo.pop();

				tempPrint = backMove;

				while (!tempPrint.isEmpty()) {
					cout << tempPrint.peek();
					tempPrint.pop();
				}

				// Again start from backMove to move the cursor back
				tempPrint = backMove;

				while (!tempPrint.isEmpty()) {
					cout << "\b";
					tempPrint.pop();
				}
			}
		}
		else if (ch == 13 || ch == 19) {
			break;
		}
		else {
			cout << ch;
			Paragraph.insertLast(ch);
			undo.push(ch);

			tempPrint = backMove;

			while (!tempPrint.isEmpty()) {
				cout << tempPrint.peek();
				tempPrint.pop();
			}

			// Again start from backMove to move the cursor back
			tempPrint = backMove;

			while (!tempPrint.isEmpty()) {
				cout << "\b";
				tempPrint.pop();
			}
		}
	}
	while (!backMove.isEmpty()) {
		Paragraph.insertLast(backMove.peek());
		undo.push(backMove.peek());
		backMove.pop();
	}
}

int main() {
	system("Color 70");
	//welcome();
	mainMenu();
	return 0;
}