#pragma warning(disable: 4996)
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <conio.h>
using namespace std;
struct person {
	int balance[5];
	string user[5]{ "user1", "user2", "user3", "user4", "user5" }, pass[5]{ "pass1","pass2", "pass3", "pass4", "pass5" };
}xen;
void deposit(int& x, string cred1, string user_report[]);
void withdraw(int& y, string cred2, string user_report[]);
void inquiry(int z);
void report_user(string cred3, string user_report[]);
void report_employee(string user_report[]);
void main() {
	int selection, balance, balance2[5]{};
	string  credentials1, status, credentials2, line{}, user_report[5]{ "report1.txt", "report2.txt", "report3.txt", "report4.txt", "report5.txt" };
	fstream balances("balances.txt", ios::in);
	for (int i = 0; i < 5; i++) {
		balances >> balance2[i];
	}
	system("color 0a");
	cout << "\t\t\tHello and welcome to our ATM" << endl;
Welcoming:
	cout << "\nPlease press 1 if you are a bank employee and 2 if you are a client: ";
	cin >> status;
	if (status == "1") {
	Login_emp:
		system("CLS");
		string emp_user, emp_pass;
		cout << "\nPlease enter your username and password: " << endl;
		cin >> emp_user >> emp_pass;
		if (emp_user == "emp1" && emp_pass == "pass1") {
			report_employee(user_report);
		here:
			cout << "\nWould you like to login as a user?(y/n)";
			string ans3; cin >> ans3;
			if (ans3 == "y" || ans3 == "Y") { goto Login; }
			else if (ans3 == "n" || ans3 == "N") { cout << "Ok, bye!!"; balances.close(); exit(-1); }
			else { cout << "Invalid entry, Please try again!!" << endl; goto here; }
		}
		else {
			cerr << "Invalid entry, Please try again: " << endl;
			goto Login_emp;
		}
	}
	else if (status == "2") {
	Login:
		bool checker = false;
		do {
			system("CLS");
			cout << "\nPlease Enter your Username and password: " << endl;
			cin >> credentials1 >> credentials2;
			/*we check if the username and password is correct and then assigning their balance to the variable "balance"
			so that we can use it later to save in the file
			*/
			for (int i = 0; i < 5; i++) {
				if (credentials1 == xen.user[i] && credentials2 == xen.pass[i]) {
					balance = balance2[i];
					checker = true;
				}
			}
			if (checker == false) {
				cout << "\nInvalid entry, Please try again: ";
			}
		} while (checker == false);
	}
	else {
		cerr << "\nInvalid entry, please try again!";
		system("CLS");
		goto Welcoming;
	}
menu:
	do {
		cout << "\nPress 1 if you want to deposit cash into your account" << endl;
		cout << "Press 2 if you want to withdraw cash from your account" << endl;
		cout << "Press 3 if you want to inquire about your bank balance" << endl;
		cout << "Press 4 if you want to generate a report about your last 5 transactions" << endl;
		cout << "Press 5 if you want to login as an employee" << endl;
		cout << "Press 6 if you want to login as a different user" << endl;
		cout << "Press 0 f you want to close our program" << endl;
		cin >> selection;
		if (selection == 1) {
			deposit(balance, credentials1, user_report);
			for (int i = 0; i < 5; i++) {
				if (credentials1 == xen.user[i]) {
					balance2[i] = balance;
				}
			}
			//rewriting the file so that we can edit the specific balance for a specific user
			int g{ 0 };
			fstream balances("balances.txt", ios::trunc, ios::trunc);
			for (int y = 0; y < 5; y++) {
				g = balance2[y];
				balances << g << endl;
			}
		}
		else if (selection == 2) {
			withdraw(balance, credentials1, user_report);
			for (int i = 0; i < 5; i++) {
				if (credentials1 == xen.user[i]) {
					balance2[i] = balance;
				}
			}
			//rewriting the file so that we can edit the specific balance for a specific user
			int t;
			fstream balances("balances.txt", ios::out);
			for (int y = 0; y < 5; y++) {
				t = balance2[y];
				balances << t << endl;
			}
		}
		else if (selection == 3) {
			inquiry(balance);
		}
		else if (selection == 4) {
			report_user(credentials1, user_report);
		}
		else if (selection == 0) {
			cout << "Thank for doing business with us!" << endl;
			balances.close();
			exit(-1);
		}
		else if (selection == 5) { goto Login_emp; }
		else if (selection == 6) { goto Login; }
		else if (selection != 0) {
			cout << "\aWrong entry, please try again!";
			goto menu;
		}
	} while (selection != 0);
}
void deposit(int& x, string cred1, string user_report[]) {
	string line;
	int money_deposited;
	cout << "How much money do you want deposited? ";
enter_deposit:
	cin >> money_deposited;
	if (money_deposited <= 0) { cout << "Please enter a positive value: "; goto enter_deposit; }
	x += money_deposited;
	system("CLS");
	cout << "\nYou deposited " << money_deposited << ", your balance is " << x << endl;
	time_t now = time(0);
	char* display_time = ctime(&now);
	for (int k = 0; k < 5; k++) {
		if (cred1 == xen.user[k]) {
			fstream ifs(user_report[k], ios::in);
			string line((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
			fstream ofs(user_report[k], ios::trunc);
			fstream ofs2(user_report[k], ios::out);
			ofs2 << line << xen.user[k] << " deposited " << money_deposited << " in " << display_time;
		}
	}
}
void withdraw(int& y, string cred2, string user_report[]) {
withdraw_again:
	string line;
	int money_withdrawn;
	cout << "\nHow much money do you want withdrawn? " << endl;
enter_withdraw:
	cin >> money_withdrawn;
	if (money_withdrawn <= 0) { cout << "Please enter a positive value: "; goto enter_withdraw; }
	if (money_withdrawn <= y) {
		y -= money_withdrawn;
		system("CLS");
		cout << "\nYou withdrew: " << money_withdrawn << ", your balance is " << y << endl;
		time_t now = time(0);
		char* display_time = ctime(&now);
		for (int k = 0; k < 5; k++) {
			if (cred2 == xen.user[k]) {
				fstream ifs(user_report[k], ios::in);
				string line((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
				fstream ofs(user_report[k], ios::trunc);
				fstream ofs2(user_report[k], ios::out);
				ofs2 << line << xen.user[k] << " withdrew " << money_withdrawn << " in " << display_time;
			}
		}
	}
	else {
		cerr << "\aInsufficient funds, please try again!";
		goto withdraw_again;
	}
}
void inquiry(int z) {
	system("CLS");
	cout << "Your balance is " << z << endl;
}
void report_user(string cred4, string user_report[]) {
	system("CLS");
	string lines;
	for (int i = 0; i < 5; i++) {
		if (cred4 == xen.user[i]) {
			fstream myfile(user_report[i], ios::in);
			string line, index[5];
			const size_t SIZE = (sizeof index / sizeof * index);//size of the array index "5"
			size_t i = 0;
			//reading file lines and putting them in the string "line"
			while (getline(myfile, line)) {
				index[i] = line;
				if (++i >= SIZE) { i = 0; }
			}
			for (size_t j = 0; j < SIZE; ++j) {
				cout << index[i] << "\n";
				if (++i >= SIZE) { i = 0; }
			}
		}
	}
}
void report_employee(string user_report[]) {
	system("CLS");
	cout << "\nWhich user do you to view his/her transactions? ";
user_try:
	bool cond = false;
	string ans, line; cin >> ans;
	do {
		for (int i = 0; i < 5; i++) {
			if (ans == xen.user[i]) {
				cond = true;
				fstream balancesss(user_report[i], ios::in);
				string line((istreambuf_iterator<char>(balancesss)), (istreambuf_iterator<char>()));
				cout << "\n" << line;
			}
		}
		if (cond == false) {
			cout << "\nThere is no such user, please try again: "; goto user_try;
		}
	} while (cond == false);

	cout << "\nWould you like to check another user?(y/n) ";
	string st;
	cin >> st;
	if (st == "Y" || st == "y") {
		cout << "\nWhich user do you to view his/her transactions? ";
		goto user_try;
	}
	else if (st != "n" && st != "N") { cerr << "\nInvalid entry, please try again!"; }
};