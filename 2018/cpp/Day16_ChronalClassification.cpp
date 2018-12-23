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
	for (int i=0; i<N; i++)
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

int test_all_operations(int before[N], int after[N], int operation[N])
{
	int no_op=0;
	set_reg(before);
	addr(operation[1],operation[2],operation[3]);
	if (is_equal(reg,after))
		no_op++;

	set_reg(before);
	addi(operation[1],operation[2],operation[3]);
	if (is_equal(reg,after))
		no_op++;

	set_reg(before);
	mulr(operation[1],operation[2],operation[3]);
	if (is_equal(reg,after))
		no_op++;

	set_reg(before);
	muli(operation[1],operation[2],operation[3]);
	if (is_equal(reg,after))
		no_op++;
	
	set_reg(before);
	banr(operation[1],operation[2],operation[3]);
	if (is_equal(reg,after))
		no_op++;

	set_reg(before);
	bani(operation[1],operation[2],operation[3]);
	if (is_equal(reg,after))
		no_op++;

	set_reg(before);
	borr(operation[1],operation[2],operation[3]);
	if (is_equal(reg,after))
		no_op++;

	set_reg(before);
	bori(operation[1],operation[2],operation[3]);
	if (is_equal(reg,after))
		no_op++;

	set_reg(before);
	setr(operation[1],operation[3]);
	if (is_equal(reg,after))
		no_op++;

	set_reg(before);
	seti(operation[1],operation[3]);
	if (is_equal(reg,after))
		no_op++;

	set_reg(before);
	gtri(operation[1],operation[2],operation[3]);
	if (is_equal(reg,after))
		no_op++;

	set_reg(before);
	gtir(operation[1],operation[2],operation[3]);
	if (is_equal(reg,after))
		no_op++;

	set_reg(before);
	gtrr(operation[1],operation[2],operation[3]);
	if (is_equal(reg,after))
		no_op++;

	set_reg(before);
	eqri(operation[1],operation[2],operation[3]);
	if (is_equal(reg,after))
		no_op++;

	set_reg(before);
	eqir(operation[1],operation[2],operation[3]);
	if (is_equal(reg,after))
		no_op++;

	set_reg(before);
	eqrr(operation[1],operation[2],operation[3]);
	if (is_equal(reg,after))
		no_op++;
	return no_op;
}

int part_one_and_two(vector<string> in)
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
		
		if (test_all_operations(before, after, oper)>=3)
			res++;

		//Die after first half
		if (*(it+3) == "" && (*(it+4) == ""))
			break;
	}
	cout << "Part 1: " << res << endl;
	return res;
}

int main(int argc, char** argv)
{
	string loc = "../inputs/day16.txt";
	if (argc >= 2)
		loc = argv[1];

	vector<string> in = read_input(loc);
	part_one_and_two(in);

	return 0;
}