
#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	<iomanip>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"
using namespace std;

bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
bool Display(List*, int, int);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
int menu();

bool Redundant(List, LibStudent);
int calcJulianDate(int, int, int);


int main() {
	LibStudent stu;
	List* stuList = new List;
	List* type1 = new List; // used in displayWarnedStudent function
	List* type2 = new List; // used in displayWarnedStudent function
	string fileName = "student.txt";
	string filename = "book.txt";
	char id[10];
	char ID[20];
	char* callNum = new char; // used in printStuWithSameBook function

	if (!ReadFile(fileName, stuList))
		cout << "Unable to read " << fileName << "." << endl;
	if (!InsertBook(filename, stuList))
		cout << "Error inserting books." << endl;

	do {
		switch (menu()) {

		case 1: // Read File
			if (!ReadFile(fileName, stuList))
				cout << "Unable to read " << fileName << "." << endl;

			else
				cout << "Read successfully." << endl;
			cout << endl;

			system("pause");
			system("cls");
			break;

		case 2: // Delete record
			cout << "Please input the student ID you wish to delete: ";
			cin.ignore();
			cin.getline(ID, 20);
			if (DeleteRecord(stuList, ID)) {
				cout << ID << " is successfully deleted." << endl;
			}
			else
				cout << "Unable to delete ID" << endl;
			system("pause");
			system("cls");
			break;

		case 3: // Search Student
			cout << endl;
			cout << "Enter Student ID: ";
			cin >> id;
			if (SearchStudent(stuList, id, stu)) {
				stu.print(cout);
			}
			else
				cout << "\nSTUDENT WITH ID " << id << " IS NOT FOUND IN THE LIST" << endl;

			system("pause");
			system("cls");
			break;

		case 4: // Insert book	
			if (InsertBook(filename, stuList)) {
				cout << "\nBooks inserted successfully!" << endl;
			}
			else
				cout << "Error inserting books." << endl;

			system("pause");
			system("cls");
			break;

		case 5: // Display output
			system("cls");
			int source, detail;
			cout << "DISPLAY OUTPUT\n\n";
			cout << "Where do you want to display the output (1 - File / 2 - Screen): ";
			cin >> source;
			cout << "Do you want to display book list for every student (1 - YES / 2 - NO): ";
			cin >> detail;
			cout << endl;

			// Call the Display function here with the appropriate parameters
			if (Display(stuList, source, detail)) {
				cout << "\nSuccessfully display output.\n\n";
			}
			else {
				cout << "Error displaying output.\n";
			}

			system("pause");
			system("cls");
			break;

		case 6: // Compute and Display Statistics
			system("cls");
			cout << "DISPLAY STATISTICS\n\n";
			computeAndDisplayStatistics(stuList);

			system("pause");
			system("cls");
			break;

		case 7: // print Stu With Same Book
			cout << "\nEnter call number of book: ";
			cin >> callNum;
			if(!printStuWithSameBook(stuList, callNum)) {
				cout << "Print failed.\n\n";
			}
			system("pause");
			system("cls");
			break;

		case 8: // Display warned student
			if (!displayWarnedStudent(stuList, type1, type2))
				cout << "Unable to display warned student." << endl;
			cout << "\n=============================================================\n";
			cout << "                        List type1\n";
			cout << " (Student who has > 2 books that are overdue for >= 10 days)\n";
			cout << "=============================================================\n" << endl;
			Display(type1, 2, 1); // display type1 in the screen with student info and book list.

			cout << "\n";
			cout << "\n================================================================\n";
			cout << "                       List type2\n";
			cout << " (Student whose total fine is > RM 50.00 and every book is due)\n";
			cout << "================================================================\n" << endl;
			Display(type2, 2, 1); // display type2 in the screen with student info and book list.

			system("pause");
			system("cls");
			break;

		case 9: // Exit
			return 0;
		}
	} while (1);
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
	cout << "Please input your option (1-9): ";
	cin >> option;

	while (option < 1 || option > 9) {
		cout << "Out of range! Enter again: ";
		cin >> option;
	}

	while (cin.fail()) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Not an integer! Enter again: ";
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
		for (int j = 0; j < 3; j++) {  //the for loop in the function is to skip the unwanted info in the txt file
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

		strcpy_s(student.id, id);  //copy the student id, name, course and phone_no into the student struct
		strcpy_s(student.name, name);
		strcpy_s(student.course, course);
		strcpy_s(student.phone_no, phone);

		if (!Redundant(*stuList, student)) { //if the student is not found in the list, insert the student info (stored in struct) into the list
			stuList->insert(student);
		}
		else
			cout << student.name << " already exist." << endl;
	}
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
	while (cur != NULL) {
		for (int i = 1; i <= list->size(); i++) { 
			if (strcmp(cur->item.id, id) == 0) { // Compare the student ID of the current node with the provided ID
				list->get(i, stu); // If match if found, retrieve the student data from the list 
				return true;
			}
			cur = cur->next;
		}
	}
	return false;
}

bool DeleteRecord(List *stuList, char *ID) {
	
	type value;
	for (int i = 1; i <= stuList->size(); i++) {
		stuList->get(i, value);		//browse through the list and access the item in the list
		if (strcmp(ID, value.id) == 0) {	//compare the id want to dlt with the id in the list
			if(stuList->remove(i)){		//if the comparison is same, dlt the student info
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
		cout << "Error opening book.txt\n";
		return false;
	}
	Node* temp;
	for (temp = list->head; temp != NULL; temp = temp->next) {
		temp->item.totalbook = 0;
	}

	// Read book.txt
	while (!bookFile.eof()) {
		char studentId[10];
		char author[256];
		char title[256];
		char publisher[30];
		char ISBN[11];
		int yearPublished;
		char callNum[20];
		char borrowDate[10];
		char dueDate[10];
		int borrowDay = 0, borrowMonth = 0, borrowYear = 0;
		int dueDay = 0, dueMonth = 0, dueYear = 0;
		int x = 0, y = 0;
		char day[5] = "", month[5] = "", year[5] = "";

		bookFile >> studentId >> author >> title >> publisher >>
			ISBN >> yearPublished >> callNum >> borrowDate >> dueDate;

		// Read the date a book is borrowed
		for (int i = 0; i < strlen(borrowDate); i++)
		{
			if (borrowDate[i] != '/') // Identify the part for day, month and year
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
			if (borrowDate[i] == '/' || i == strlen(borrowDate) - 1) // Check if the date has completed read
			{
				cout << " ";
				if (x == 0)
				{
					day[y] = '\0';
					borrowDay = atoi(day); // convert to integer
				}
				if (x == 1)
				{
					month[y] = '\0';
					borrowMonth = atoi(month);
				}
				if (x == 2)
				{
					year[y] = '\0';
					borrowYear = atoi(year);
				}
				y = 0;
				x++;
			}
		}

		// Read the date a book is due
		int c = 0, d = 0;
		for (int i = 0; i < strlen(dueDate); i++)
		{
			if (dueDate[i] != '/') // Identify the part for day, month and year
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
			if (dueDate[i] == '/' || i == strlen(dueDate) - 1) // Check if the date has completed read
			{
				if (c == 0)
				{
					day[d] = '\0';
					dueDay = atoi(day); // Convert to integer
				}
				if (c == 1)
				{
					month[d] = '\0';
					dueMonth = atoi(month);
				}
				if (c == 2)
				{
					year[d] = '\0';
					dueYear = atoi(year);
				}
				d = 0;
				c++;
			}
		}

		// Assuming current date is 29/3/2020
		int daysLate = calcJulianDate(29, 3, 2020) - calcJulianDate(dueDay, dueMonth, dueYear);
		double fine = 0.0;

		// Calculate the fine
		if (daysLate > 0) {
			 fine = daysLate * 0.5;
		}

		// Find the student based on ID and insert the book
		Node* cur = list->head;
		if (cur == NULL) {
			cout << "Please read file first.\n";
			return false;
		}
		while (cur != NULL) {
			LibStudent& student = cur->item;
			if (strcmp(student.id, studentId) == 0) { // Find the student based on ID
				
				if (student.totalbook < 15) {
					
					// Check if the student has borrowed any books and detect the empty slot for inserting other books
					int emptySlotIndex = -1;
					for (int i = 0; i < 15; i++) {

						if (student.book[i].author[0] == NULL) {
							emptySlotIndex = i;
							break;
						}
					}
					if (emptySlotIndex != -1) {
						
						// Insert author
						int a = 0, t = 0;
						char temp[256] = "";
						for (int i = 0; i < strlen(author); i++)
						{
							if (author[i] == '_')
							{
								author[i] = ' '; // Replace underscores with spaces
							}

							if (author[i] != '/')
							{
								temp[t] = author[i];
								t++;
							}
							// Check if the current character is the end of the first author's name or the last character
							if (author[i] == '/' || i == strlen(author) - 1)
							{
								temp[t] = '\0';
								t = 0;
								student.book[emptySlotIndex].author[a] = new char[strlen(temp) + 1]; // Allocate memory for each author name
								strcpy(student.book[emptySlotIndex].author[a], temp);
								a++;
							}
						}

						// Insert title
						strcpy(student.book[emptySlotIndex].title, title);
						for (int i = 0; i < strlen(student.book[emptySlotIndex].title); i++) {
							if (student.book[emptySlotIndex].title[i] == '_')
							{
								student.book[emptySlotIndex].title[i] = ' '; // Replace underscores with spaces
							}
						}

						// Insert publisher
						strcpy(student.book[emptySlotIndex].publisher, publisher);
						for (int i = 0; i < strlen(student.book[emptySlotIndex].publisher); i++) {
							if (student.book[emptySlotIndex].publisher[i] == '_')
							{
								student.book[emptySlotIndex].publisher[i] = ' '; // Replace underscores with spaces
							}
						}

						// Insert ISBN
						strcpy(student.book[emptySlotIndex].ISBN, ISBN);

						// Insert year published
						student.book[emptySlotIndex].yearPublished = yearPublished;

						// Inser call number
						strcpy(student.book[emptySlotIndex].callNum, callNum);

						// Insert the date a book is borrowed
						student.book[emptySlotIndex].borrow.day = borrowDay;
						student.book[emptySlotIndex].borrow.month = borrowMonth;
						student.book[emptySlotIndex].borrow.year = borrowYear;

						// Insert the date a book is due
						student.book[emptySlotIndex].due.day = dueDay;
						student.book[emptySlotIndex].due.month = dueMonth;
						student.book[emptySlotIndex].due.year = dueYear;

						// Insert fine
						student.book[emptySlotIndex].fine = fine;
					}
					student.totalbook++;
					student.calculateTotalFine();

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

bool Display(List* list, int source, int detail) {
	if (list->empty()) {
		cout << "Error: List is empty." << endl;
		return false;
	}
	// Create an output stream (file or screen)
	ostream* output;
	ofstream outputFile;
	if (source == 1) {
		if (detail == 1) {
			outputFile.open("student_booklist.txt"); // Open the file for writing
			if (!outputFile.is_open()) {
				cout << "Error opening file for writing." << endl;
				return false;
			}
			cout << "Successfully display output to student_booklist.txt." << endl;
		}
		else if (detail == 2) {
			outputFile.open("student_info.txt"); // Open the file for writing
			if (!outputFile.is_open()) {
				cout << "Error opening file for writing." << endl;
				return false;
			}
			cout << "Successfully display output to student_info.txt." << endl;
		}
		else {
			cout << "Invalid detail input. Use 1 for student info or 2 for book list." << endl;
			return false;
		}
		output = &outputFile;
	}

	else if (source == 2) {
		if (detail != 1 && detail != 2) {
			cout << "Invalid detail input. Use 1 for student info or 2 for book list." << endl;
			return false;
		}
		output = &cout;
	}
	else {
		cout << "Invalid source. Use 1 for file or 2 for screen." << endl;
		return false;
	}

	Node* cur = list->head;
	int stuNum = 1;
	while (cur != NULL) {
		LibStudent& student = cur->item;
		// Display students' detail from student list
		*output << "\nSTUDENT " << stuNum++;
		student.print(*output);
		*output << endl;

		if (detail == 1) {
			// Display books' detail from student list
			*output << "BOOK LIST:" << "\n\n";
			for (int i = 0; i < student.totalbook; i++) {
				*output << "BOOK " << i + 1 << "\n";
				student.book[i].print(*output);
				*output << endl;
			}
		}
		*output << "*****************************************************************************" << endl;
		cur = cur->next;
	}		
	outputFile.close();	
	return true;
}

bool computeAndDisplayStatistics(List* list) {
	Node* cur;
	cur = list->head;
	int CS = 0, IA = 0, IB = 0, CN = 0, CT = 0;
	int CStotalBook = 0, IAtotalBook = 0, IBtotalBook = 0, CNtotalBook = 0, CTtotalBook = 0;
	int CStotalOverDueBook = 0, IAtotalOverDueBook = 0, IBtotalOverDueBook = 0, CNtotalOverDueBook = 0, CTtotalOverDueBook = 0;
	double CStotalFine = 0, IAtotalFine = 0, IBtotalFine = 0, CNtotalFine = 0, CTtotalFine = 0;

	if (cur == NULL) {
		cout << "The list is empty. Please READ FILE first!!" << endl;
		return false;
	}
	while (cur != NULL) {
		LibStudent& student = cur->item; // Get the student data from the current node 
		int overdueBooks = 0;

		// Determine the course of the student and update statistics accordingly 
		if (strcmp(student.course, "CS") == 0) {
			CS++;
			CStotalBook += student.totalbook;

			for (int i = 0; i < student.totalbook; i++) {
				if (student.book[i].fine != NULL) { // Check if the book has a fine 
					overdueBooks++;
					CStotalFine += student.book[i].fine; // Add the fine amount of the overdue book to the course's total fine
				}
			}
			CStotalOverDueBook += overdueBooks; // Add the count of overdue bookd to the course's total overdue book 

		}
		else if (strcmp(student.course, "IA") == 0) {
			IA++;
			IAtotalBook += student.totalbook;
			for (int i = 0; i < student.totalbook; i++) {
				if (student.book[i].fine != NULL) {
					overdueBooks++;
					IAtotalFine += student.book[i].fine;
				}
			}
			IAtotalOverDueBook += overdueBooks;

		}
		else if (strcmp(student.course, "IB") == 0) {
			IB++;
			IBtotalBook += student.totalbook;
			for (int i = 0; i < student.totalbook; i++) {
				if (student.book[i].fine != NULL) {
					overdueBooks++;
					IBtotalFine += student.book[i].fine;
				}
			}
			IBtotalOverDueBook += overdueBooks;

		}
		else if (strcmp(student.course, "CN") == 0) {
			CN++;
			CNtotalBook += student.totalbook;
			for (int i = 0; i < student.totalbook; i++) {
				if (student.book[i].fine != NULL) {
					overdueBooks++;
					CNtotalFine += student.book[i].fine;
				}
			}
			CNtotalOverDueBook += overdueBooks;

		}
		else if (strcmp(student.course, "CT") == 0) {
			CT++;
			CTtotalBook += student.totalbook;
			for (int i = 0; i < student.totalbook; i++) {
				if (student.book[i].fine != NULL) {
					overdueBooks++;
					CTtotalFine += student.book[i].fine;
				}
			}
			CTtotalOverDueBook += overdueBooks;
		}
		cur = cur->next;
	}

	// Display the statistics 
	cout << setw(10) << right << "Course " << setw(25) << "Number of Student " << setw(25) << right << "Total Books Borrowed "
		<< setw(25) << right << "Total Overdue Books " << setw(29) << "Total Overdue Fine(RM)" << endl;
	
	cout << setw(8) << right << "CS" << setw(19) << CS << setw(23) << right << CStotalBook
		<< setw(28) << right << CStotalOverDueBook << setw(28) << fixed << setprecision(2) << CStotalFine << endl;
	
	cout << setw(8) << right << "IA" << setw(19) << IA << setw(23) << right << IAtotalBook
		<< setw(28) << right << IAtotalOverDueBook << setw(28) << fixed << setprecision(2) << IAtotalFine << endl;
	
	cout << setw(8) << right << "IB" << setw(19) << IB << setw(23) << right << IBtotalBook
		<< setw(28) << right << IBtotalOverDueBook << setw(28) << fixed << setprecision(2) << IBtotalFine << endl;
	
	cout << setw(8) << right << "CN" << setw(19) << CN << setw(23) << right << CNtotalBook
		<< setw(28) << right << CNtotalOverDueBook << setw(28) << fixed << setprecision(2) << CNtotalFine << endl;
	
	cout << setw(8) << right << "CT" << setw(19) << CT << setw(23) << right << CTtotalBook
		<< setw(28) << right << CTtotalOverDueBook << setw(28) << fixed << setprecision(2) << CTtotalFine << endl;

	return true;
}

// Used in insert book function
int calcJulianDate(int day, int month, int year) { // Julian date according to the year 2022
	bool isLeapYear = false;
	if (year % 4 == 0) {
		isLeapYear = true;
	}
	switch (month) {
	case 12:
		day += 30;
	case 11:
		day += 31;
	case 10:
		day += 30;
	case 9:
		day += 31;
	case 8:
		day += 31;
	case 7:
		day += 30;
	case 6:
		day += 31;
	case 5:
		day += 30;
	case 4:
		day += 31;
	case 3:
		if (isLeapYear)
			day += 29;
		else
			day += 28;
	case 2:
		day += 31;
	}
	return day;
}

bool printStuWithSameBook(List* list, char* callNum) {
	int studentCounter = 0;
	if (list->empty())
		return false;

	Node* cur = list->head; // cur pointer to traverse the list
	while (cur != NULL) {
		for (int i = 0; i < cur->item.totalbook; i++) {
			if (strcmp(cur->item.book[i].callNum, callNum) == 0) {
				studentCounter++;
			}
		}
		cur = cur->next;
	}
	if (studentCounter == 0) {
		cout << "\nNo student has borrowed book of call num " << callNum << "\n\n";
		return false;
	}
	cout << "\nThere are " << studentCounter << " student(s) that borrow the book with call number "
		<< callNum << " as shown below:\n\n";
	cur = list->head;
	while (cur != NULL) {
		for (int i = 0; i < cur->item.totalbook; i++) {
			if (strcmp(cur->item.book[i].callNum, callNum) == 0) {
				cout << "Student Id = " << cur->item.id << endl;
				cout << "Name = " << cur->item.name << endl;
				cout << "Course = " << cur->item.course << endl;
				cout << "Phone Number = " << cur->item.phone_no << endl;
				cout << "Borrow Date: " << cur->item.book[i].borrow.day
					<< "/" << cur->item.book[i].borrow.month << "/"
					<< cur->item.book[i].borrow.year << endl;
				cout << "Due Date: " << cur->item.book[i].due.day
					<< "/" << cur->item.book[i].due.month << "/"
					<< cur->item.book[i].due.year << endl;
				cout << "\n\n";
			}
		}
		cur = cur->next;
	}
	return true;
}

bool displayWarnedStudent(List* list, List* type1, List* type2) {
	int daysDue = 0;
	int tenDaysOverdueBooks = 0;
	int overdueBooks = 0;

	if (list->empty())
		return false;

	for (Node* cur = list->head; cur != NULL; cur = cur->next) { // traverse the list
		overdueBooks = 0; // reset no. of overdued books for every student
		tenDaysOverdueBooks = 0;
		for (int i = 0; i < cur->item.totalbook; i++) {
			daysDue = calcJulianDate(29, 3, 2020) - calcJulianDate(cur->item.book[i].due.day, cur->item.book[i].due.month, cur->item.book[i].due.year);
			if (daysDue < 0) {
				daysDue = 0;
			}
			if (daysDue >= 10) {
				tenDaysOverdueBooks++;
			}
			if (daysDue > 0) {
				overdueBooks++;
			}
		}
		if (tenDaysOverdueBooks > 2) {
			type1->insert(cur->item);
		}
		if ((overdueBooks == cur->item.totalbook) && (cur->item.total_fine > 50)) {
			type2->insert(cur->item);
		}
	}
	return true;
}
