﻿#include "functions.h"
#include "menu.h"

//CLASS MANAGEMENT
void ImportStudents() {
	int nImport, n;
	ifstream fin;
	ofstream fout;
	string address;
	string Class;
	Student* studentImport;
	Student* student;

	//FUNCTION NAME
	cout << "Import students of a class from a text file" << endl;
	cout << endl;

	//COUT CLASSES LIST
	cout << "Class: ";
	cin.ignore(1000, '\n');
	getline(cin, Class, '\n');
	cout << "File address: ";
	getline(cin, address, '\n');
	fin.open(address);
	if (!fin.is_open()) {
		cout << "Cannot open the file!";
		return;
	}
	fin >> nImport;
	studentImport = new Student[nImport];
	LoadStudent(fin, studentImport, nImport);
	fin.close();

	//READ STUDENTS FILE FROM GIVING CLASS
	fin.open("Data/Classes/Student-" + Class + ".txt");
	if (!fin.is_open()) {
		cout << "Cannot open the file!";
		return;
	}
	fin >> n;
	student = new Student[n + nImport];
	LoadStudent(fin, student, n);
	fin.close();

	//MERGE OLD AND NEW STUDENTS
	for (int i = n; i < n + nImport; i++) {
		int j = 0;
		student[i].id = studentImport[j].id;
		student[i].password = studentImport[j].password;
		student[i].fullName = studentImport[j].fullName;
		student[i].birthday = studentImport[j].birthday;
		student[i].Class = studentImport[j].Class;
		student[i].isActive = studentImport[j].isActive;
		j++;
	}

	//WRITE NEW STUDENTS LIST TO THE CLASS FILE
	fout.open("Data/Classes/Student-" + Class + ".txt");
	if (!fout.is_open()) {
		cout << "Cannot open the file!";
		return;
	}
	fout << n + nImport;
	for (int i = 0; i < n + nImport; i++) {
		fout << endl;
		fout << endl;
		fout << student[i].id << endl;
		fout << student[i].birthday.year << setw(2) << setfill('0') << student[i].birthday.month << setw(2) << setfill('0') << student[i].birthday.day << endl;
		fout << student[i].fullName << endl;
		fout << student[i].birthday.year << " " << setw(2) << setfill('0') << student[i].birthday.month << " " << setw(2) << setfill('0') << student[i].birthday.day << endl;
		fout << student[i].Class << endl;
		fout << student[i].isActive;
	}
	fout.close();

	//READ STUDENT LOGIN FILE
	fin.open("Data/Student.txt");
	if (!fin.is_open()) {
		cout << "Cannot open the file!";
		return;
	}
	fin >> n;
	student = new Student[n + nImport];
	LoadStudent(fin, student, n);
	fin.close();
	for (int i = n; i < n + nImport; i++) {
		int j = 0;
		student[i].id = studentImport[j].id;
		student[i].password = studentImport[j].password;
		student[i].fullName = studentImport[j].fullName;
		student[i].birthday = studentImport[j].birthday;
		student[i].Class = studentImport[j].Class;
		student[i].isActive = studentImport[j].isActive;
		j++;
	}

	//WRITE NEW STUDENTS LIST TO THE STUDENT LOGIN FILE
	fout.open("Data/Student.txt");
	if (!fout.is_open()) {
		cout << "Cannot open the file!";
		return;
	}
	fout << n + nImport;
	for (int i = 0; i < n + nImport; i++) {
		fout << endl;
		fout << endl;
		fout << student[i].id << endl;
		fout << student[i].birthday.year << setw(2) << setfill('0') << student[i].birthday.month << setw(2) << setfill('0') << student[i].birthday.day << endl;
		fout << student[i].fullName << endl;
		fout << student[i].birthday.year << " " << setw(2) << setfill('0') << student[i].birthday.month << " " << setw(2) << setfill('0') << student[i].birthday.day << endl;
		fout << student[i].Class << endl;
		fout << student[i].isActive;
	}
	fout.close();

	cout << endl;
	cout << "Imported successfully!" << endl;
	system("pause");
	system("CLS");
	delete[] studentImport;
	delete[] student;
}
void AddStudentManually() {

	Student studentTmp;
	Student* student;
	ifstream fin;
	ofstream fout;
	int n;

	//FUNCTION NAME
	cout << "Manually add a student to a class" << endl;
	cout << endl;

	//COUT CLASSES LIST
	cout << "Classes list: " << endl;
	fin.open("Data/Classes/Class.txt");
	if (!fin.is_open()) {
		cout << "Cannot open the file!" << endl;
		return;
	}
	fin >> n;
	string* tmp = new string[n];
	for (int i = 0; i < n; i++) {
		fin >> tmp[i];
		cout << i + 1 << " " << tmp[i] << endl;
	}
	fin.close();

	//READ STUDENTS LOGIN FILE
	fin.open("Data/Student.txt");
	if (!fin.is_open()) {
		cout << "Cannot open the file!";
		return;
	}
	fin >> n;
	student = new Student[n + 1];
	LoadStudent(fin, student, n);
	fin.close();

	//LET USER INPUT NEW STUDENT PROFILE
	cin.ignore();
	cout << "Enter student's class: ";
	getline(cin, studentTmp.Class, '\n');
	cout << "ID: ";
	getline(cin, studentTmp.id, '\n');
	for (int i = 0; i < n; i++) {
		while (studentTmp.id.compare(student[i].id) == 0) {
			cout << "ID existed, please try again." << endl;
			cout << "ID: ";
			getline(cin, studentTmp.id, '\n');
		}
	}
	cout << "Full name: ";
	getline(cin, studentTmp.fullName, '\n');
	cout << "Date of birth (yyyy/mm/dd): ";
	cin >> studentTmp.birthday.year >> studentTmp.birthday.month >> studentTmp.birthday.day;

	//WRITE NEW STUDENT PROFILE TO STUDENT LOGIN FILE
	fout.open("Data/Student.txt");
	if (!fout.is_open()) {
		cout << "Cannot open the file!";
		return;
	}
	fout << n + 1;
	if (n >= 2) {
		for (int i = 0; i < n; i++) {
			fout << endl;
			fout << endl;
			fout << student[i].id << endl;
			fout << student[i].birthday.year << setw(2) << setfill('0') << student[i].birthday.month << setw(2) << setfill('0') << student[i].birthday.day << endl;
			fout << student[i].fullName << endl;
			fout << student[i].birthday.year << " " << setw(2) << setfill('0') << student[i].birthday.month << " " << setw(2) << setfill('0') << student[i].birthday.day << endl;
			fout << student[i].Class << endl;
			fout << student[i].isActive;
		}
		fout << endl;
		fout << endl;
		fout << studentTmp.id << endl;
		fout << studentTmp.birthday.year << setw(2) << setfill('0') << studentTmp.birthday.month << setw(2) << setfill('0') << studentTmp.birthday.day << endl;
		fout << studentTmp.fullName << endl;
		fout << studentTmp.birthday.year << " " << setw(2) << setfill('0') << studentTmp.birthday.month << " " << setw(2) << setfill('0') << studentTmp.birthday.day << endl;
		fout << studentTmp.Class << endl;
		fout << 1;
	}
	else {
		fout << endl;
		fout << endl;
		fout << studentTmp.id << endl;
		fout << studentTmp.birthday.year << setw(2) << setfill('0') << studentTmp.birthday.month << setw(2) << setfill('0') << studentTmp.birthday.day << endl;
		fout << studentTmp.fullName << endl;
		fout << studentTmp.birthday.year << " " << setw(2) << setfill('0') << studentTmp.birthday.month << " " << setw(2) << setfill('0') << studentTmp.birthday.day << endl;
		fout << studentTmp.Class << endl;
	}
	fout.close();

	//READ STUDENT CLASS FILE
	fin.open("Data/Classes/Student-" + studentTmp.Class + ".txt");
	if (!fin.is_open()) {
		cout << "Cannot open the file!";
		return;
	}
	fin >> n;
	student = new Student[n + 1];
	LoadStudent(fin, student, n);
	fin.close();

	//WRITE NEW STUDENT PROFILE TO THE STUDENT CLASS FILE
	fout.open("Data/Classes/Student-" + studentTmp.Class + ".txt");
	if (!fout.is_open()) {
		cout << "Cannot open the file!";
	}
	fout << n + 1;
	for (int i = 0; i < n; i++) {
		fout << endl;
		fout << endl;
		fout << student[i].id << endl;
		fout << student[i].birthday.year << setw(2) << setfill('0') << student[i].birthday.month << setw(2) << setfill('0') << student[i].birthday.day << endl;
		fout << student[i].fullName << endl;
		fout << student[i].birthday.year << " " << setw(2) << setfill('0') << student[i].birthday.month << " " << setw(2) << setfill('0') << student[i].birthday.day << endl;
		fout << student[i].Class << endl;
		fout << student[i].isActive;
	}
	fout << endl;
	fout << endl;
	fout << studentTmp.id << endl;
	fout << studentTmp.birthday.year << setw(2) << setfill('0') << studentTmp.birthday.month << setw(2) << setfill('0') << studentTmp.birthday.day << endl;
	fout << studentTmp.fullName << endl;
	fout << studentTmp.birthday.year << " " << setw(2) << setfill('0') << studentTmp.birthday.month << " " << setw(2) << setfill('0') << studentTmp.birthday.day << endl;
	fout << studentTmp.Class << endl;
	fout << 1;

	//END THE FUNCTION
	cout << endl;
	cout << "Student added successfully!" << endl;
	system("pause");
	system("CLS");
	delete[] tmp;
	delete[] student;
}
void EditStudent() {
	string ID;
	Student* student;
	Student studentTmp;
	ifstream fin;
	ofstream fout;
	int n;

	//FUNCTION NAME
	cout << "Edit an existing student" << endl;
	cout << endl;

	//COUT CLASSES LIST
	//cout << "Classes list: " << endl;
	//fin.open("Data/Classes/Class.txt");
	//if (!fin.is_open()) {
	//	cout << "Cannot open the file!" << endl;
	//}
	//fin >> n;
	//string* tmp = new string[n];
	//for (int i = 0; i < n; i++) {
	//	fin >> tmp[i];
	//	cout << i + 1 << " " << tmp[i] << endl;
	//}
	//fin.close();

	//LET USER INPUT EXISTING STUDENT
	cin.ignore();
	cout << "Enter student ID: ";
	getline(cin, studentTmp.id, '\n');

	//READ AND COUT STUDENT INFO
	fin.open("Data/Student.txt");
	if (!fin.is_open()) {
		cout << "Cannot open the file!";
		return;
	}
	fin >> n;
	student = new Student[n];
	LoadStudent(fin, student, n);
	fin.close();
	for (int i = 0; i < n; i++) {
		if (student[i].id == studentTmp.id) {
			cout << "Student name: ";
			cout << student[i].fullName << endl;
			cout << "Student birth date: ";
			cout << student[i].birthday.year << " " << setw(2) << setfill('0') << student[i].birthday.month << " " << setw(2) << setfill('0') << student[i].birthday.day << endl;
			cout << endl;
		}
	}

	//CHECK IF USER WANT TO EDIT PROFILE
	bool isAgree;
	cout << "Do you want to edit this student? (1-yes / 0-no): ";
	cin >> isAgree;
	if (!isAgree) {
		cout << "Returning to menu..." << endl;
		system("pause");
		system("CLS");
	}

	//EDIT PROFILE ON STUDENTS LOGIN FILE
	cin.ignore(1000, '\n');
	cout << "Enter new full name: ";
	getline(cin, studentTmp.fullName, '\n');
	cout << "Enter new birth date (yyyy/mm/dd): ";
	cin >> studentTmp.birthday.year >> studentTmp.birthday.month >> studentTmp.birthday.day;
	for (int i = 0; i < n; i++) {
		if (student[i].id == studentTmp.id) {
			student[i].fullName = studentTmp.fullName;
			student[i].birthday = studentTmp.birthday;
			studentTmp.Class = student[i].Class;
		}
	}
	fout.open("Data/Student.txt");
	if (!fout.is_open()) {
		cout << "Cannot open the file!";
		return;
	}
	fout << n;
	for (int i = 0; i < n; i++) {
		fout << endl;
		fout << endl;
		fout << student[i].id << endl;
		fout << student[i].birthday.year << setw(2) << setfill('0') << student[i].birthday.month << setw(2) << setfill('0') << student[i].birthday.day << endl;
		fout << student[i].fullName << endl;
		fout << student[i].birthday.year << " " << setw(2) << setfill('0') << student[i].birthday.month << " " << setw(2) << setfill('0') << student[i].birthday.day << endl;
		fout << student[i].Class << endl;
		fout << student[i].isActive;
	}
	fout.close();

	//EDIT PROFILE ON STUDENTS CLASS FILE
	fout.open("Data/Classes/Student-" + studentTmp.Class + ".txt");
	if (!fout.is_open()) {
		cout << "Cannot open the file!";
		return;
	}
	fout << n;
	for (int i = 0; i < n; i++) {
		fout << endl;
		fout << endl;
		fout << student[i].id << endl;
		fout << student[i].birthday.year << setw(2) << setfill('0') << student[i].birthday.month << setw(2) << setfill('0') << student[i].birthday.day << endl;
		fout << student[i].fullName << endl;
		fout << student[i].birthday.year << " " << setw(2) << setfill('0') << student[i].birthday.month << " " << setw(2) << setfill('0') << student[i].birthday.day << endl;
		fout << student[i].Class << endl;
		fout << student[i].isActive;
	}
	fout.close();

	//END THE FUNCTION
	cout << endl;
	cout << "Student edited successfully!" << endl;
	system("pause");
	system("CLS");

	//delete[] tmp; //	=>Uncomment this line if you want to cout classes list
	delete[] student;
}
void RemoveStudent()
{
	int n;
	Student* student;
	string id;
	string Class;
	ifstream fin;
	ofstream fout;

	//READ STUDENT LOGIN FILE
	fin.open("Data/Student.txt");
	if (!fin.is_open()) {
		cout << "Cannot open the file!" << endl;
		return;
	}
	fin >> n;
	student = new Student[n];
	LoadStudent(fin, student, n);
	fin.close();

	//LET USER ENTER STUDENT ID
	cin.ignore(1000, '\n');
	cout << "Enter student ID to remove: ";
	getline(cin, id, '\n');
	int count = 0;;
	for (int i = 0; i < n; i++) {
		if (id.compare(student[i].id) != 0)
			count++;
		else {
			count = 0;
			break;
		}
	}
	while (count != 0) {
		cout << "ID doesn't exist, please try again: ";
		getline(cin, id, '\n');
		count = 0;
		for (int i = 0; i < n; i++) {
			if (id.compare(student[i].id) != 0)
				count++;
			else {
				count = 0;
				break;
			}
		}
	}

	//CHANGE STUDENT STATUS
	for (int i = 0; i < n; i++)
	{
		if (student[i].id == id) {
			student[i].isActive = 0;
			Class = student[i].Class;
		}
	}

	//WRITE STUDENT LOGIN FILE
	fout.open("Data/Student.txt");
	if (!fout.is_open()) {
		cout << "Cannot open the file!";
		return;
	}
	fout << n;
	for (int i = 0; i < n; i++) {
		fout << endl;
		fout << endl;
		fout << student[i].id << endl;
		fout << student[i].birthday.year << setw(2) << setfill('0') << student[i].birthday.month << setw(2) << setfill('0') << student[i].birthday.day << endl;
		fout << student[i].fullName << endl;
		fout << student[i].birthday.year << " " << setw(2) << setfill('0') << student[i].birthday.month << " " << setw(2) << setfill('0') << student[i].birthday.day << endl;
		fout << student[i].Class << endl;
		fout << student[i].isActive;
	}
	fout.close();

	//WRITE STUDENT CLASS FILE
	fout.open("Data/Classes/Student-" + Class + ".txt");
	if (!fout.is_open()) {
		cout << "Cannot open the file!";
		return;
	}
	fout << n;
	for (int i = 0; i < n; i++) {
		fout << endl;
		fout << endl;
		fout << student[i].id << endl;
		fout << student[i].birthday.year << setw(2) << setfill('0') << student[i].birthday.month << setw(2) << setfill('0') << student[i].birthday.day << endl;
		fout << student[i].fullName << endl;
		fout << student[i].birthday.year << " " << setw(2) << setfill('0') << student[i].birthday.month << " " << setw(2) << setfill('0') << student[i].birthday.day << endl;
		fout << student[i].Class << endl;
		fout << student[i].isActive;
	}
	fout.close();

	//END THE FUNCTION
	cout << endl;
	cout << "Student removed successfully!" << endl;
	system("pause");
	system("CLS");
	delete[] student;
}
void ChangeClass() {
	string ID, Class, classtemp;
	Student temp;
	ifstream fin;
	ofstream fout;
	int n;

	//FUNCTION NAME
	cout << "Change student from class A to B" << endl;
	cout << endl;

	//LET USER ENTER STUDENT ID
	cout << "Enter student's ID: ";
	cin.ignore();
	getline(cin, ID, '\n');
	cout << "Enter new class: ";
	getline(cin, Class, '\n');

	//READ STUDENT LOGIN FILE
	fin.open("Data/Student.txt");
	if (!fin.is_open()) {
		cout << "Cannot open the file!" << endl;
		return;
	}
	fin >> n;
	Student* student = new Student[n];
	for (int i = 0; i < n; i++) {
		fin.ignore(1000, '\n');
		fin.get();
		getline(fin, student[i].id, '\n');
		getline(fin, student[i].password, '\n');
		getline(fin, student[i].fullName, '\n');
		fin >> student[i].birthday.year >> student[i].birthday.month >> student[i].birthday.day;
		fin.ignore(1000, '\n');
		getline(fin, student[i].Class, '\n');
		fin >> student[i].isActive;
	}
	fin.close();
	for (int i = 0; i < n; i++) {
		if (student[i].id == ID) {
			if (student[i].Class == Class) {
				cout << "The class hasn't been changed!" << endl;
				system("pause");
				system("CLS");
				return;
			}
			classtemp = student[i].Class;
			student[i].Class = Class;
			temp = student[i];
		}
	}
	fout.open("Data/Student.txt");
	if (!fout.is_open()) {
		cout << "Cannot open the file!" << endl;
	}
	fout << n;
	for (int i = 0; i < n; i++) {
		fout << endl;
		fout << endl;
		fout << student[i].id << endl;
		fout << student[i].Class << endl;
		fout << student[i].fullName << endl;
		fout << student[i].birthday.year << " " << setw(2) << setfill('0') << student[i].birthday.month << " " << setw(2) << setfill('0') << student[i].birthday.day << endl;
		fout << student[i].Class << endl;
		fout << student[i].isActive;
	}
	fout.close();
	fin.open("Data/Classes/Student-" + temp.Class + ".txt");

	if (!fin.is_open()) {
		cout << "Cannot open the file!" << endl;

		return;
	}
	fin >> n;
	Student* studenttemp = new Student[n];
	for (int i = 0; i < n; i++) {
		fin.ignore(1000, '\n');
		fin.get();
		getline(fin, studenttemp[i].id);
		getline(fin, studenttemp[i].password);
		getline(fin, studenttemp[i].fullName);
		fin >> studenttemp[i].birthday.year >> studenttemp[i].birthday.month >> studenttemp[i].birthday.day;
		fin.ignore(1000, '\n');
		getline(fin, studenttemp[i].Class);
		fin >> studenttemp[i].isActive;
	}
	n++;
	fin.close();
	fout.open("Data/Classes/Student-" + temp.Class + ".txt");
	if (!fout.is_open()) {
		cout << "Cannot open the file!" << endl;
	}
	fout << n;
	for (int i = 0; i < n - 1; i++) {
		fout << endl;
		fout << endl;
		fout << studenttemp[i].id << endl;
		fout << studenttemp[i].password << endl;
		fout << studenttemp[i].fullName << endl;
		fout << studenttemp[i].birthday.year << " " << setw(2) << setfill('0') << studenttemp[i].birthday.month << " " << setw(2) << setfill('0') << studenttemp[i].birthday.day << endl;
		fout << studenttemp[i].Class << endl;
		fout << studenttemp[i].isActive;
	}
	fout << endl;
	fout << endl;
	fout << temp.id << endl;
	fout << temp.password << endl;
	fout << temp.fullName << endl;
	fout << temp.birthday.year << " " << setw(2) << setfill('0') << temp.birthday.month << " " << setw(2) << setfill('0') << temp.birthday.day << endl;
	fout << temp.Class << endl;
	fout << temp.isActive;
	fout.close();

	fin.open("Data/Classes/Student-" + classtemp + ".txt");
	if (!fin.is_open()) {
		cout << "Cannot open the file!" << endl;
		return;
	}
	fin >> n;
	Student* studenttemp1 = new Student[n];
	for (int i = 0; i < n; i++) {
		fin.ignore(1000, '\n');
		fin.get();
		getline(fin, studenttemp1[i].id, '\n');
		getline(fin, studenttemp1[i].password, '\n');
		getline(fin, studenttemp1[i].fullName, '\n');
		fin >> studenttemp1[i].birthday.year >> studenttemp1[i].birthday.month >> studenttemp1[i].birthday.day;
		fin.ignore(1000, '\n');
		getline(fin, studenttemp1[i].Class, '\n');
		fin >> studenttemp1[i].isActive;
	}
	--n;
	fin.close();

	fout.open("Data/Classes/Student-" + classtemp + ".txt");
	if (!fout.is_open()) {
		cout << "Cannot open the file!" << endl;
	}
	fout << n;
	for (int i = 0; i < n + 1; i++) {
		if (studenttemp1[i].id != temp.id) {
			fout << endl;
			fout << endl;
			fout << studenttemp1[i].id << endl;
			fout << studenttemp1[i].password << endl;
			fout << studenttemp1[i].fullName << endl;
			fout << studenttemp1[i].birthday.year << " " << setw(2) << setfill('0') << studenttemp[i].birthday.month << " " << setw(2) << setfill('0') << studenttemp[i].birthday.day << endl;
			fout << studenttemp1[i].Class << endl;
			fout << studenttemp1[i].isActive;
		}
	}
	fout.close();
	cout << endl;
	cout << endl;
	cout << "Class changed successfully!" << endl;
	system("pause");
	system("CLS");
	delete[] student;
	//con đĩ
}
void viewclass() {
	ifstream fin;
	ofstream fout;
	int n = 0;
	fin.open("Data/Classes/Class.txt");
	if (!fin.is_open()) {
		cout << "Cannot open the file!" << endl;
		return;
	}
	fin >> n;
	string* Classes = new string[n];
	for (int i = 0; i < n; i++) {
		fin >> Classes[i];
	}
	fin.close();
	cout << "Classes list: " << endl;
	for (int i = 0; i < n; i++) {
		cout << Classes[i] << endl;
	}
	cout << endl;
	system("pause");
	system("CLS");
}
void viewStudent() {
	ifstream fin;
	ofstream fout;
	int n = 0;
	fin.open("Data/Classes/Class.txt");
	if (!fin.is_open()) {
		cout << "Cannot open the file!" << endl;
		return;
	}
	fin >> n;
	string* Classes = new string[n];
	for (int i = 0; i < n; i++) {
		fin >> Classes[i];
	}
	fin.close();
	string temp;
	viewclass();
	cout << "Which class do you want to view ?: ";
	cin >> temp;
	for (int i = 0; i < n; i++) {
		if (temp == Classes[i]) {
			fin.open("Data/Classes/Student-" + temp + ".txt");
			if (!fin.is_open()) {
				cout << "Cannot open the file!" << endl;

				return;
			}
			fin >> n;
			Student* studenttemp = new Student[n];
			for (int i = 0; i < n; i++) {
				fin.ignore(1000, '\n');
				fin.get();
				getline(fin, studenttemp[i].id);
				getline(fin, studenttemp[i].password);
				getline(fin, studenttemp[i].fullName);
				fin >> studenttemp[i].birthday.year >> studenttemp[i].birthday.month >> studenttemp[i].birthday.day;
				fin.ignore(1000, '\n');
				getline(fin, studenttemp[i].Class);
				fin >> studenttemp[i].isActive;
			}
			fin.close();
			system("CLS");
			cout << "Students in class " + temp + ": " << endl;
			for (int i = 0; i < n; i++) {
				cout << studenttemp[i].id << endl;
				cout << studenttemp[i].password << endl;
				cout << studenttemp[i].fullName << endl;
				cout << studenttemp[i].birthday.year << " " << studenttemp[i].birthday.month << " " << studenttemp[i].birthday.day << endl;
				cout << studenttemp[i].Class << endl;
				cout << studenttemp[i].isActive << endl;
				cout << endl;
			}
		}
	}
	system("pause");
	system("CLS");
}

//COURSE MANAGEMENT
void EditAcademicYears() {
	//int n;
	//AYear* ayear;
	//ifstream fin;
	//ofstream fout;

	////FUNCTION NAME
	//cout << "Create / update / delete / view academic years, and semesters" << endl;
	//cout << endl;

	////LET USER SELECT OPTION
	//int selection;
	//cout << "1. Create new academic year" << endl;
	//cout << "2. Update academic year" << endl;
	//cout << "3. Delete academic year" << endl;
	//cout << "4. View academic year" << endl;
	//cout << "Select option (1 - 4): ";
	//cin >> selection;
	//switch (selection) {
	//case 1:
	//	fin.open("Data/Courses/Academic-Years.txt");
	//	if (!fin.is_open()) {
	//		cout << "Cannot open the file!";
	//		return;
	//	}
	//	fin >> n;
	//	for (int i = 0; i < n; i++) {
	//		fin.get();
	//		fin >> ayear[i].startYear >> ayear[i].endYear;
	//		fin.ignore(1000, '\n');
	//		getline(fin, ayear[i].semester, '\n');
	//		fin.close();
	//	}
	//}
}
void ImportCourses() {
	//Course* course;

	////FUNCTION NAME
	//cout << "Import courses from a file" << endl;
	//cout << endl;

}


//EDIT AN EXISTING COURSE
void EditCourse() {
	Course* course;
	Course courseTmp;
	/*DOB startDate;
	DOB endDate;
	int day;
	Time startTime;
	Time endTime;
	string room;*/
	int n;
	ifstream fin;
	ofstream fout;
	//FUNCTION NAME
	cout << "Edit an existing course" << endl;
	cout << endl;
	//LET USER INPUT EXISTING COURSE
	cin.ignore();
	cout << "Enter Course ID: ";
	getline(cin, courseTmp.course, '\n');
	//READ AND COUT COURSE INFO
	fin.open("Data/Courses/2019-2020-HK2-Schedule-19APCS1.txt");
	if (!fin.is_open()) {
		cout << "Can not open this file! " << endl;
		return;
	}
	fin >> n;
	course = new Course[n];
	LoadCourse(fin, course, n);
	fin.close();

	for (int i = 0; i < n; ++i) {
		if (course[i].course == courseTmp.course)
		{
			cout << "Course name: ";
			cout << course[i].courseName << endl;
			cout << "Class: ";
			cout << course[i].Class << endl;
			cout << "Lecturer user: ";
			cout << course[i].lecturerUser << endl;
			cout << "Lecturer degree: ";
			cout << course[i].education << endl;
			cout << "Lecturer gender: ";
			cout << course[i].gender << endl;
			cout << "StartDate: ";
			cout << course[i].startDate.year << " " << setw(2) << setfill('0') << course[i].startDate.month << " " << setw(2) << setfill('0') << course[i].startDate.day << endl;
			cout << "EndDate: ";
			cout << course[i].endDate.year << " " << setw(2) << setfill('0') << course[i].endDate.month << " " << setw(2) << setfill('0') << course[i].endDate.day << endl;
			cout << "Day of week: ";
			cout << course[i].day << endl;
			cout << "StartTime: ";
			cout << course[i].startTime.hour << " " << setw(2) << setfill('0') << course[i].startTime.minute << endl;
			cout << "EndTime: ";
			cout << course[i].endTime.hour << " " << setw(2) << setfill('0') << course[i].endTime.minute << endl;
			cout << "Room: ";
			cout << course[i].room << endl;
			cout << endl;
		}
	}
	//CHECK IF USER WANT TO EDIT PROFILE
	bool isAgree;
	cout << "Do you want to edit this course ? (1-yes / 0-no): ";
	cin >> isAgree;
	if (!isAgree) {
		cout << "Returning to menu.... " << endl;
		system("pause");
		system("CLS");
	}
	//EDIT PROFILE OF THE COURSE IN SCHEDULE FILE
	cin.ignore(1000, '\n');
	cout << "Enter new start Date: ";
	cin >> courseTmp.startDate.year >> courseTmp.startDate.month >> courseTmp.startDate.day;
	cout << endl;
	cout << "Enter new end Date: ";
	cin >> courseTmp.endDate.year >> courseTmp.endDate.month >> courseTmp.endDate.day;
	cout << endl;
	cout << "Enter the new day of week: ";
	cin >> courseTmp.day;
	cout << endl;
	cout << "Enter new start time: ";
	cin >> courseTmp.startTime.hour >> courseTmp.startTime.minute;
	cout << endl;
	cout << "Enter new end time: ";
	cin >> courseTmp.endTime.hour >> courseTmp.endTime.minute;
	cout << endl;
	for (int i = 0; i < n; ++i) {
		if (course[i].course == courseTmp.course) {
			course[i].startDate.year = courseTmp.startDate.year;
			course[i].startDate.month = courseTmp.startDate.month;
			course[i].startDate.day = courseTmp.startDate.day;
			course[i].endDate.year = courseTmp.endDate.year;
			course[i].endDate.month = courseTmp.endDate.month;
			course[i].endDate.day = courseTmp.endDate.day;
			course[i].day = courseTmp.day;
			course[i].startTime.hour = courseTmp.startTime.hour;
			course[i].startTime.minute = courseTmp.startTime.minute;
		}
	}
	fout.open("Data/Courses/2019-2020-HK2-Schedule-19APCS1.txt");
	if (!fout.is_open()) {
		cout << "Can not open this file!" << endl;
		return;
	}
	fout << n;
	for (int i = 0; i < n; ++i) {
		fout << endl;
		fout << endl;
		fout << course[i].course << endl;
		fout << course[i].courseName << endl;
		fout << course[i].Class << endl;
		fout << course[i].lecturerUser << endl;
		fout << course[i].lecturerName << endl;
		fout << course[i].education << endl;
		fout << course[i].gender << endl;
		fout << course[i].startDate.year << " " << setw(2) << setfill('0') << course[i].startDate.month << " " << setw(2) << setfill('0') << course[i].startDate.day << endl;
		fout << course[i].endDate.year << " " << setw(2) << setfill('0') << course[i].endDate.month << " " << setw(2) << setfill('0') << course[i].endDate.day << endl;
		fout << course[i].day;
		fout << course[i].startTime.hour << " " << setw(2) << setfill('0') << course[i].startTime.minute << endl;
		fout << course[i].endTime.hour << " " << setw(2) << setfill('0') << course[i].endTime.minute << endl;
		fout << course[i].room;
	}
	fout.close();
	//END THE FUNCTION
	cout << endl;
	cout << "Course edited successfully!" << endl;
	system("pause");
	system("CLS");
	delete[]course;
}