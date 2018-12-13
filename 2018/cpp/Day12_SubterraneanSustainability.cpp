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
	string initial = in[0].substr(15);
	map<string,char> change_map;
	for (int i=2; i<(int)in.size(); i++)
	{
		change_map[in[i].substr(0,5)] = in[i][9];
	}
	for (int gen=0; gen<20; gen++)
	{
		string next_gen = initial;
		string temp = ".." + initial.substr(0,3);
		next_gen[0] = change_map[temp];
		temp = "." + initial.substr(0,4);
		next_gen[1] = change_map[temp];
		int len = (int)initial.size()-2;
		for (int i=2; i<len; i++)
		{
			temp = initial.substr(i-2,5);
			next_gen[i] = change_map[temp];
		}
		temp = initial.substr(len-4,4) + ".";
		next_gen[len-1] = change_map[temp];
		temp = initial.substr(len-3,3) + "..";
		next_gen[len] = change_map[temp];
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