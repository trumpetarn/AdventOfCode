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
namespace day09{
vector<long long int> read_input(string loc)
{
	vector<long long int> in;
	string line;
	ifstream infile (loc);
	if (infile.is_open())
	{
		while (getline(infile,line,','))
		{
			in.push_back(stoi(line));
		}
	}
	return in;
}

void task1(vector<long long int> input){
	Intcode i;
	i.set_program(input);
	i.increase_memory(100000);
	i.run(1);
	cout << "Star 1: " << i.get_last_output() << endl;
}

void task2(vector<long long int> input){
	Intcode i;
	i.set_program(input);
	i.increase_memory(100000);
	i.run(2);
	cout << "Star 1: " << i.get_last_output() << endl;
}

int main()
{
	string path = "../inputs/day09.txt";
	vector<long long int> input = read_input(path);
	//input = {104,1125899906842624,99};
	//input = {1102,34915192,34915192,7,4,7,99,0};
	//input = {109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99};
	task1(input);
	task2(input);
	
	return 0;
}
}//namespace day09