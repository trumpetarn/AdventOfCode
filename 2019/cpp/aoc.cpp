#include <iostream>
#include "aoc.h"
#include <chrono> 

using namespace std;

void time_it(void(*f)()){
	auto start = chrono::high_resolution_clock::now(); 
	(*f)();
	auto end = chrono::high_resolution_clock::now(); 
	auto duration = chrono::duration_cast<chrono::microseconds>(end-start); 
	cout << "Execution time: " << duration.count() << " \u03BCs" << endl << endl; 
}

void run_day(int n) {
	//cout << "--- Day " << n << " ---" << endl;
	switch (n) {
		case 1:
			time_it(day01::main);
			break;
		case 2:
			time_it(day02::main);
			break;
		default:
			break;
	}
}

int main(int argc, char** argv) {
	if (argc > 1) {
		try {
			int n = stoi(argv[1]);
			run_day(n);
		}catch (exception& e){
			cout << "ERROR: Could not convert input to int" << endl;
		}
	}else{
		for (int i=1; i<26; i++) {
			run_day(i);
		}
	}
	return 0;
}