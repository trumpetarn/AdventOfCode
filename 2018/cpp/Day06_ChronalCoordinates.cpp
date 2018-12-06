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

int main(int, char**)
{
	vector<string> in = read_input();
	string ans = reduce(in[0]);
	cout << "Part 1: " << ans.size() << endl;
	int p2 = part_two(in[0]);
	cout << "Part 2: " << p2 << endl;
	return 0;
}