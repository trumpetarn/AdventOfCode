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

using namespace std;



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

int main(int argc, char** argv)
{
	string loc = "../inputs/day12.txt";
	if (argc >= 2)
		loc = argv[1];

	vector<string> in = read_input(loc);
	string initial = "....................";
	initial += in[0].substr(15);
	initial += "........................................";
	map<string,char> change_map;
	for (int i=2; i<(int)in.size(); i++)
	{
		change_map[in[i].substr(0,5)] = in[i][9];
	}
	for (int gen=0; gen<20; gen++)
	{
		string next_gen = initial;
		for (int i=2; i<(int)initial.size()-2; i++)
		{
			string temp = initial.substr(i-2,5);
			next_gen[i] = change_map[temp];
		}
		initial = next_gen;
		cout << initial << endl;
	}
	int ans = 0;
	for (int i=0; i<(int)initial.size(); i++)
	{
		if (initial[i] == '#')
			ans += i-20;
	}	
	cout << "Task 1: " << ans << endl;
	return 0;
}