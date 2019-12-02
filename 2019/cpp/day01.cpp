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

using namespace std;
namespace day01{

vector<string> read_input(string loc)
{
	vector<string> in;
	string line;
	ifstream infile (loc);
	if (infile.is_open())
	{
		while (getline(infile,line))
		{
			in.push_back(line);
		}
	}
	return in;
}

int compute_fuel(int mass) {
	int fuel = floor(mass/3)-2;
	if (fuel < 0)
		return 0;
	return fuel;
}

void task1(vector<string> in) {
	int totalFuel = 0;
	for (auto n : in) {
		totalFuel += compute_fuel(stoi(n));
	}
	printf("Star 1: %d\n", totalFuel);
}

void task2(vector<string> in) {
	int totalFuel = 0;
	for (auto n : in) {
		int fuel = compute_fuel(stoi(n));
		int moduleFuel = fuel;
		while (fuel > 0) {
			fuel = compute_fuel(fuel);
			moduleFuel += fuel;
		}
		totalFuel += moduleFuel;
	}
	printf("Star 2: %d\n", totalFuel);
}

int main()
{
	string loc = "../inputs/day01.txt";
	vector<string> in = read_input(loc);
	task1(in);
	task2(in);
	return 0;
}
}