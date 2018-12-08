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
#define TIME 0

using namespace std;

struct worker_t
{
	bool is_working;
	char task;
	int done_time;
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

vector<char> part_two(map<char,vector<char>> instr, vector<char> start_candidates, int num_workers)
{
	vector<worker_t> workers;
	for (int i=0; i < num_workers; i++)
	{
		worker_t temp = {false, '0', 0};
		workers.push_back(temp);
	}
	vector<char> done;
	vector<char> active;
	vector<char> candidates = start_candidates;
	char last;
	int time = 0;
	while (done.size() < instr.size() && time < 10000)
	{
		sort(candidates.begin(), candidates.end());
		int i = 0;
		for (auto it=workers.begin(); it != workers.end(); ++it)
		{
			i++;
			if ((it->is_working) && (it->done_time == time)){ //done
				it->is_working = false;
				done.push_back(it->task);
				for (auto it2 = instr[it->task].begin(); it2!=instr[it->task].end();++it2)
				{
					if(has_no_dependecy(*it2, instr, active))
						candidates.push_back(*it2);
				}
			}
			//assign
			if ((!it->is_working) && candidates.size()>0)
			{
				last = candidates[0];
				candidates.erase(candidates.begin());
				active.push_back(last);
				it->is_working = true;
				it->task = last;
				int task_time = (int) (last - 'A') + 1 +TIME;
				it->done_time = time+task_time;
				cout << time << ' ' << i << " Started working: " 
							<< last << ':' << it->done_time << endl;
			}
		}
		time++;
	}
	cout << "Time: " << time << endl;
	return done;
}

int main(int, char**)
{
	//vector<string> in = read_input("../inputs/day07.txt");
	vector<string> in = read_input("../inputs/day07_example.txt");
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
	to_do = part_two(instr, candidates, 2);
	cout << "Task 2: ";
	for (auto i: to_do)
		cout << i;
	cout << endl;
	return 0;
}