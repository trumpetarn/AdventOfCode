#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

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
	string str, rx;
	int diff=0;
	//TODO: Something less bruteforce should be possible
	for (auto it=input.begin(); it != input.end(); it++)
	{
		for (auto iter=input.begin(); iter != input.end(); iter++)
		{
			diff = 0;
			for (string::size_type i=0; i<it->length(); i++)
			{
				if ((*iter)[i]!=(*it)[i])
					diff++;
				if (diff>1)
					break;
			}
			if (diff==1)
			{
				cout << "Part 2: ";
				for (string::size_type i=0; i<it->length(); i++)
				{	
					if ((*iter)[i]==(*it)[i])
						cout << (*iter)[i];
				}
				cout << '\n';
				break;
			}
		}
		if (diff==1)
			break;
	}
	return 0;
}

int main(int, char**)
{
	vector<string> in = part_one();
	part_two(in);
	return 0;
}