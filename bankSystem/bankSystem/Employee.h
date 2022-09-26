#include<iostream>
#include<string>
#include<Windows.h>
#include<vector>
#include<exception>
#include<fstream>
#include"Client.h"
#include"Person.h"
#pragma once
using namespace std;

class ClientNotFound :public exception {
public:
	const char* what() const throw() {
		cout << "Client ";
		return "not found";
	}
};

class Employee :public Person {
protected:
	double balance;
	vector<Client> clients;
public:
	Employee() {
		balance = 5000;
		//To read data from "Client.txt" file
		int idClient; string nClient, passClient; double balClient;
		ifstream clientFile("Database/Client.txt");
		int i = 0;
		if (clientFile.is_open()) {
			while (clientFile >> idClient) {
				clientFile.ignore();
				getline(clientFile, nClient);
				getline(clientFile, passClient);
				clientFile >> balClient;
				Client c(idClient, nClient, passClient, balClient);
				clients.push_back(c);
				i++;
			}
			clientFile.close();
		}
	}
	Employee(int i, string n, string pass, double bal) :Person(i, n, pass) {
		balance = bal;
	}
	void setBalance(double bal) {
		balance = bal;
	}
	double checkBalance() {
		return balance;
	}
	void displayMyInfo() {
		cout << "Employee info :\n";
		cout << "\tId : " << id << endl;
		cout << "\tName : " << name << endl;
		cout << "\tPassword : " << password << endl;
		cout << "\tBalance : " << balance << endl;
	}
	void addNewClient(Client a) {
		clients.push_back(a);
		ofstream clientFile;
		clientFile.open("Database/Client.txt", ios::out | ios::app);
		clientFile << a.getId() << "\n"
			<< a.getName() << "\n"
			<< a.getPassword() << "\n"
			<< a.checkBalance() << endl;
	}
	void deleteClient(Client& a) {
		remove("Database/Client.txt");

		//erase
		int i = 0;
		while (i < clients.size()) {
			if (clients[i].getId() == a.getId()) {
				clients.erase(clients.begin() + i);
			}
			i++;
		}

		ofstream clientFile;
		clientFile.open("Database/Client.txt", ios::out | ios::app);

		int index = 0;
		while (index < clients.size()) {

			clientFile << clients[index].getId() << "\n"
				<< clients[index].getName() << "\n"
				<< clients[index].getPassword() << "\n"
				<< clients[index].checkBalance() << endl;
			index++;
		}
		clientFile.close();
	}
	void modifyClientInfo(Client& a) {
		string cName, pass;
		double bal;
		cout << "Please enter client information after modification :\n";
		cout << "Username : ";
		cin >> cName;
		cout << "Password : ";
		cin >> pass;
		cout << "Balance : ";
		cin >> bal;

		//////////////////////////////////
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
					if (bal >= 1500) {

						remove("Database/Client.txt");
						//modify it in vector
						int i = 0;
						while (i < clients.size()) {
							if (clients[i].getId() == a.getId()) {

								clients[i].setName(cName);
								clients[i].setPassword(pass);
								clients[i].setBalance(bal);
								break;
							}
							i++;
						}
						ofstream clientFile;
						clientFile.open("Database/Client.txt", ios::out | ios::app);
						int index = 0;
						while (index < clients.size()) {
							clientFile << clients[index].getId() << "\n"
								<< clients[index].getName() << "\n"
								<< clients[index].getPassword() << "\n"
								<< clients[index].checkBalance() << endl;
							index++;
						}
						clientFile.close();
					}
					else {
						cout << "Balance must be 1500 at least!\n";
						Sleep(1000);
						cout << "Try again.\n";
						Sleep(1000);
						system("CLS");
						modifyClientInfo(a);
					}
				}
				else {
					cout << "Password must be 8 : 20 !\n";
					Sleep(1000);
					cout << "Try again.\n";
					Sleep(1000);
					system("CLS");
					modifyClientInfo(a);
				}
			}
			else {
				cout << "Name must be 5 : 20 characters.\n";
				Sleep(2000);
				cout << "Try again.\n";
				Sleep(1000);
				system("CLS");
				modifyClientInfo(a);
			}
		}
		else {
			system("CLS");
			cout << "Name must be only alphabetic chars or underscores\n";
			Sleep(2000);
			cout << "Try again.\n";
			Sleep(1000);
			system("CLS");
			modifyClientInfo(a);
		}
		//////////////////////////////////
	}
	Client clientSearchById(int i) {
		int index = 0;
		bool founded = 0;

		for (index; index < clients.size(); index++) {
			if (clients[index].getId() == i) {
				founded = 1;
				break;
			}
		}
		if (founded) {
			return clients[index];
		}
		else {
			throw ClientNotFound();
		}
	}
	void listClients() {
		for (int i = 0; i < clients.size(); i++) {
			cout << clients[i].getId() << " | "
				<< clients[i].getName() << " | "
				<< clients[i].getPassword() << " | "
				<< clients[i].checkBalance() << endl;
		}
	}
	void deleteAllClients() {
		remove("Database/Client.txt");
		clients.clear();
		ofstream clientFile;
		clientFile.open("Database/Client.txt", ios::out | ios::app);
		clientFile.close();
	}

	/*
			-> addNewClient      (Done)
			-> deleteClient      (Done)
			-> editClientInfo    (Done)
			-> clientSearchById  (Done)
			-> listClients       (Done)
			-> deleteAllClients  (Done)
	*/
};