#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<Windows.h>//to hold screen for seconds
//Classes
#include"Person.h"
#include"Client.h"
#include"Employee.h"
#include"Admin.h"
using namespace std;

void welcomeScreen1();
void thanksScreen();

void typeOfUser();
void adminMakeSure();
void employeeMakeSure();
void clientMakeSure();

void adminLogIn();
void employeeLogin();
void clientLogin();

void adminCTRL();
void employeeCTRL();
void clientMethods();

void newAdminInfo();
void clientOperations();
void clientSearchOperation();
void newClientInfo();
void employeeOperations();
void employeeSearchOperation();
void newEmployeeInfo();
void transfermoney();

Admin a1;
Client c1;

int main() {
	welcomeScreen1();
}

//choosing type of user (Done)
void typeOfUser() {
	cout << "You login as :\n\t1 : Admin.\n\t2 : Employee.\n\t3 : Client.\nYour choice : ";
	int a; cin >> a;
	system("CLS");
	switch (a) {
	case 1:
		adminMakeSure();
		break;
	case 2:
		employeeMakeSure();
		break;
	case 3:
		clientMakeSure();
	default:
		int count = 0;
		while (count < 3) {
			Sleep(0700);
			cout << "Unvalid choice.";
			Sleep(0700);
			system("CLS");
			count++;
		}
		typeOfUser();
		break;
	}
}

//Admin methods (Done)
void adminMakeSure() {
	int choice;
	cout << "You are an admin?\n1 : Yes, continue.\n2 : No, Choosed by mistake.\nYour choice : ";
	cin >> choice;
	system("CLS");

	switch (choice) {
	case 1:
		adminLogIn();
		break;
	case 2:
		typeOfUser();
		break;
	default:
		Sleep(800);
		cout << "Unvalid choice.";
		Sleep(800);
		system("CLS");
		adminMakeSure();
		break;
	}
}

int q;//id of logged in admin
void adminLogIn() {
	Admin s;
	int id, choice;
	string password;

	cout << "Your id : "; cin >> id;
	cout << "Password  : "; cin >> password;
	try {
		s = a1.adminSearchById(id);
	}
	catch (AdminNotFound& e) {
		int count = 0;
		while (count < 3) {
			Sleep(0700);
			cout << e.what() << endl;
			Sleep(0700);
			system("CLS");
			count++;
		}
	}
	system("CLS");
	if (s.getPassword() == password && s.getId() == id) {
		q = id;
		cout << "Login successful" << endl;
		Sleep(1000);
		system("CLS");
		adminCTRL();
	}
	else {
		cout << "Inaccurate information !\n";
		cout << "1 : LogIn again.\n2 : Exit.\nYour choice : ";
		cin >> choice;
		system("CLS");
		switch (choice) {
		case 1:
			adminLogIn();
			break;
		case 2:
			thanksScreen();
			break;
		default:
			cout << "Invalid choice.\n";
			Sleep(1000);
			system("CLS");
			adminLogIn();
			break;
		}
	}
	system("CLS");
}

void adminCTRL() {
	cout << "===========================\n";
	cout << "\tAdmin controlls\n";
	cout << "===========================\n";
	cout << "1 : Add new admin.\n2 : List all admins.\n3 : Clients operations.\n4 : Employees operations.\n5 : Check my info.\n";
	cout << "Your choice : "; int x; cin >> x;
	Admin s;
	system("CLS");

	switch (x) {
	case 1:
		newAdminInfo();
		break;
	case 2:
		a1.listAdmins();
		cout << "\n=========================\n=========================\n";
		cout << "Do you want to perform any other operations?\n";
		cout << "1 : Yes.\t\t2 : No,Thanks.\n"; int choice; cout << "Your choice : "; cin >> choice;
		system("CLS");

		switch (choice) {
		case 1:
			adminCTRL();
			break;
		case 2:
			thanksScreen();
			break;
		}
		break;
	case 3:
		clientOperations();
		break;
	case 4:
		employeeOperations();
		break;
	case 5:
		s = a1.adminSearchById(q);
		s.displayMyInfo();
		cout << "=======================\n=======================\n";
		cout << "Any operation else?\n1 : Yes.\t2 : No,Thanks.";
		cout << "Your choice : "; cin >> choice;
		system("CLS");

		switch (choice) {
		case 1:
			adminCTRL();
			break;
		case 2:
			thanksScreen();
			break;
		}
		break;
	default:
		cout << "Unvalid choice!\n";
		Sleep(2000);
		system("CLS");
		adminCTRL();
		break;
	}
}

void newAdminInfo() {
	cout << "Please complete the following information : \n";
	cout << "Enter a number as an id : "; int id; cin >> id;
	system("CLS");
	try {
		Admin b = a1.adminSearchById(id);
		cout << "This id is already exist!\n";
		Sleep(1000);
		cout << "Try another one.\n";
		Sleep(3000);
		system("CLS");
		newAdminInfo();
	}
	catch (AdminNotFound& e) {
		cout << "Enter admin name (only consists of characters and underscores) : "; string name; cin >> name;
		//check validation of entered name
		bool validation = 1;
		for (int i = 0; i < name.length(); i++) {
			if (!((name[i] >= 65 && name[i] <= 90) || (name[i] >= 97 && name[i] <= 122) || name[i] == 95)) {
				validation = 0;
				break;
			}
		}
		if (validation) {
			if (name.size() <= 20 && name.size() >= 5) {
				cout << "Enter a password (Must be 8 : 20 length) : "; string password; cin >> password;
				if (password.length() <= 20 && password.length() >= 8) {
					cout << "Enter balance (Must be 5000 at least) : "; double bal; cin >> bal;
					if (bal >= 5000) {
						a1.addNewAdmin({ id,name,password,bal });
						cout << "Admin added successfully.\n";
						Sleep(1000);
						system("CLS");
						cout << "Any another operation?\n1 : Yes.\t2 : No,Thanks.\nYour choice : "; int choice; cin >> choice;
						system("CLS");
						switch (choice) {
						case 1:
							adminCTRL();
							break;
						case 2:
							thanksScreen();
							break;
						}
					}
					else {
						cout << "Balance must be 5000 at least!\n";
						Sleep(1000);
						cout << "Try again.\n";
						Sleep(1000);
						system("CLS");
						newAdminInfo();
					}
				}
				else {
					cout << "Password must be 8 : 20 !\n";
					Sleep(1000);
					cout << "Try again.\n";
					Sleep(1000);
					system("CLS");
					newAdminInfo();
				}
			}
			else {
				cout << "Name must be 5 : 20 characters.\n";
				Sleep(2000);
				cout << "Try again.\n";
				Sleep(1000);
				system("CLS");
				newAdminInfo();
			}
		}
		else {
			system("CLS");
			cout << "Name must be only alphabetic chars or underscores\n";
			Sleep(2000);
			cout << "Try again.\n";
			Sleep(1000);
			system("CLS");
			newAdminInfo();
		}

	}
}

//Employee methods (Done)
void employeeMakeSure() {
	int choice;
	cout << "You are an Employee?\n1 : Yes, continue.\n2 : No, Choosed by mistake.\nYour choice : ";
	cin >> choice;
	system("CLS");

	system("CLS");
	switch (choice) {
	case 1:
		employeeLogin();
		break;
	case 2:
		typeOfUser();
		break;
	default:
		Sleep(800);
		cout << "Unvalid choice.";
		Sleep(800);
		system("CLS");
		adminLogIn();
		break;
	}
}

int eq;//id of logged in employee
void employeeLogin() {
	Employee s;
	int id, choice;
	string password;

	cout << "Your id : "; cin >> id;
	cout << "Password  : "; cin >> password;
	try {
		s = a1.employeeSearchById(id);
	}
	catch (EmployeeNotFound& e) {
		int count = 0;
		while (count < 3) {
			Sleep(0700);
			cout << e.what() << endl;
			Sleep(0700);
			system("CLS");
			count++;
		}
	}
	system("CLS");
	if (s.getPassword() == password && s.getId() == id) {
		eq = id; q = 0;
		cout << "Login successful" << endl;
		Sleep(1000);
		system("CLS");
		employeeCTRL();
	}
	else {
		cout << "Inaccurate information !\n";
		cout << "1 : LogIn again.\n2 : Exit.\nYour choice : ";
		cin >> choice;
		system("CLS");
		switch (choice) {
		case 1:
			employeeLogin();
			break;
		case 2:
			thanksScreen();
			break;
		default:
			cout << "Invalid choice.\n";
			Sleep(1000);
			system("CLS");
			employeeLogin();
			break;
		}
	}
	system("CLS");
}

void employeeCTRL() {
	cout << "1 : Search for client by id.\n2 : Add new client.\n3 : List all clients.\n4 : Delete all clients.\n5 : Check my info.\nYour choice : ";
	int choice; cin >> choice;
	system("CLS");

	Client s;
	switch (choice) {
	case 1:
		clientSearchOperation();
		break;
	case 2:
		newClientInfo();
		break;
	case 3:
		a1.listClients();
		cout << "\n=========================\n=========================\n";
		cout << "Do you want to do any other operations?\n";
		cout << "1 : Yes.\t\t2 : No,Thanks.\nYour choice : "; cin >> choice;
		system("CLS");
		switch (choice) {
		case 1:
			employeeCTRL();
			break;
		case 2:
			thanksScreen();
			break;
		}
		break;
	case 4:
		a1.deleteAllClients();
		cout << "All clients deleted successfully.\nAny another operation?\n1 : Yes.\t\t2 : No,Thanks.\nYour choice : ";
		cin >> choice;
		system("CLS");

		switch (choice) {
		case 1:
			employeeCTRL();
			break;
		case 2:
			thanksScreen();
			break;
		}
		break;
	case 5:
		a1.employeeSearchById(eq).displayMyInfo();
		Sleep(1000);
		cout << "Do you want to do any other operations?\n";
		cout << "1 : Yes.\t\t2 : No,Thanks.\n"; cin >> choice;
		system("CLS");
		switch (choice) {
		case 1:
			employeeCTRL();
			break;
		case 2:
			thanksScreen();
			break;
		}
		break;
	default:
		for (int i = 0; i < 3; i++) {
			cout << "Unvalid choice!\n";
			Sleep(1000);
			system("CLS");
			Sleep(1000);
		}
		clientOperations();
		break;
	}
}

void clientOperations() {
	cout << "=======================\n\tClient operations\n=======================\n";
	cout << "1 : Search for client by id.\n2 : Add new client.\n3 : List all clients.\n4 : Delete all clients.\nYour choice : ";
	int choice; cin >> choice;
	system("CLS");

	Client s;
	switch (choice) {
	case 1:
		clientSearchOperation();
		break;
	case 2:
		newClientInfo();
		break;
	case 3:
		a1.listClients();
		cout << "\n=========================\n=========================\n";
		cout << "Do you want to do any other operations?\n";
		cout << "1 : Yes.\t\t2 : No,Thanks.\nYour choice : "; int choice; cin >> choice;
		system("CLS");
		int choice2;
		switch (choice) {
		case 1:
			(q == 0) ? employeeCTRL() : adminCTRL();
			break;
		case 2:
			thanksScreen();
			break;
		}
		break;
	case 4:
		a1.deleteAllClients();
		cout << "All clients deleted successfully.\nAny another operation?\n1 : Yes.\t\t2 : No,Thanks.\nYour choice : ";
		cin >> choice2;
		system("CLS");

		switch (choice2) {
		case 1:
			(q == 0) ? employeeCTRL() : adminCTRL();
			break;
		case 2:
			thanksScreen();
			break;
		}
	default:
		for (int i = 0; i < 3; i++) {
			cout << "Unvalid choice!\n";
			Sleep(1000);
			system("CLS");
			Sleep(1000);
		}
		clientOperations();
		break;
	}
}

void clientSearchOperation() {
	cout << "Enter client id : "; int x; cin >> x;
	try {
		Client a = a1.clientSearchById(x);
		system("CLS");
		a.displayMyInfo();
		cout << "\n=========================\n=========================\n";
		cout << "1 : Modify client information.\n2 : Delete client.\n3 : Exit\nYour choice : ";
		int choice; cin >> choice;
		system("CLS");

		switch (choice) {
		case 1:
			a1.modifyClientInfo(a);
			cout << "Client modified successfully.\n";
			Sleep(1000);
			a.displayMyInfo();
			cout << "\n=========================\n=========================\n";
			break;
		case 2:
			a1.deleteClient(a);
			cout << "CLient deleted successfully.\n";
			Sleep(1000);
			break;
		case 3:
			thanksScreen();
			break;
		}
		system("CLS");

		cout << "Any another operation ? \n1 : Yes.\t\t2 : No, Thanks.\nYour choice : ";
		int choice2; cin >> choice2;
		system("CLS");

		switch (choice2) {
		case 1:
			(q == 0) ? employeeCTRL() : adminCTRL();
			break;
		case 2:
			thanksScreen();
			break;
		}
	}
	catch (ClientNotFound& e) {
		system("CLS");
		for (int i = 0; i < 3; i++) {
			cout << e.what() << endl;
			Sleep(1000);
			system("CLS");
			Sleep(1000);
		}
		cout << "1 : Try again.\n2 : Do another client operation.\n3 : Exit system.\nYour choice : ";
		int choice; cin >> choice;
		system("CLS");

		switch (choice) {
		case 1:
			clientSearchOperation();
			break;
		case 2:
			clientOperations();
			break;
		case 3:
			thanksScreen();
			break;
		default:
			for (int i = 0; i < 3; i++) {
				cout << "Unvalid choice!\n";
				Sleep(1000);
				system("CLS");
				Sleep(1000);
			}
			cout << "Try again.\n";
			Sleep(1000);
			system("CLS");
			clientSearchOperation();
			break;
		}
	}
}

void newClientInfo() {
	cout << "Please complete the following information : \n";
	cout << "Enter a number as an id : "; int id; cin >> id;
	try {
		Client b = a1.clientSearchById(id);
		system("CLS");
		cout << "This id is already exist!\n";
		Sleep(1000);
		cout << "Try another one.\n";
		Sleep(3000);
		system("CLS");
		newClientInfo();
	}
	catch (ClientNotFound& e) {
		cout << "Enter client name (only consists of characters or underscores) : "; string name; cin >> name;
		//check validation of entered name
		bool validation = 1;
		for (int i = 0; i < name.length(); i++) {
			if (!((name[i] >= 65 && name[i] <= 90) || (name[i] >= 97 && name[i] <= 122) || name[i] == 95)) {
				validation = 0;
				break;
			}
		}
		if (validation) {
			if (name.size() <= 20 && name.size() >= 5) {
				cout << "Enter a password (Must be 8 : 20 length) : "; string password; cin >> password;
				//To check entered password
				if (password.size() >= 8 && password.size() <= 20) {
					cout << "Enter balance (Must be 1500 at least) : "; double balance; cin >> balance;
					if (balance >= 1500) {
						a1.addNewClient({ id,name,password,balance });
						cout << "CLient added successfully.\n";
						Sleep(2000);
						system("CLS");
						cout << "Do you want to perform any other operations?\n";
						cout << "1 : Yes.\t\t2 : No,Thanks.\n";
						cout << "Your choice : "; int a; cin >> a;
						system("CLS");
						switch (a) {
						case 1:
							(q == 0) ? employeeCTRL() : adminCTRL();
							break;
						case 2:
							thanksScreen();
							break;
						}
						thanksScreen();
					}
				}
				else {
					cout << "password must be 8 : 20 length.\n";
					Sleep(1000);
					cout << "Try again.\n";
					Sleep(1000);
					system("CLS");
					newClientInfo();
				}
			}
			else {
				cout << "Name must be 5 : 20 characters or underscores\n";
				Sleep(2000);
				cout << "Try again.\n";
				Sleep(1000);
				system("CLS");
				newClientInfo();
			}
		}
		else {
			system("CLS");
			cout << "Name must be only alphabetic chars or spaces\n";
			Sleep(2000);
			cout << "Try again.\n";
			Sleep(1000);
			system("CLS");
			newClientInfo();
		}
	}
}

void employeeOperations() {
	cout << "========================\n\tEmployee operations\n========================\n";
	cout << "1 : Search for employee by id.\n2 : Add new employee.\n3 : List all employees.\n4 : Delete all employees.\nYour choice : ";
	int choice; cin >> choice;
	system("CLS");
	int choice2;
	switch (choice) {
	case 1:
		employeeSearchOperation();
		break;
	case 2:
		newEmployeeInfo();
		break;
	case 3:
		a1.listEmployees();
		cout << "\n=========================\n=========================\n";
		Sleep(1000);
		cout << "Any another operation ? \n1 : Yes.\t\t2 : No, Thanks.\nYour choice : ";
		cin >> choice2;
		system("CLS");

		switch (choice2) {
		case 1:
			adminCTRL();
			break;
		case 2:
			thanksScreen();
			break;
		}
		break;
	case 4:
		a1.deleteAllEmployees();
		cout << "Clients deleted successfully.\n";
		Sleep(1000);
		cout << "Any another operation ? \n1 : Yes.\t\t2 : No, Thanks.\nYour choice : ";
		cin >> choice2;
		system("CLS");

		switch (choice2) {
		case 1:
			adminCTRL();
			break;
		case 2:
			thanksScreen();
			break;
		}
		break;
	default:
		cout << "Unvalid choice!\n";
		Sleep(1000);
		system("CLS");
		employeeOperations();
		break;
	}
	cout << "Any another operation ? \n1 : Yes.\t\t2 : No, Thanks.\nYour choice : ";
	cin >> choice2;
	system("CLS");

	switch (choice2) {
	case 1:
		adminCTRL();
		break;
	case 2:
		thanksScreen();
		break;
	}

}

void employeeSearchOperation() {
	cout << "Enter client id : "; int x; cin >> x;
	try {
		Employee a = a1.employeeSearchById(x);
		system("CLS");
		a.displayMyInfo();
		cout << "\n=========================\n=========================\n";
		cout << "1 : Modify employee information.\n2 : Delete employee.\n3 : Exit\nYour choice : ";
		int choice; cin >> choice;
		system("CLS");

		switch (choice) {
		case 1:
			a1.modifyEmployeeInfo(a);
			cout << "Employee modified successfully.\n";
			Sleep(1000);
			a.displayMyInfo();
			cout << "\n=========================\n=========================\n";
			break;
		case 2:
			a1.deleteEmployee(a);
			cout << "Employee deleted successfully.\n";
			Sleep(1000);
			break;
		case 3:
			thanksScreen();
			break;
		}
		system("CLS");

		cout << "Any another operation ? \n1 : Yes.\t\t2 : No, Thanks.\nYour choice : ";
		int choice2; cin >> choice2;
		system("CLS");

		switch (choice2) {
		case 1:
			adminCTRL();
			break;
		case 2:
			thanksScreen();
			break;
		}
	}
	catch (EmployeeNotFound& e) {
		system("CLS");
		for (int i = 0; i < 3; i++) {
			cout << e.what() << endl;
			Sleep(1000);
			system("CLS");
			Sleep(1000);
		}
		cout << "1 : Try again.\n2 : Do another employee operation.\n3 : Exit system.\nYour choice : ";
		int choice; cin >> choice;
		system("CLS");

		switch (choice) {
		case 1:
			employeeSearchOperation();
			break;
		case 2:
			employeeOperations();
			break;
		case 3:
			thanksScreen();
			break;
		default:
			for (int i = 0; i < 3; i++) {
				cout << "Unvalid choice!\n";
				Sleep(1000);
				system("CLS");
				Sleep(1000);
			}
			cout << "Try again.\n";
			Sleep(1000);
			system("CLS");
			employeeSearchOperation();
			break;
		}
	}
}

void newEmployeeInfo() {
	cout << "Please complete the following information : \n";
	cout << "Enter a number as an id : "; int id; cin >> id;
	try {
		Client b = a1.clientSearchById(id);
		system("CLS");
		cout << "This id is already exist!\n";
		Sleep(1000);
		cout << "Try another one.\n";
		Sleep(3000);
		system("CLS");
		newClientInfo();
	}
	catch (EmployeeNotFound& e) {
		cout << "Enter Employee name (only consists of characters) : "; string name; cin >> name;
		//check validation of entered name
		bool validation = 1;
		for (int i = 0; i < name.length(); i++) {
			if (!((name[i] >= 65 && name[i] <= 90) || (name[i] >= 97 && name[i] <= 122) || name[i] == 32)) {
				validation = 0;
				break;
			}
		}
		if (validation) {
			if (name.size() <= 20 && name.size() >= 5) {
				cout << "Enter a password (Must be 8 : 20 length) : "; string password; cin >> password;
				//To check entered password
				if (password.size() >= 8 && password.size() <= 20) {
					cout << "Enter balance (Must be 5000 at least) : "; double balance; cin >> balance;
					if (balance >= 5000) {
						a1.addNewClient({ id,name,password,balance });
						cout << "Employee added successfully.\n";
						Sleep(2000);
						system("CLS");
						cout << "Do you want to perform any other operations?\n";
						cout << "1 : Yes.\t\t2 : No,Thanks.\n";
						cout << "Your choice : "; int a; cin >> a;
						system("CLS");
						switch (a) {
						case 1:
							adminCTRL();
							break;
						case 2:
							thanksScreen();
							break;
						}
						thanksScreen();
					}
				}
				else {
					cout << "password must be 8 : 20 length.\n";
					Sleep(1000);
					cout << "Try again.\n";
					Sleep(1000);
					system("CLS");
					newEmployeeInfo();
				}
			}
			else {
				cout << "Name must be 5 : 20 characters\n";
				Sleep(2000);
				cout << "Try again.\n";
				Sleep(1000);
				system("CLS");
				newEmployeeInfo();
			}
		}
		else {
			system("CLS");
			cout << "Name must be only alphabetic chars or spaces\n";
			Sleep(2000);
			cout << "Try again.\n";
			Sleep(1000);
			system("CLS");
			newEmployeeInfo();
		}
	}
}


//Client methods (Done)
void clientMakeSure() {
	int choice;
	cout << "You are a client?\n1 : Yes, continue.\n2 : No, Choosed by mistake.\nYour choice : ";
	cin >> choice;
	system("CLS");

	switch (choice) {
	case 1:
		clientLogin();
		break;
	case 2:
		typeOfUser();
		break;
	default:
		Sleep(800);
		cout << "Unvalid choice.";
		Sleep(800);
		system("CLS");
		clientMakeSure();
		break;
	}
}

int cq;//id of logged in client
void clientLogin() {
	Client s;
	int id, choice;
	string password;

	cout << "Your id : "; cin >> id;
	cout << "Password  : "; cin >> password;
	try {
		s = a1.clientSearchById(id);
	}
	catch (ClientNotFound& e) {
		int count = 0;
		while (count < 3) {
			Sleep(0700);
			cout << e.what() << endl;
			Sleep(0700);
			system("CLS");
			count++;
		}
	}
	system("CLS");
	if (s.getPassword() == password && s.getId() == id) {
		cq = id;
		cout << "Login successful" << endl;
		Sleep(1000);
		system("CLS");
		clientMethods();
	}
	else {
		cout << "Inaccurate information !\n";
		cout << "1 : LogIn again.\n2 : Exit.\nYour choice : ";
		cin >> choice;
		system("CLS");
		switch (choice) {
		case 1:
			clientLogin();
			break;
		case 2:
			thanksScreen();
			break;
		default:
			cout << "Invalid choice.\n";
			Sleep(1000);
			system("CLS");
			clientLogin();
			break;
		}
	}
	system("CLS");
}

void clientMethods() {
	Client s;
	cout << "1 : Display my info.\n2 : Deposite money.\n3 : Withdraw money.\n4 : Transfer money.\nYour choice : ";
	int choice; cin >> choice;
	system("CLS");
	double money;
	switch (choice) {
	case 1:
		s = a1.clientSearchById(cq);
		s.displayMyInfo();
		break;
	case 2:
		cout << "Enter amount of money : "; cin >> money;
		c1.deposite(cq, money);
		cout << "Deposited successfully\n";
		Sleep(1000);
		break;
	case 3:
		cout << "Enter amount of money : "; cin >> money;
		c1.withdraw(cq, money);
		cout << "Withdrowed successfully\n";
		Sleep(1000);
		break;
	case 4:
		transfermoney();
		break;
	default:
		cout << "Invalid choice!\n";
		Sleep(1000);
		cout << "Try again.\n";
		Sleep(1000);
		system("CLS");
		clientMethods();
		break;
	}
	cout << "Any another operation?\n1 : yes.\t2 : No,thanks.\nYour choice : ";
	cin >> choice;
	system("CLS");
	switch (choice) {
	case 1:
		clientMethods();
		break;
	case 2:
		thanksScreen();
		break;
	}
}

void transfermoney() {
	cout << "Enter transfer amount : "; double amount; cin >> amount;
	cout << "Enter id of client you transfer to : "; int id; cin >> id;

	double tbal = a1.clientSearchById(cq).checkBalance();
	Client s;
	s = a1.clientSearchById(id);
	string password = a1.clientSearchById(cq).getPassword();
	if (amount > tbal) {
		cout << "Your balance is't enough.\n";
		Sleep(2000);
		cout << "Try again?\n1 : yes.\t2 : No,Thanks.\nYour choice : "; int choice; cin >> choice;
		switch (choice) {
		case 1:
			transfermoney();
			break;
		case 2:
			thanksScreen();
			break;
		}
	}
	else {
		cout << "Enter your password to complete the operation : "; string pass; cin >> pass;
		if (pass == password) {

			c1.transferTo(cq, amount, s);
			cout << "Transferred successfully.\n";
		}
		else {
			cout << "Incorrect password! Try again?\n1 : yes.\t2 : No,Thanks.\nYour choice : ";
			int choice; cin >> choice;
			switch (choice) {
			case 1:
				transfermoney();
				break;
			case 2:
				thanksScreen();
				break;
			}
		}
	}
}

//Start and end of project (Done)
void welcomeScreen1() {
	int x = 0;
	while (x < 3) {
		// print "B" star pattern 
		int height = 10, width = 8;
		for (int i = 0; i < height; i++) {
			cout << "**";
			for (int j = 0; j < width; j++) {
				if ((i == 0 || i == height - 1 || i == height / 2) && j < (width - 2))
					cout << "*";
				else if (j == (width - 2) && !(i == 0 || i == height - 1 || i == height / 2))
					cout << "**";
				else
					cout << " ";
			}
			if (i == 0 || i == height / 2 || i == height - 1) {
				for (int j = 0; j < 3; j++) {
					cout << " ";
				}
			}
			else {
				for (int j = 0; j < 2; j++) {
					cout << " ";
				}
			}
			if (i >= 4) {
				for (int j = 0; j < 13; j++) {
					if (i != 6 && i != 7) {
						if (j != 5 && j != 6 && j != 7) {
							cout << " ";
						}
						else
							cout << "*";
					}
					else {
						cout << "*";
					}
				}

				for (int j = 0; j < 2; j++) {
					cout << " ";
				}

				for (int j = 0; j < 13; j++) {
					if (i != 6 && i != 7) {
						if (j != 5 && j != 6 && j != 7) {
							cout << " ";
						}
						else
							cout << "*";
					}
					else {
						cout << "*";
					}
				}
			}
			//print "++" pattern
			cout << endl;
		}
		cout << "<<======== Welcome to \"B++\" bank ========>>\n";
		cout << "<<=========== Not just a bank ===========>>\n\t\t  Loading";
		Sleep(900);
		for (int j = 0; j < 3; j++) {
			cout << ".";
			Sleep(900);
		}
		system("CLS");
		x++;
	}
	typeOfUser();
}

void thanksScreen() {
	int height = 7, width = 9;
	for (int i = 0; i < 2; i++) {
		cout << "<=============================================================================>\n";
	}cout << endl;
	for (int i = 0; i < height; i++) {
		//to print "t"
		for (int j = 0; j < 11; j++) {
			if ((i == 0) || (i == 1) || (j == 5) || (j == 4) || (j == 6)) {
				cout << "*";
			}
			else {
				cout << " ";
			}
		}
		cout << "  ";
		//to print "h"
		for (int j = 0; j < 9; j++) {
			if (i == 3 || i == 4) {
				cout << "*";
			}
			else {
				if (j > 2 && j < 6) {
					cout << " ";
				}
				else {
					cout << "*";
				}
			}
		}
		cout << "  ";
		//to print "a"
		for (int j = i; j < height; j++) {
			cout << " ";
		}

		for (int j = 0; j < 2; j++) {
			cout << "*";
		}
		for (int j = 0; j < i - 1; j++) {
			if (i == 4) {
				cout << "**";
			}
			else {
				cout << "  ";
			}
		}
		if (i > 0) {
			for (int j = 0; j < 2; j++) {
				cout << "*";
			}
		}
		for (int j = i; j < 8; j++) {
			cout << " ";
		}
		for (int j = 0; j < 2; j++) {
			cout << "*";
		}
		for (int j = 0; j < i; j++) {
			if (i == 1) {
				cout << "*";
			}
			else {
				cout << " ";
			}
		}
		for (int j = 0; j < 2; j++) {
			cout << "*";
		}
		for (int j = i; j < 6; j++) {
			if (i == height - 2) {
				cout << "*";
			}
			else {
				cout << " ";
			}
		}
		for (int j = 0; j < 2; j++) {
			cout << "*";
		}
		cout << "  ";
		//To print "K"
		for (int j = 0; j < 3; j++) {
			cout << "*";
		}
		for (int j = 0; j < 2; j++) {
			if (i == 0 || i == 1 || i == 5 || i == 6) {
				cout << " ";
			}
		}
		if (i == 4) {
			cout << "*";
		}
		else if (i == 0 || i == 6) {
			cout << " ";
		}
		for (int j = 0; j < 3; j++) {
			cout << "*";
		}

		if (i == 2 || i == 3) {
			for (int j = 0; j < 5; j++) {
				cout << " ";
			}
		}
		else if (i == 0 || i == height - 1) {
			for (int j = 0; j < 2; j++) {
				cout << " ";
			}
		}
		else if (i == 1 || i == height - 2) {
			for (int j = 0; j < 3; j++) {
				cout << " ";
			}
		}
		else if (i == 2 || i == 4) {
			for (int j = 0; j < 4; j++) {
				cout << " ";
			}
		}

		//To print "S"
		if (!(i == 2 || i == 5)) {
			for (int j = 0; j < 13; j++) {
				cout << "*";
			}
		}
		else if (i == 2) {
			for (int j = 0; j < 3; j++) {
				cout << "*";
			}
		}
		else {
			for (int j = 0; j < 10; j++) {
				cout << " ";
			}
			for (int j = 0; j < 3; j++) {
				cout << "*";
			}
		}
		cout << endl;
	}
	cout << endl;
	cout << "<====================== Thanks for using \"B++\" system ========================>\n";
	cout << "<=============================================================================>\n\n";
	cout << "Programmed by : \n";
	cout << "\t-> Eng.Mustafa Mohamed.\n";
	cout << "\t-> Eng.Mustafa Ahmed.\n";
	cout << "\t-> Eng.Mariem sameh.\n";
	Sleep(5000);
	system("CLS");
	welcomeScreen1();
}
