#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

#define SIZE 10000
using namespace std;

struct coord_t
{
	int x;
	int y;
	bool operator <(const coord_t& rhs) const{
		return (x+y) < (rhs.x + rhs.y);
	}
};

int manhattan_distance(coord_t p, coord_t q)
{
	return abs(p.x-q.x)+abs(p.y-q.y);
}

vector<string> read_input()
{
	vector<string> in;
	string line;
	ifstream infile ("../inputs/day06.txt");
	if (infile.is_open())
	{
		while (getline(infile,line))
		{
			in.push_back(line);
		}
	}
	return in;
}

vector<coord_t> string_2_coord(vector<string> in)
{
	vector<coord_t>	out;
	int temp_x;
	int temp_y;
	for (auto it = in.begin(); it != in.end(); ++it)
	{
		stringstream ss(*it);
		ss >> temp_x;
		ss.ignore();
		ss >> temp_y;
		out.push_back({temp_x,temp_y});
	}
	return out;
}

void part_one_and_two(vector<coord_t> cv)
{
	int max_x = cv[0].x;
	int max_y = cv[0].y;
	int min_x = cv[0].x;
	int min_y = cv[0].y;
	for (int i = 1; i < (int) cv.size(); ++i)
	{
		if (cv[i].x > max_x)
			max_x = cv[i].x;
		if (cv[i].y > max_y)
			max_y = cv[i].y;
		if (cv[i].x < min_x)
			min_x = cv[i].x;
		if (cv[i].y < min_y)
			min_y = cv[i].y;
	}
	map<coord_t,int> closest;
	int smallest, temp;
	int count[cv.size()];
	int sum_region;
	set<int> infinite;
	vector<coord_t> region;
	for (int j=0; j<(int) cv.size(); j++)
	{
		count[j] = 0;
	}
	for (int x=min_x-5; x < max_x+5; ++x)
	{
		for (int y = min_y-5; y < max_y+5; ++y)
		{
			smallest = manhattan_distance({x,y},cv[0]);
			sum_region = smallest;
			closest[{x,y}] = 0;
			for (int i = 1; i < (int) cv.size(); ++i)
			{
				temp = manhattan_distance({x,y},cv[i]);
				sum_region += temp;
				if (temp < smallest)
				{
					closest[{x,y}] = i;
					smallest = temp;
				}else if (temp == smallest) {
					closest[{x,y}] = -1;
				}
			}
			if (x<=min_x||x>=max_x||y<=min_y||y>=max_y)
			{
				infinite.emplace(closest[{x,y}]);
			}
			if (sum_region < SIZE)
			{
				region.push_back({x,y});
			}
			count[closest[{x,y}]]++;
		}
	}
	int max = 0;
	for (int j=0; j<(int) cv.size(); j++)
	{
		if (count[j] >= max && (find(infinite.begin(),infinite.end(),j) == infinite.end()))
		{
			max = count[j] ;
		}
	}
	cout << "Part 1: " << max << endl;
	cout << "Part 2: " << region.size() << endl;
	cout << "Area: " << max_x*max_y << endl;
}

int main(int, char**)
{
	vector<string> in = read_input();
	vector<coord_t> coords = string_2_coord(in);
	part_one_and_two(coords);
	return 0;
}