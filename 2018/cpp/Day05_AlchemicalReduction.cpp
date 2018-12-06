#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

vector<string> read_input()
{
	vector<string> in;
	string line;
	ifstream infile ("../inputs/day05.txt");
	if (infile.is_open())
	{
		while (getline(infile,line))
		{
			in.push_back(line);
		}
	}
	return in;
}

string reduce(string str)
{
	bool change = false;
	string new_str = ""; 
	for(string::size_type i = 0; i < str.size(); ++i) 
	{
		if (!((toupper(str[i])==toupper(str[i+1])) && (str[i]!=str[i+1])))
		{
			new_str += str[i];
		}else{
			change = true;
			i++;
		}
	}
	if (change)
		new_str = reduce(new_str);
	return new_str;
}

int part_two(string str)
{
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	string str2;
	string res;
	int shortest = -1;
	for(auto it=alpha.begin(); it != alpha.end(); ++it)
	{ 
		str2 = "";
		for(string::size_type i = 0; i < str.size(); ++i) 
		{
			if (!(tolower(str[i])==(*it)))
				str2 += str[i];
		}
		res = reduce(str2);
		if ((shortest < 0) || ((int) res.size() < shortest))
		{
			cout << (*it);
			shortest = (int) res.size();
		}
	}
	return shortest;
}

int main(int, char**)
{
	vector<string> in = read_input();
	string ans = reduce(in[0]);
	cout << "Part 1: " << ans.size() << endl;
	int p2 = part_two(in[0]);
	cout << "Part 2: " << p2 << endl;
	return 0;
}