#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <numeric>
#include <unistd.h>
#include <iterator>
#include <list>
#include <math.h>
#include "intcode.h"

#define NUM_AMPLIFIERS 5

using namespace std;
namespace day07{
void print_vector(vector<int> v, char delim){
	for (auto i : v){
		cout << i << delim;
	}
	cout << endl;
}

vector<int> read_input(string loc)
{
	vector<int> in;
	string num;
	ifstream infile (loc);
	if (infile.is_open())
	{
		while (getline(infile,num,','))
		{
			in.push_back(stoi(num));
		}
	}
	return in;
}

int amplifiers(vector<int> instr, vector<int> phase, int input){
	Intcode intcode[NUM_AMPLIFIERS];
	for (int i=0; i<NUM_AMPLIFIERS; i++){
		intcode[i].set_program(instr);
		// Provide phase
		intcode[i].provide_input(phase[i]);
		intcode[i].run(input);
		input = intcode[i].get_last_output();
	}
	return input;
}

int amplifier_loop(vector<int> instr, vector<int> phase){
	Intcode intcode[NUM_AMPLIFIERS];
	// Insert phase
	for (int i=0; i<NUM_AMPLIFIERS; i++){
		intcode[i].set_program(instr);
		// Provide phase
		intcode[i].provide_input(phase[i]);
	}
	bool has_halted = false;
	int input = 0;
	while (!has_halted){
		for (int i=0; i<NUM_AMPLIFIERS; i++){
			intcode[i].provide_input(input);
			has_halted = !intcode[i].run2output();
			input = intcode[i].get_last_output();
		}
	}
	return input;
}

void task1(vector<int> instr){
	vector<int> phases = {0,1,2,3,4};
	int n,max = 0;
	vector<int> perm;
	do{
		//print_vector(phases,' ');
		n = amplifiers(instr, phases, 0);
		if (n>max){
			perm=phases;
			max = n;
		}
	}while(next_permutation(phases.begin(),phases.end()));
	cout << "Star 1: " << max << " with phase ";
	print_vector(perm,'\0');
}

void task2(vector<int> instr){
	vector<int> phases = {5,6,7,8,9};
	int n,max = 0;
	vector<int> perm;
	do{
		n = amplifier_loop(instr, phases);
		if (n>max){
			perm=phases;
			max = n;
		}
	}while(next_permutation(phases.begin(),phases.end()));
	cout << "Star 2: " << max << " with phase ";
	print_vector(perm,'\0');
}

int main()
{
	string path = "../inputs/day07.txt";
	vector<int> input = read_input(path);
	task1(input); //914828 
	task2(input);
	return 0;
}
}//namespace day07