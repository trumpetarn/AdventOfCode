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

int main(int, char**)
{
	vector<string> in = read_input("../inputs/day07.txt");
	map<char,vector<char>> instr = parse_input(in);
	stack<char> to_do;
	for (auto it = instr.begin(); it != instr.end(); ++it)
	{
		to_do.push();
	}
	cout << "Task 1:";
	while (!to_do.empty()) {
		cout<<to_do.top();
		to_do.pop();
	}
	cout << endl;
	return 0;
}