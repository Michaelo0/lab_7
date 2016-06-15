// threads2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <chrono>
#include<string>




using namespace std;


void echo(string s) {
	cout << s << endl;

	return;
}


void alarm(int time) {
	this_thread::sleep_for(chrono::seconds(time));

	cout << "\nAlarm!!1!" << endl;



	return;
}
void processor(void) {
	string command;

	cin >> command;

	if (command == "echo") {
		string s;
		getline(cin, s);
		thread t(echo, s);
		t.join();
	}
	else if (command == "alarm") {
		int seconds;
		cin >> seconds;
		thread t(alarm, seconds);
		t.join();
	}

	return;
}


int main(void) {
	while (!cin.eof())
		processor();

	return 0;
}
