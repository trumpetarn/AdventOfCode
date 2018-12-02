#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool recurring_letter(string str, int r)
{
	for (string::size_type i = 0; i < str.length(); i++)
	{
	    if (count(str.begin(), str.end(), str[i]) == r)
	    	return true;
	}
	return false;
}


vector<string> part_one(){
	vector<string> input;
	string line;
	int doubles=0, triples=0;
	ifstream infile ("../inputs/day02.txt");
	if (infile.is_open())
	{
		while (getline(infile,line))
		{
			if (recurring_letter(line,2))
				doubles++;
			if (recurring_letter(line,3))
				triples++;
			input.push_back(line);
		}
	}
	cout << "Part 1: Checksum: " << doubles * triples << "\n";
	return input;
}

int part_two(vector<string> input)
{
	for (auto it=input.begin(); it != input.end(); it++)
	{
		
	}
	return 0;
}

int main(int, char**)
{
	vector<string> in = part_one();
	part_two(in);
	return 0;
}