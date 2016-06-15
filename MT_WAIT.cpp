// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>



using namespace std;


mutex mute;
condition_variable waiter;

void f1(void) {
	unique_lock<mutex> lock(mute);

	for (int i = 0; i < 50; i++) {
		this_thread::sleep_for(chrono::milliseconds(10));
		cout << "bbbbb\n";
	}

	lock.unlock();
	waiter.notify_one();

	for (int i = 0; i < 50; i++) {
		this_thread::sleep_for(chrono::milliseconds(10));
		cout << "bbbbb\n";
	}

	return;
}


void f2(void) {
	unique_lock<mutex> lk(mute);
	waiter.wait(lk, []() { return true;});


	for (int i = 0; i < 100; i++) {
		this_thread::sleep_for(chrono::milliseconds(10));
		cout << "aaaaa\n";
	}

	return;
}


int main(void) {
	thread t1(f1);
	thread t2(f2);

	t1.join();
	t2.join();

	return 0;
}
