#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"Person.h"

using namespace std;
#pragma once

class Client :public Person {
public:
	vector<Client> clientdb;
	double balance;
public:
	//Constructors
	Client() {
		balance = 1500;
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
				clientdb.push_back(c);
				i++;
			}
			clientFile.close();
		}
	}
	Client(int i, string n, string pass, double bal) :Person(i, n, pass) {
		balance = bal;
	}
	//Methods
	void setBalance(double bal) {
		balance = bal;
	}
	double checkBalance() {
		return balance;
	}
	void deposite(int i, double money) {
		remove("Database/Client.txt");
		int index = 0;
		for (index; index < clientdb.size(); index++) {
			if (clientdb[index].getId() == i) {
				break;
			}
		}
		clientdb[index].balance += money;

		ofstream clientFile;
		clientFile.open("Database/Client.txt", ios::out | ios::app);

		index = 0;
		while (index < clientdb.size()) {
			clientFile << clientdb[index].getId() << "\n"
				<< clientdb[index].getName() << "\n"
				<< clientdb[index].getPassword() << "\n"
				<< clientdb[index].checkBalance() << endl;
			index++;
		}
		clientFile.close();
		//balance += money;
	}

	void withdraw(int i, double money) {
		if (money > balance) {
			cout << "AMOUNT EXCEEDED!";
		}
		else {
			remove("Database/Client.txt");
			int index = 0;
			for (index; index < clientdb.size(); index++) {
				if (clientdb[index].getId() == i) {
					break;
				}
			}
			clientdb[index].balance -= money;

			ofstream clientFile;
			clientFile.open("Database/Client.txt", ios::out | ios::app);

			index = 0;
			while (index < clientdb.size()) {
				clientFile << clientdb[index].getId() << "\n"
					<< clientdb[index].getName() << "\n"
					<< clientdb[index].getPassword() << "\n"
					<< clientdb[index].checkBalance() << endl;
				index++;
			}
			clientFile.close();
		}
	}
	void transferTo(int i, double money, Client& recipient) {
		if (this->balance < money) {
			cout << "AMOUNT EXCEEDED!";
		}
		else {
			withdraw(i, money);
			deposite(recipient.getId(), money);
		}
	}
	void displayMyInfo() {
		cout << "Client info :\n";
		cout << "\tId : " << id << endl;
		cout << "\tName : " << name << endl;
		cout << "\tPassword : " << password << endl;
		cout << "\tBalance : " << balance << endl;
	}
};