#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <numeric>
#include <unistd.h>
#include <iterator>
#include <list>
#include <math.h>

using namespace std;
namespace day06{
static unordered_map<string, vector<string>> tree;

unordered_map<string, vector<string>> read_input(string loc)
{
	unordered_map<string, vector<string>> in;
	string line;
	ifstream infile (loc);
	if (infile.is_open())
	{
		while (getline(infile,line))
		{
			string AAA = line.substr(0,3);
			string BBB = line.substr(4,3);
			in[AAA].push_back(BBB);
		}
	}
	return in;
}

unsigned int calc_orbits(string key){
	vector<string> v = tree[key];
	cout << v.size();
	for (string s: v){
		calc_orbits(s);
	}
	return 0;
}

int task1(){
	return calc_orbits("COM");
}

int main()
{
	string path = "../inputs/day06.txt";
	unordered_map<string, vector<string>> input = read_input(path);
	tree = input;
	cout << "Star 1: " << task1() << endl;
	return 0;
}
}//namespace day06