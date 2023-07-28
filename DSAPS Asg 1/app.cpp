
#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"
using namespace std;

bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
bool Display(List, int, int);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
int menu();

bool Redundant(List, LibStudent);
bool printList2(List);

int main() {
	LibStudent stu;
	List stuList;
	string fileName = "student.txt";
	char id[10];
	
	do {
		switch (menu()) {

		case 1: // Read File
			if (!ReadFile(fileName, &stuList)) 
				cout << "Unable to read " << fileName << "." << endl;
			
			else 
				cout << "Read successfully." << endl;
				cout << endl;
				system("pause");
				system("cls");
			
			break;
		case 2: // Delete record
			break;
		case 3: // Search Student
			cout << " Enter Student ID: ";
			cin >> id;
			cout << endl;
			if (SearchStudent(&stuList, id, stu)) {
				cout << "Name: " << stu.name << endl;
				cout << "ID: " << stu.id << endl;
				cout << "Course: " << stu.course << endl;
				cout << "Phone No: " <<stu.phone_no << endl;
				cout << "Total Fine: " << stu.total_fine << endl;
			}
			system("pause");
			system("cls");
			
			break;
		case 4: // Insert book
			break;
		case 5: // Display
			break;
		case 6: // Compute and Display Statistics
			break;

		case 7: // print Stu With Same Book
			break;

		case 8: // Display warned student
			break;

		case 9: // Exit
			return 0;
		}

	} while (1);

	system("pause");
	return 0;
}

int menu() {
	int option;

	cout << "-------------------------------------" << endl;
	cout << "Menu" << endl;
	cout << "-------------------------------------" << endl;
	cout << "1. Read File" << endl
		<< "2. Delete record" << endl
		<< "3. Search student" << endl
		<< "4. Insert book" << endl
		<< "5. Display output" << endl
		<< "6. Compute and Display Statistics" << endl
		<< "7. Student with Same Book" << endl
		<< "8. Display Warned Student" << endl
		<< "9. Exit" << endl << endl;
	cout << "-------------------------------------" << endl;
	cout << "Please input your option: ";
	cin >> option;

	while (cin.fail()) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Not an integer! Enter again: ";
		cin >> option;
	}

	while (option < 1 || option > 9) {
		cout << "Out of range! Enter again: ";
		cin >> option;
	}
	return option;
}

bool Redundant(List list, LibStudent item)
{
	LibStudent temp;
	Node* cur;

	if (list.empty())
		return false;

	//slower method
	for (int i = 1; i <= list.size(); i++)
	{
		if (list.get(i, temp))
		{
			if (temp.compareName2(item))
				return true;
		}
	}
	return false;
}

bool printList2(List list)
{
	Node* cur;

	if (list.empty())
	{
		cout << "\n\nCannot print from an empty list\n";
		return false;
	}

	cur = list.head; //start traversing from the first node

	while (cur != NULL)
	{
		cur->item.print(cout);

		cur = cur->next; //move to next node in the list
	}
	return true;
}

bool ReadFile(string filename, List* stuList) {
	LibStudent student;

	string file = filename;
	ifstream inFile(file);

	char s[256];
	int count = 1;
	char name[20], course[20], phone[20], id[20];

	if (inFile.fail())
		cout << "Unable to open the file!" << endl;

	else {
		while (!inFile.eof()) {
			for (int j = 0; j < 3; j++) {
				inFile >> s;
			}
			inFile >> id;

			for (int j = 0; j < 2; j++) {
				inFile >> s;
			}
			inFile >> name;
			inFile.getline(s, 256);
			strcat_s(name, s);

			for (int j = 0; j < 2; j++) {
				inFile >> s;
			}
			inFile >> course;

			for (int j = 0; j < 3; j++) {
				inFile >> s;
			}
			inFile >> phone;

			strcpy_s(student.id, id);
			strcpy_s(student.name, name);
			strcpy_s(student.course, course);
			strcpy_s(student.phone_no, phone);

			if (!Redundant(*stuList, student))
			{
				stuList->insert(count++, student);

			}
			//stuList.insert(count++, student);
			else
				cout << student.name << "already exist." << endl;
		}
		printList2(*stuList);
		inFile.close();

		return true;
	}
}
bool SearchStudent(List* list, char* id, LibStudent& stu) {

	Node* cur;
	cur = list->head;

	if (list->empty()) {
		cout << "\n\nCannot print from an empty list\n";
		return false;
	}

	else {
		while (cur != NULL) {
			for (int i = 1; i <= list->size(); i++) {
				if (strcmp(cur->item.id, id) == 0) {
					list->get(i, stu);
					return &stu;
				}
				cur = cur->next;
			}

		}
		cout << "\nSTUDENT WITH ID " << id << "IS NOT FOUND IN THE LIST" << endl;
		return false;
	}

}

