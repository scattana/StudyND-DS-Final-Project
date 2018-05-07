#include <iostream>
#include <stdio.h>
#include <chrono>
#include <ctime>
using namespace std;

int main(){
	//time_t t = time(0);
	//tm* now = localtime(&t);
	//cout << (now->tm_year + 1900) << "-" << (now->tm_mon + 1) << "-" << now->tm_mday << "\n";
	chrono::duration<int,ratio<60*60*24>> one_day (1);
	chrono::system_clock::time_point today = chrono::system_clock::now();
	time_t tt = chrono::system_clock::to_time_t (today);
	cout << "today is " << ctime(&tt);
	return EXIT_SUCCESS;
}
