#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <regex>
#include <stack>

using namespace std;

struct worker
{
	int id;
	bool is_working;
	char task;
	int time_done;
};

vector<string> read_input(string filename)
{
	vector<string> in;
	string line;
	ifstream infile (filename);
	if (infile.is_open())
	{
		while (getline(infile,line))
		{
			in.push_back(line);
		}
	}
	return in;
}

map<char,vector<char>> parse_input(vector<string> in)
{
	map<char,vector<char>> parsed; 
	regex rgx("Step ([A-Z]) must be finished before step ([A-Z]) can begin.");
	smatch matches;
	char a,b;
	for (auto it=in.begin(); it!=in.end(); ++it)
	{
		if (regex_search(*it, matches, rgx))
		{
			if (matches.size()!=3)
				cout << "WTF!";
			//cout << matches[1] << endl;
			a = matches[1].str()[0];
			b = matches[2].str()[0];
			parsed[a].push_back(b);
			if (parsed.count(b) == 0)
				parsed[b] = {};
		}
	}
	return parsed;
}

bool has_no_dependecy(char c, map<char,vector<char>> instr, vector<char> skip)
{
	bool no_dependency = true;
	for (auto it = instr.begin(); it != instr.end(); ++it)
	{
		if (find(skip.begin(),skip.end(), it->first) == skip.end())
		{
			for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
			{
				no_dependency = no_dependency && (c != (*it2));
			}
		}
	}
	return no_dependency;
}

vector<char> part_one(map<char,vector<char>> instr, vector<char> start_candidates)
{
	vector<char> to_do;
	vector<char> candidates = start_candidates;
	while (to_do.size() < instr.size())
	{
		sort(candidates.begin(), candidates.end());
		char last = candidates[0];
		candidates.erase(candidates.begin());
		to_do.push_back(last);
		for (auto it2 = instr[last].begin(); it2!=instr[last].end();++it2)
		{
			if(has_no_dependecy(*it2, instr, to_do))
				candidates.push_back(*it2);
		}
	}
	return to_do;
}

vector<char> part_two(map<char,vector<char>> instr, vector<char> start_candidates)
{
	vector<char> to_do;
	vector<char> candidates = start_candidates;
	while (to_do.size() < instr.size())
	{
		sort(candidates.begin(), candidates.end());
		char last = candidates[0];
		candidates.erase(candidates.begin());
		to_do.push_back(last);
		for (auto it2 = instr[last].begin(); it2!=instr[last].end();++it2)
		{
			if(has_no_dependecy(*it2, instr, to_do))
				candidates.push_back(*it2);
		}
	}
	return to_do;
}


int main(int, char**)
{
	vector<string> in = read_input("../inputs/day07.txt");
	map<char,vector<char>> instr = parse_input(in);
	vector<char> to_do;
	vector<char> candidates;
	bool no_dependency;
	for (auto it = instr.begin(); it != instr.end(); ++it)
	{
		no_dependency = has_no_dependecy(it->first, instr, {'0'});
		if (no_dependency)
			candidates.push_back(it->first);		
	}	
	to_do = part_one(instr, candidates);
	cout << "Task 1: ";
	for (auto i: to_do)
		cout << i;
	cout << endl;
	return 0;
}