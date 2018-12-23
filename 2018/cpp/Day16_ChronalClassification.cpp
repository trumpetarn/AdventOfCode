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
#define N 4

using namespace std;
typedef int regid;
typedef int value;

int reg[] = {0,0,0,0};

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

int test_all(int before[N], int after[N], int oper[N])
{
	return 0;
}

int part_one(vector<string> in)
{
	int res= 0;
	for (auto it=in.begin(); it!=in.end(); ++it)
	{
		//Die after first half
		if (*it == "" && (*(it+1) == ""))
			break;

		int before[N] = {0,0,0,0};
		int oper[N] = {0,0,0,0};
		int after[N] = {0,0,0,0};
		
		
		if (test_all(before, after, oper)>=3)
			res++;
	}
	return res;
}

int main(int argc, char** argv)
{
	string loc = "../inputs/day16.txt";
	if (argc >= 2)
		loc = argv[1];

	vector<string> in = read_input(loc);
	cout << "Part 1: " << part_one(in) << endl;

	return 0;
}