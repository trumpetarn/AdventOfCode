#include <iostream>
#include "aoc.h"
#include <chrono> 

using namespace std;

void time_it(void(*f)()){
	auto start = chrono::high_resolution_clock::now(); 
	(*f)();
	auto end = chrono::high_resolution_clock::now(); 
	auto duration = chrono::duration_cast<chrono::microseconds>(end-start); 
	if (duration > chrono::milliseconds(10)){
		cout << "Execution time: " << chrono::duration_cast<chrono::milliseconds>(duration).count() << " ms" << endl << endl; 
	}else{
		cout << "Execution time: " << duration.count() << " \u03BCs" << endl << endl; 
	}
}

void run_day(int n) {
	cout << "--- Day " << n << " ---" << endl;
	switch (n) {
		case 1:
			time_it(day01::main);
			break;
		case 2:
			time_it(day02::main);
			break;
		case 3:
			time_it(day03::main);
			break;
		case 4:
			time_it(day04::main);
			break;
		case 5:
			time_it(day05::main);
			break;
		case 6:
			time_it(day06::main);
			break;
		case 7:
			time_it(day07::main);
			break;
		case 8:
			time_it(day08::main);
			break;
		case 9:
			time_it(day09::main);
			break;
		case 10:
			time_it(day10::main);
			break;
		case 11:
			time_it(day11::main);
			break;
		case 12:
			time_it(day12::main);
			break;
		case 13:
			time_it(day13::main);
			break;
		case 14:
			time_it(day14::main);
			break;
		case 15:
			time_it(day15::main);
			break;
		case 16:
			time_it(day16::main);
			break;
		case 17:
			time_it(day17::main);
			break;
		case 18:
			time_it(day18::main);
			break;
		case 19:
			time_it(day19::main);
			break;
		case 20:
			time_it(day20::main);
			break;
		case 21:
			time_it(day21::main);
			break;
		case 22:
			time_it(day22::main);
			break;
		case 23:
			time_it(day23::main);
			break;
		case 24:
			time_it(day24::main);
			break;
		case 25:
			time_it(day25::main);
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