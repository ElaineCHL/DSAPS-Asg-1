
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
bool Redundant(List, LibStudent);
bool printList2(List);

struct Person {						// define a person type
	char	name[20], phone[20];	// user name and phone
	double  money;					// money in bank
};

int main() {
	LibStudent student;
	List stuList;
	string fileName = "student.txt";
	int option;

	cout << "-------------------------------------" << endl;
	cout << "Menu" << endl;
	cout << "-------------------------------------" << endl;
	cout << "1. Read File" << endl
		<< "2. Delete record" << endl
		<< "3. Search student" << endl
		<< "4. Insert book" << endl
		<< "5. Display output" << endl
		<< "6. COmpute and Display Statistics" << endl
		<< "7. Student with Same Book" << endl
		<< "8. Display Warned Student" << endl
		<< "9. Exit" << endl << endl;
	cout << "-------------------------------------" << endl;
	cout << "Please input your option: ";
	cin >> option;

	if (option == 1) {
		ReadFile(fileName, &stuList);
	}


	system("pause");
	return 0;
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