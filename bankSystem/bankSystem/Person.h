#include<iostream>
using namespace std;
#pragma once

class Person {
protected:
	int id;
	string name, password;
public:
	Person() {
		id = 0; name = "-----"; password = "********";
	}
	Person(int i, string n, string pass) {
		id = i;
		name = n;
		password = pass;
	}
	void setId(int i) {
		id = i;
	}
	void setName(string n) {
		name = n;
	}
	void setPassword(string pass) {
		password = pass;
	}

	int getId() {
		return id;
	}
	string getName() {
		return name;
	}
	string getPassword() {
		return password;
	}

	virtual void displayMyInfo() = 0;
};