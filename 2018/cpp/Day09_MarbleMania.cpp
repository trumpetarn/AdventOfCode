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

using namespace std;

int main(int argc, char** argv)
{
	if (argc < 3) {
		cout << "Two inputs needed, num_players and points" << endl;
		return -1;
	}
	int num_players = atoi(argv[1]);
	int last_marble_point = atoi(argv[2]);
	list<long> marbles = {};
	vector<int64_t> points;
	points.resize(num_players);

	int current_player=-1;

	marbles.push_back(0);
	auto it = marbles.cbegin();
	for (int current_marble=1; current_marble< last_marble_point+1; ++current_marble)
	{
		current_player = (current_player+1)% num_players;

		if ((current_marble%23)!=0)
		{
			if (++it == marbles.cend())
				it = marbles.cbegin();
			it = marbles.insert(++it, current_marble);
		} 
		else 
		{
			for (int i=0; i<7; ++i)
			{
				it--;
				if (it == marbles.cbegin())
					it = marbles.cend();
			}
			points[current_player] += current_marble + *it;
			marbles.erase(it++);
		}
	}
	int64_t max = 0;
	for (int i=0; i<num_players; i++)
	{
		if (points[i] > max)
			max = points[i];
	}
	cout << "Result: " << max << endl;
	return 0;
}