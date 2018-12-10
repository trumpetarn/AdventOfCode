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

using namespace std;
bool debug = true;

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
	int num_players = atoi(argv[1]);
	int last_marble_point = atoi(argv[2]);
	vector<int> marbles;
	marbles.push_back(0);
	map<int,int> points;
	int latest_point=0;
	int next_marble = 0;
	int index=0;
	int current_player=0;
	vector<int>::iterator it = marbles.end();
	while (latest_point < last_marble_point)
	{
		current_player = current_player % num_players + 1;
		next_marble++;
		if ((next_marble%23)!=0)
		{
			index = next_index(index,(int) marbles.size());
			it = marbles.begin() + index;
			if (it>marbles.end())
				cout << "WTF!\n";
			marbles.insert(it,next_marble);
		} 
		else 
		{
			index = (index - 7)%(int) marbles.size();
			it = marbles.begin() + index;
			latest_point = next_marble + marbles[index];
			marbles.erase(it);
			if (points.find(current_player)==points.end())
				points[current_player] = 0;
			points[current_player] += latest_point;
		}

		if (debug)
		{
			cout << current_player << " (" << marbles.size() << ')' << ": ";
			for (auto it=marbles.begin(); it!=marbles.end(); ++it)
				cout << *it << " ";
			cout << " [" << latest_point << "]" << endl;
			cout << num_players << ';' << last_marble_point << endl;
		}
	}
	cout << "Task 1: " << points[current_player] << endl;
	return 0;
}