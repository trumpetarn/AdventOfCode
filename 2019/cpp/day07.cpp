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

int amplifiers(vector<int> instr, vector<int> phase){
	int input=0;
	int out;
	for (int i=0; i<5; i++){
		//cout << input << ':';
		intcode::run(instr, {phase[i], input}, out);
		input = out;
	}
	//cout << input << endl;
	return input;
}

int amplifiers2(vector<int> instr, int &input){
	int out, ret;
	for (int i=0; i<5; i++){
		cout << input << ':';
		//ret = intcode::run(instr, {input}, out);
		input = out;
		if (ret==0)
			break;
	}
	cout << input << endl;
	return ret;
}

void task1(vector<int> instr){
	vector<int> phases = {0,1,2,3,4};
	int n,max = 0;
	vector<int> perm;
	do{
		//print_vector(phases,' ');
		n = amplifiers(instr, phases);
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
		n = amplifiers(instr, phases);
		while (amplifiers2(instr, n) != 0);
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
	//vector<int> input = read_input(path);
	//vector<int> input =  {3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0};
	vector<int> input = {3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5};
	task1(input); //914828 
	task2(input);
	return 0;
}
}//namespace day07