#include<iostream>
#include<string>
#include<Windows.h>
#include<vector>
#include"Employee.h"
#pragma once
using namespace std;

class EmployeeNotFound :public exception {
public:
	const char* what() const throw() {
		cout << "Employee ";
		return "not found";
	}
};

class AdminNotFound :public exception {
public:
	const char* what() const throw() {
		cout << "Admin ";
		return "not found";
	}
};
class Admin :public Employee {
	vector<Employee> employees;
	vector<Admin> admins;
public:
	Admin() {
		//To read data from "Employee.txt" file
		int idEmployee; string nEmployee, passEmployee; double balEmployee;
		ifstream employeeFile("Database/Employee.txt");
		int i = 0;
		if (employeeFile.is_open()) {
			while (employeeFile >> idEmployee) {
				employeeFile.ignore();
				getline(employeeFile, nEmployee);
				getline(employeeFile, passEmployee);
				employeeFile >> balEmployee;
				Employee e(idEmployee, nEmployee, passEmployee, balEmployee);
				employees.push_back(e);
				i++;
			}
			employeeFile.close();
		}

		//To read data from "Admin.txt" file
		int idAdmin; string nAdmin, passAdmin; double balAdmin;
		ifstream adminFile("Database/Admin.txt");
		int j = 0;
		if (adminFile.is_open()) {
			while (adminFile >> idAdmin) {
				adminFile.ignore();
				getline(adminFile, nAdmin);
				getline(adminFile, passAdmin);
				adminFile >> balAdmin;
				Admin a(idAdmin, nAdmin, passAdmin, balAdmin);
				admins.push_back(a);
				j++;
			}
			employeeFile.close();
		}


	}
	Admin(int i, string n, string pass, double bal) :Employee(i, n, pass, bal) {}

	void addNewEmployee(Employee a) {
		employees.push_back(a);
		ofstream employeeFile;
		employeeFile.open("Database/Employee.txt", ios::out | ios::app);
		employeeFile << a.getId() << "\n"
			<< a.getName() << "\n"
			<< a.getPassword() << "\n"
			<< a.checkBalance() << endl;
	}
	void addNewAdmin(Admin a) {
		admins.push_back(a);
		ofstream adminFile;
		adminFile.open("Database/Admin.txt", ios::out | ios::app);
		adminFile << a.getId() << "\n"
			<< a.getName() << "\n"
			<< a.getPassword() << "\n"
			<< a.checkBalance() << endl;
	}
	void deleteEmployee(Employee& a) {
		remove("Database/Employee.txt");

		//erase
		int i = 0;
		while (i < employees.size()) {
			if (employees[i].getId() == a.getId()) {
				employees.erase(employees.begin() + i);
			}
			i++;
		}

		ofstream employeeFile;
		employeeFile.open("Database/Employee.txt", ios::out | ios::app);

		int index = 0;
		while (index < clients.size()) {

			employeeFile << employees[index].getId() << " | "
				<< employees[index].getName() << " | "
				<< employees[index].getPassword() << " | "
				<< employees[index].checkBalance() << endl;
			index++;
		}
		employeeFile.close();
	}
	void modifyEmployeeInfo(Employee& a) {
		string cName, pass;
		double bal;
		cout << "Please enter employee information after modification :\n";
		cout << "Username : ";
		cin >> cName;
		cout << "Password : ";
		cin >> pass;
		cout << "Balance : ";
		cin >> bal;
		remove("Database/Employee.txt");
		//////////////////////////////////////////////////////////
		bool validation = 1;
		for (int i = 0; i < name.length(); i++) {
			if (!((cName[i] >= 65 && cName[i] <= 90) || (cName[i] >= 97 && cName[i] <= 122) || cName[i] == 95)) {
				validation = 0;
				break;
			}
		}
		if (validation) {
			if (cName.size() <= 20 && cName.size() >= 5) {
				if (pass.length() <= 20 && pass.length() >= 8) {
					if (bal >= 5000) {
						//modify it in vector
						int i = 0;
						while (i < employees.size()) {
							if (employees[i].getId() == a.getId()) {
								employees[i].setName(cName);
								employees[i].setPassword(pass);
								employees[i].setBalance(bal);
								break;
							}
							i++;
						}
						ofstream employeeFile;
						employeeFile.open("Database/Employee.txt", ios::out | ios::app);

						int index = 0;
						while (index < employees.size()) {
							employeeFile << employees[index].getId() << "\n"
								<< employees[index].getName() << "\n"
								<< employees[index].getPassword() << "\n"
								<< employees[index].checkBalance() << endl;
							index++;
						}
						employeeFile.close();
					}
					else {
						cout << "Balance must be 5000 at least!\n";
						Sleep(1000);
						cout << "Try again.\n";
						Sleep(1000);
						system("CLS");
						modifyEmployeeInfo(a);
					}
				}
				else {
					cout << "Password must be 8 : 20 !\n";
					Sleep(1000);
					cout << "Try again.\n";
					Sleep(1000);
					system("CLS");
					modifyEmployeeInfo(a);
				}
			}
			else {
				cout << "Name must be 5 : 20 characters.\n";
				Sleep(2000);
				cout << "Try again.\n";
				Sleep(1000);
				system("CLS");
				modifyEmployeeInfo(a);
			}
		}
		else {
			system("CLS");
			cout << "Name must be only alphabetic chars or underscores\n";
			Sleep(2000);
			cout << "Try again.\n";
			Sleep(1000);
			system("CLS");
			modifyEmployeeInfo(a);
		}
		//////////////////////////////////////////////////////////
	}
	Employee employeeSearchById(int i) {
		int index = 0;
		bool founded = 0;

		for (index; index < employees.size(); index++) {
			if (employees[index].getId() == i) {
				founded = 1;
				break;
			}
		}
		if (founded) {
			return employees[index];
		}
		else {
			throw EmployeeNotFound();
		}
	}
	void listEmployees() {
		for (int i = 0; i < employees.size(); i++) {
			cout << employees[i].getId() << " | "
				<< employees[i].getName() << " | "
				<< employees[i].getPassword() << " | "
				<< employees[i].checkBalance() << endl;
		}
	}
	void listAdmins() {
		for (int i = 0; i < admins.size(); i++) {
			cout << admins[i].getId() << " | "
				<< admins[i].getName() << " | "
				<< admins[i].getPassword() << " | "
				<< admins[i].checkBalance() << endl;
		}
	}
	void deleteAllEmployees() {
		remove("Database/Employee.txt");
		clients.clear();
		ofstream employeeFile;
		employeeFile.open("Database/Employee.txt", ios::out | ios::app);
		employeeFile.close();
	}
	Admin adminSearchById(int i) {
		int index = 0;
		bool founded = 0;

		for (index; index < admins.size(); index++) {
			if (admins[index].getId() == i) {
				founded = 1;
				break;
			}
		}
		if (founded) {
			return admins[index];
		}
		else {
			throw AdminNotFound();
		}
	}
	/*
		The remaining functions
			-> addNewEmployee      (Done)
			-> deleteEmployee      (Done)
			-> editEmployeeInfo    (Done)
			-> employeeSearchById  (Done)
			-> employeeSearchById  (Done)
			-> listEmployees       (Done)
			-> DeleteAllEmployees  (Done)
	*/
};