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

using namespace std;

int next_index(int index, int size)
{
	int index1 = (index+1)%size;
	int index2 = (index+2)%size;
	if (index1 < index2)
		return index2;
	//cout << index1 << ':' << index2 << ':' << size << endl;
	return index1+1;
}

int main(int argc, char** argv)
{
	if (argc < 3) {
		cout << "Two inputs needed, num_players and points" << endl;
		return -1;
	}
	bool debug = (argc >3);
	int num_players = atoi(argv[1]);
	int last_marble_point = atoi(argv[2]);
	vector<int> marbles;
	map<int,int> points;
	int latest_point=0;
	int next_marble = 0;
	int index=0;
	int current_player=0;

	marbles.push_back(0);
	int v_size = (int) marbles.size();
	vector<int>::iterator it;
	while (next_marble < last_marble_point)
	{
		v_size = (int) marbles.size();
		current_player = (current_player % num_players) + 1;
		next_marble++;

		if ((next_marble%23)!=0)
		{
			index = next_index(index,v_size);
			it = marbles.begin();
			advance(it, index);
			marbles.insert(it,next_marble);
		} 
		else 
		{
			index = (index + v_size - 7)%(v_size);
			//cout << index << ':' << marbles.at(index) << '=' << v_size << endl;
			latest_point = next_marble + marbles.at(index);
			it = marbles.begin();
			advance(it, index);
			marbles.erase(it);
			//cout << index << '/' << marbles.at(index) << endl;
			if (points.find(current_player)==points.end())
			{
				points[current_player] = 0;
			}
			points[current_player] += latest_point;
		}

		if (debug)
		{
			//cout << "Points: " << latest_point << endl;
			cout << current_player << " (" << marbles.size() << ')' << ": ";
			for (auto it=marbles.begin(); it!=marbles.end(); ++it)
				cout << *it << " ";
			cout << " [" << latest_point << "]" << endl;
			//cout << num_players << ';' << last_marble_point << endl;
		}

	}
	cout << "High Score" << endl;
	int max = 0;
	for (auto it=points.begin(); it != points.end(); ++it)
	{
		cout << it->first << ' ' << it->second << endl;
		if (it->second > max)
			max = it->second;
	}
	cout << "Task 1: " << max << endl;
	return 0;
}