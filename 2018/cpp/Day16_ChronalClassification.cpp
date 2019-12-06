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
#include <regex>
#include <iterator>
#include <list>
#define N 4
#define NumOP 15

using namespace std;
typedef int regid;
typedef int value;

int reg[N] = {0,0,0,0};

void addr(regid A, regid B, regid C)
{
	reg[C] = reg[A] + reg[B];
	return;
}

void addi(regid A, value B, regid C)
{
	reg[C] = reg[A] + B;
	return;
}

void mulr(regid A, regid B, regid C)
{
	reg[C] = reg[A]*reg[B];
	return;
}

void muli(regid A, value B, regid C)
{
	reg[C] = reg[A]*B;
	return;
}

void banr(regid A, regid B, regid C)
{
	reg[C] = (reg[A] & reg[B]);
	return;
}

void bani(regid A, value B, regid C)
{
	reg[C] = (reg[A] & B);
	return;
}


void borr(regid A, regid B, regid C)
{
	reg[C] = (reg[A] | reg[B]);
	return;
}

void bori(regid A, value B, regid C)
{
	reg[C] = (reg[A] | B);
	return;
}

void setr(regid A, regid C)
{
	reg[C] = reg[A];
	return;
}

void seti(value A, regid C)
{
	reg[C] = A;
	return;
}

void gtir(value A, regid B, regid C)
{
	reg[C] = (int) (A > reg[B]);
	return;
}

void gtri(regid A, value B, regid C)
{
	reg[C] = (int) (reg[A] > B);
	return;
}

void gtrr(regid A, regid B, regid C)
{
	reg[C] = (int) (reg[A] > reg[B]);
	return;
}

void eqir(value A, regid B, regid C)
{
	reg[C] = (int) (A == reg[B]);
	return;
}

void eqri(regid A, value B, regid C)
{
	reg[C] = (int) (reg[A] == B);
	return;
}

void eqrr(regid A, regid B, regid C)
{
	reg[C] = (int) (reg[A] == reg[B]);
	return;
}

void set_reg(int n[N])
{
	for (int i=0; i<N; i++)
		reg[i]=n[i];
}

bool is_equal(int a[N], int b[N])
{
	for (int i=1; i<N; i++)
	{
		if (a[i]!=b[i])
			return false;
	}
	return true;
}

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


void run_operation(int opcode, int operation[N])
{
	switch (opcode)
	{
		case 0:
			addr(operation[1],operation[2],operation[3]);
			break;
		case 1:
			addi(operation[1],operation[2],operation[3]);
			break;
		case 2:
			mulr(operation[1],operation[2],operation[3]);
			break;
		case 3:
			muli(operation[1],operation[2],operation[3]);
			break;
		case 4:
			banr(operation[1],operation[2],operation[3]);
			break;
		case 5:
			bani(operation[1],operation[2],operation[3]);
			break;
		case 6:
			borr(operation[1],operation[2],operation[3]);
			break;
		case 7:
			bori(operation[1],operation[2],operation[3]);
		case 8:
			setr(operation[1],operation[3]);
			break;
		case 9:
			seti(operation[1],operation[3]);
			break;
		case 10:
			gtri(operation[1],operation[2],operation[3]);
			break;
		case 11:
			gtir(operation[1],operation[2],operation[3]);
			break;
		case 12:
			gtrr(operation[1],operation[2],operation[3]);
			break;
		case 13:
			eqri(operation[1],operation[2],operation[3]);
			break;
		case 14:
			eqir(operation[1],operation[2],operation[3]);
			break;
		case 15:
			eqrr(operation[1],operation[2],operation[3]);
			break;
	}
	return;
}

vector<int> try_all_operations(int before[N], int after[N], int operation[N])
{
	vector<int> works;
	for (int i=0; i<=NumOP; i++)
	{
		set_reg(before);
		cout << i << endl;
		cout << "B: " << reg[0]<< reg[1]<< reg[2]<< reg[3] << endl;
		run_operation(i, operation);
		cout << "A: " << reg[0]<< reg[1]<< reg[2]<< reg[3] << endl;
		if (is_equal(reg,after))
			works.push_back(i);
	}
	return works;
}

int part_one(vector<string> in)
{
	int res= 0;
	int before[N], after[N], oper[N];
	string temp;
	string regular = ".*\\[([0-9]+), ([0-9]), ([0-9]), ([0-9])]";

	for (auto it=in.begin(); it!=in.end(); it+=4)
	{
		regex rgx(regular);
		smatch matches;
		if (regex_search((*it), matches, rgx))
		{
			if (matches.size()>4)
			{
				before[0] = stoi(matches[1]);
				before[1] = stoi(matches[2]);
				before[2] = stoi(matches[3]);
				before[3] = stoi(matches[4]);
			}
		}
		
		if (regex_search(*(it+2), matches, rgx))
		{
			if (matches.size()>4)
			{
				after[0] = stoi(matches[1]);
				after[1] = stoi(matches[2]);
				after[2] = stoi(matches[3]);
				after[3] = stoi(matches[4]);
			}
		}
		
		stringstream tmp(*(it+1));
		int i=0;
		while (!tmp.eof())
		{
			tmp >> temp;
			oper[i] = stoi(temp);
			i++;
		}
		vector<int> temp = try_all_operations(before, after, oper);
		if (temp.size()>=3)
			res++;

		//Die after first half
		if (*(it+3) == "" && (*(it+4) == ""))
			break;
	}
	cout << "Part 1: " << res << endl;
	return res;
}


int part_two(vector<string> in)
{
	int res= 0;
	int before[N], after[N], oper[N];
	string temp;
	string regular = ".*\\[([0-9]+), ([0-9]), ([0-9]), ([0-9])]";
	bool learning = true;
	map<int, vector<int>> opcodes;
	for (auto it=in.begin(); it!=in.end();)
	{
		if (learning)
		{
			regex rgx(regular);
			smatch matches;
			if (regex_search((*it), matches, rgx))
			{
				if (matches.size()>4)
				{
					before[0] = stoi(matches[1]);
					before[1] = stoi(matches[2]);
					before[2] = stoi(matches[3]);
					before[3] = stoi(matches[4]);
				}
			}
			
			if (regex_search(*(it+2), matches, rgx))
			{
				if (matches.size()>4)
				{
					after[0] = stoi(matches[1]);
					after[1] = stoi(matches[2]);
					after[2] = stoi(matches[3]);
					after[3] = stoi(matches[4]);
				}
			}
			stringstream tmp(*(it+1));
			int i=0;
			while (!tmp.eof())
			{
				tmp >> temp;
				oper[i] = stoi(temp);
				i++;
			}
			cout << oper[0] << " " << oper[1]<< " " << oper[2]<< " " << oper[3] << endl;

			vector<int> temp = try_all_operations(before, after, oper);
			cout << temp.size() << endl;

			//Die after first half
			if (*(it+3) == "" && (*(it+4) == ""))
				learning = false;
			it+=4;
		}else{
			cout << "End!" << endl;
			for (int i=0; i<=NumOP; i++)
			{
				for (auto iter=opcodes[i].begin();iter!=opcodes[i].end();++iter)
					cout << i << ": " << *iter << endl;
			}
			cout << endl;
			break;
		}
	}
	cout << "Part 2: " << res << endl;
	return 0;
}

int main(int argc, char** argv)
{
	string loc = "../inputs/day16.txt";
	if (argc >= 2)
		loc = argv[1];

	//vector<string> in = read_input(loc);
	//part_one(in);
	//part_two(in);
	int b[4] = {2,1,2,2};
	int a[4] = {3,1,2,2};
	int o[4] = {2,2,3,0};
	try_all_operations(b,a,o);
	return 0;
}