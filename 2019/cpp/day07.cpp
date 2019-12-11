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
	int input = 0;
	for (int i=0; i<5; i++){
		cout << input << ',';
		input = intcode::run(instr, {phase[i], input});
	}
	cout << input << endl;
	return input;
}

void task1(vector<int> instr){
	vector<int> phases = {0,1,2,3,4};
	int n,max = 0;
	vector<int> perm;
	do{
		print_vector(phases,' ');
		n = amplifiers(instr, phases);
		if (n>max){
			perm=phases;
			max = n;
		}
	}while(next_permutation(phases.begin(),phases.end()));
	cout << "Star 1: ";
	print_vector(perm,' ');
}

int main()
{
	string path = "../inputs/day07.txt";
	//vector<int> input = read_input(path);
	vector<int> input =  {3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0};
	task1(input);
	return 0;
}
}//namespace day07