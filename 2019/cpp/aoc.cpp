#include <iostream>
#include "aoc.h"
#include <chrono> 

using namespace std;

void time_it(void(*f)()){
	auto start = chrono::high_resolution_clock::now(); 
	(*f)();
	auto end = chrono::high_resolution_clock::now(); 
	auto duration = chrono::duration_cast<chrono::microseconds>(end-start); 
	cout << "Execution time: " << duration.count() << " \u03BCs" << endl; 
}

int main(int argc, char** argv) {
	time_it(day01::main);
	time_it(day02::main);
	return 0;
}