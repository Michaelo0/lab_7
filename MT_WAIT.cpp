// ConsoleApplication1.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
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
	for (int i = 0; i < 100; i++) {
		if(i + 1 == 50)
			waiter.notify_one();
		this_thread::sleep_for(chrono::milliseconds(10));
		cout << "bbbbb\n";
	}

	return;
}


void f2(void) {
	unique_lock<mutex> lk(mute);
	waiter.wait(lk);
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