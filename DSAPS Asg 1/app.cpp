
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
bool Display(List*, int, int);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
//bool computeAndDisplayStatistics(List*);
//bool printStuWithSameBook(List*, char*);
//bool displayWarnedStudent(List*, List*, List*);
int menu();

bool Redundant(List, LibStudent);
bool printstuList(List);

int main() {
	LibStudent stu;
	List stuList;
	string fileName = "student.txt";
	string filename = "book.txt";
	char id[10];
	char ID[20];
	
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
			//ReadFile(fileName, &stuList);
			cout << "Please input the student ID you wish to delete: ";
			cin.ignore();
			cin.getline(ID, 20);
			if (DeleteRecord(&stuList, ID)) {
				system("cls");
				cout << "-----------------------------------" << endl;
				cout << "     Updated List after Delete" << endl;
				cout << "-----------------------------------" << endl;
				if (!printstuList(stuList))
					cout << "\nCannot print from empty list.\n";
			}
			else
				cout << "Unable to delete ID" << endl;
			break;
		case 3: // Search Student
			cout << " Enter Student ID: ";
			cin >> id;
			cout << endl;
			if (SearchStudent(&stuList, id, stu)) {
				cout << "Name: " << stu.name << endl;
				cout << "ID: " << stu.id << endl;
				cout << "Course: " << stu.course << endl;
				cout << "Phone No: " << stu.phone_no << endl;
				cout << "Total Fine: " << stu.total_fine << endl;
			}
			system("pause");
			system("cls");

			break;
		case 4: // Insert book	
			if (InsertBook(filename, &stuList))
				cout << "Books inserted successfully!" << endl;
			else	
				cout << "Error inserting books." << endl;

			system("pause");
			system("cls");
			break;
		case 5: // Display
			system("cls");
			int source, detail;
			cout << "Where do you want to display the output (1 - File / 2 - Screen): ";
			cin >> source;
			cout << "Do you want to display book list for every student (1 - YES / 2 - NO): ";
			cin >> detail;
			cout << endl;

			// Call the Display function here with the appropriate parameters
			cout << "DISPLAY OUTPUT\n";
			if (Display(&stuList, source, detail)) {			
			}
			else {
				cout << "Error displaying output.\n";
			}

			system("pause");
			system("cls");
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
	cout << "                Menu" << endl;
	cout << "-------------------------------------" << endl;
	cout << "1. Read File" << endl
		<< "2. Delete record" << endl
		<< "3. Search student" << endl
		<< "4. Insert book" << endl
		<< "5. Display output" << endl
		<< "6. Compute and Display Statistics" << endl
		<< "7. Student with Same Book" << endl
		<< "8. Display Warned Student" << endl
		<< "9. Exit" << endl;
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

bool printstuList(List list)
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

	if (inFile.fail()) {
		cout << "Unable to open the file!" << endl;
		return false;
	}
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

		else
			cout << student.name << " already exist." << endl;
	}
	printstuList(*stuList);
	inFile.close();

	return true;

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

bool DeleteRecord(List *stuList, char *ID) {
	
	type value;
	for (int i = 1; i <= stuList->size(); i++) {
		stuList->get(i, value);
		//cout << value.id << " " << endl;
		if (strcmp(ID, value.id) == 0) {
			cout << ID << endl;
			if(stuList->remove(i)){
				return true;
			}
			return false;
			
		}
		
	}
	return false;
}

bool InsertBook(string filename, List* list) {
	ifstream bookFile(filename);

	if (!bookFile) {
		cout << "Error opening book.txt!\n";
		return false;
	}
	else {

		while (!bookFile.eof()) {

			//Read book.txt
			char studentId[10];
			char author[256], temp[256];
			char title[256];
			char publisher[30];
			char ISBN[11];
			int yearPublished;
			char callNum[20];
			char borrowDate[10];
			char dueDate[10];

			bookFile >> studentId >> author >> title >> publisher >>
				ISBN >> yearPublished >> callNum >> borrowDate >> dueDate;

			
			int borrowDay = 0, borrowMonth = 0, borrowYear = 0;
			int dueDay = 0, dueMonth = 0, dueYear = 0;
			int x = 0, y = 0;
			char day[5] = "", month[5] = "", year[5] = "";

			//Find the date a book is borrowed
			for (int i = 0; i < strlen(borrowDate); i++)
			{
				if (borrowDate[i] != '/') //Find the part of day, month and year
				{
					if (x == 0)
					{
						day[y] = borrowDate[i];
						y++;
					}
					if (x == 1)
					{
						month[y] = borrowDate[i];
						y++;
					}
					if (x == 2)
					{
						year[y] = borrowDate[i];
						y++;
					}
				}
				if (borrowDate[i] == '/' || i == strlen(borrowDate) - 1) //To confirm the corresponding component (day, month, or year) is complete.
				{
					cout << " ";
					if (x == 0)
					{
						day[y] = '\0';
						borrowDay = atoi(day); //convert to integer
					}
					if (x == 1)
					{
						month[y] = '\0';
						borrowMonth = atoi(month); //convert to integer then store into struct
					}
					if (x == 2)
					{
						year[y] = '\0';
						borrowYear = atoi(year); //convert to integer then store into struct
					}
					y = 0;
					x++;
				}
			}

			//Find the date a book is due
			int c = 0, d = 0;
			for (int i = 0; i < strlen(dueDate); i++)
			{	
				if (dueDate[i] != '/') //Find the part of day, month and year
				{
					if (c == 0)
					{
						day[d] = dueDate[i];
						d++;
					}
					if (c == 1)
					{
						month[d] = dueDate[i];
						d++;
					}
					if (c == 2)
					{
						year[d] = dueDate[i];
						d++;
					}
				}
				if (dueDate[i] == '/' || i == strlen(dueDate) - 1) //To confirm the corresponding component (day, month, or year) is complete.
				{
					if (c == 0)
					{
						day[d] = '\0';
						dueDay = atoi(day); //convert to integer
					}
					if (c == 1)
					{
						month[d] = '\0';
						dueMonth = atoi(month); //convert to integert
					}
					if (c == 2)
					{
						year[d] = '\0';
						dueYear = atoi(year); //convert to integer
					}
					d = 0;
					c++;

				}

			}

			//Assuming each month has 30 days, calculate the fine
			//Assuming current date is 29/3/2020
			int dueJulianDay = 0;
			int curJulianDay = 29 + 3 * 30 + 2020 * 360;			
			dueJulianDay = dueDay + dueMonth * 30 + dueYear * 360;

			double fine = 0.00;
			if (curJulianDay > dueJulianDay) {
				int daysLate = curJulianDay - dueJulianDay;
				fine = daysLate * 0.50;
			}


			//Find the student with the given ID and insert the book
			Node* cur = list->head;

			if (cur == NULL) {
				cout << "Please read file first.\n";
				return false;
			}
		
			while (cur != NULL) {
				LibStudent& student = cur->item;
				if (strcmp(student.id, studentId) == 0) { //Find the student with ID

					if (student.totalbook < 15) {

						// Find an empty slot in the books array to insert the book
						int emptySlotIndex = -1;
						for (int i = 0; i < 15; i++) {

							if (student.book[i].author[0] == NULL) {
								emptySlotIndex = i;
								break;
							}
						}
						if (emptySlotIndex != -1) {
							//Insert author
							int a = 0, t = 0;
							char temp[256] = "";
							for (int i = 0; i < strlen(author); i++)
							{
								if (author[i] == '_')
								{
									author[i] = ' '; //Replace underscores with spaces
								}

								if (author[i] != '/')
								{
									temp[t] = author[i];
									t++;
								}
								if (author[i] == '/' || i == strlen(author) - 1)
								{
									temp[t] = '\0';
									t = 0;
									student.book[emptySlotIndex].author[a] = new char[strlen(temp) + 1]; //Allocate memory for each author name
									strcpy(student.book[emptySlotIndex].author[a], temp);
									a++;
								}
							}

							//Insert title
							strcpy(student.book[emptySlotIndex].title, title);
							for (int i = 0; i < strlen(student.book[emptySlotIndex].title); i++) {
								if (student.book[emptySlotIndex].title[i] == '_')
								{
									student.book[emptySlotIndex].title[i] = ' '; //Replace underscores with spaces
								}
							}

							//Insert publisher
							strcpy(student.book[emptySlotIndex].publisher, publisher);
							for (int i = 0; i < strlen(student.book[emptySlotIndex].publisher); i++) {
								if (student.book[emptySlotIndex].publisher[i] == '_')
								{
									student.book[emptySlotIndex].publisher[i] = ' '; //Replace underscores with spaces
								}
							}
							
							//Insert ISBN
							strcpy(student.book[emptySlotIndex].ISBN, ISBN);

							//Insert year published
							student.book[emptySlotIndex].yearPublished = yearPublished;

							//Inser call number
							strcpy(student.book[emptySlotIndex].callNum, callNum);

							//Insert the date a book is borrowed
							student.book[emptySlotIndex].borrow.day = borrowDay;
							student.book[emptySlotIndex].borrow.month = borrowMonth;
							student.book[emptySlotIndex].borrow.year = borrowYear;

							//Insert the date a book is due
							student.book[emptySlotIndex].due.day = dueDay;
							student.book[emptySlotIndex].due.month = dueMonth;
							student.book[emptySlotIndex].due.year = dueYear;

							//Insert fine
							student.book[emptySlotIndex].fine = fine;
						}
						student.totalbook++;
						student.total_fine = student.calculateTotalFine();
						
					}
					else {
						cout << "Student with ID: " << studentId << " already borrowed maximum books (15)." << endl;
					}
				}
				cur = cur->next;
			}			
		}
		bookFile.close();
		return true;
	}
}

bool Display(List* list, int source, int detail) {
	if (list == NULL) {
		cout << "Error: List is empty." << endl;
		return false();
	}

	// Create an output stream (file or screen)
	ostream* output;
	ofstream outputFile;
	if (source == 1) {
		outputFile.open("student_info.txt"); // Open the file for writing
		if (!outputFile.is_open()) {
			cout << "Error opening file for writing." << endl;
			return false;
		}
		output = &outputFile;
		
	}
	else if (source == 2) {
		output = &cout;
	}
	else {
		cout << "Invalid source. Use 1 for file or 2 for screen." << endl;
		return false;
	}

	//Iterate through the list and display the information
	Node* cur = list->head;
	int stuNum = 1;
	while (cur != NULL) {
		LibStudent& student = cur->item;
	
		// Calculate total fine before displaying it
		student.calculateTotalFine();
		*output << "STUDENT " << stuNum++ << "\n\n";
		*output << "Name: " << student.name << endl;
		*output << "Id: " << student.id << endl;
		*output << "Course: " << student.course << endl;
		*output << "Phone No: " << student.phone_no << endl;
		*output << "Total Fine: " << student.total_fine << endl;
		*output << endl;

	
		if (detail == 1) {
			*output << "BOOK LIST:" << "\n\n";			
			for (int i = 0; i < student.totalbook; i++) {
				*output << "BOOK " << i + 1 << "\n\n";
				*output << "Title: " << student.book[i].title << endl;
				*output << "Author: ";
				for(int j = 0;j < 10 ;j++){
					if (student.book[i].author[j] != NULL) {
						*output << student.book[i].author[j] << "\t" ;
					}
				}	
				*output << endl;
				*output << "Publisher: " << student.book[i].publisher << endl;
				*output << "Year Published: " << student.book[i].yearPublished << endl;
				*output << "ISBN: " << student.book[i].ISBN << endl;
				*output << "Call Number: " << student.book[i].callNum << endl;
				*output << "Borrow Date: " << student.book[i].borrow.day << "/" << student.book[i].borrow.month << "/" << student.book[i].borrow.year << endl;
				*output << "Due Date: " << student.book[i].due.day << "/" << student.book[i].due.month << "/" << student.book[i].due.year << endl;
				*output << "Fine: " << student.book[i].fine << "\n\n";
			}
		}

		*output << "*****************************************************************************" << endl;

		cur = cur->next;
	}
	outputFile.close();
	return true;

}