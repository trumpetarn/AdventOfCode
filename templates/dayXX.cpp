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

/*
$title_comment
*/
using namespace std;
namespace day03
{
	vector<string> read_input(string loc)
	{
		vector<string> in;
		string line;
		ifstream infile(loc);
		if (infile.is_open())
		{
			while (getline(infile, line))
			{
				in.push_back(line);
			}
		}
		return in;
	}

	int main()
	{
		string loc = "$input_file";
		if (argc >= 2)
			loc = argv[1];

		vector<string> in = read_input(loc);
		return 0;
	}
}