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
	
	int displacement = 0;
	int displacement20 = 0;
	map<string,char> change_map;
	for (int i=2; i<(int)in.size(); i++)
	{
		change_map[in[i].substr(0,5)] = in[i][9];
	}
	list<string> hist;
	string gen20;
	for (int gen=0; gen<500000; gen++)
	{
		string next_gen = initial;
		for (int i=2; i<(int)initial.size()-2; i++)
		{
			//initial = initial + ".....";
			string temp = initial.substr(i-2,5);
			next_gen[i] = change_map[temp];
		}
		auto first_hash = next_gen.find('#');
		if (first_hash > 10)
			first_hash -= 5;
		else
			first_hash = 0;
		displacement += (int) first_hash;
		next_gen.erase(0,first_hash);
		//cout << first_hash<< ','<< displacement << ':' << next_gen.size() << endl;
		next_gen.append(first_hash,'.');
		//cout << next_gen << endl;
		//cout << next_gen << endl;
		//cout << first_hash << ':' << next_gen.size() << ':' << initial.size() << endl;
		initial = next_gen;
		if (gen==19)
		{
			gen20 = initial;
			displacement20 = displacement;
		}
		//cout << initial << endl << endl;
		if (find(hist.begin(), hist.end(), initial) != hist.end())
		{
			cout << gen << ": Recurrence " << *(find(hist.begin(), hist.end(), initial)) << endl;
			break;
		}
		hist.push_back(initial);
	}
	long long int ans1 = 0;
	long long int ans2 = 0;
	for (int i=0; i<(int)initial.size(); i++)
	{
		if (gen20[i] == '#')
			ans1 += i-20+displacement20;
		if (initial[i] == '#')
			ans2 += i-20+displacement+(50000000000-hist.size()-1);
	}	

	cout << "Task 1: " << ans1 << endl;
	cout << "Task 2: " << ans2 << endl;

	return 0;
}