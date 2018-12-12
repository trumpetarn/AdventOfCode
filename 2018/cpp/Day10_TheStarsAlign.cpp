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
#include <regex>

/* Needs to be compiled with -std=C++17*/
using namespace std;

struct coord_t{
	long long int x;
	long long int y;
};

bool operator== (const coord_t &c1, const coord_t &c2)
{
    return (c1.x== c2.x &&
            c1.y== c2.y);
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

tuple<vector<coord_t>,vector<coord_t>> input_to_coords(vector<string> in)
{
	vector<coord_t> coordinates;
	vector<coord_t> speed;
	regex rgx("^position=<(.*),(.*)> velocity=<(.*),(.*)>");
	smatch matches;
	int x,y;
	for (auto it=in.begin(); it!=in.end(); ++it)
	{
		regex_search(*it, matches, rgx);
		if (matches.size()==0)
			cout << "Regex failed\n";
		x = stoi(matches[1]);
		y = stoi(matches[2]);
		//cout << x << ',' << y << endl;
		coordinates.push_back({x,y});
		x = stoi(matches[3]);
		y = stoi(matches[4]);
		speed.push_back({x,y});
	}
	return make_tuple(coordinates, speed);
}

unsigned long long int get_square(vector<coord_t> in)
{
	long long int min_x=in[0].x;
	long long int min_y=in[0].y;
	long long int max_x=in[0].x;
	long long int max_y=in[0].y;
	long long int temp_x,temp_y;
	for (auto it=in.begin(); it!=in.end(); ++it)
	{
		temp_x = it->x;
		temp_y = it->y;
		if (temp_x<min_x)
			min_x = temp_x;
		else if (temp_x > max_x)
			max_x = temp_x;
		
		if (temp_y<min_y)
			min_y = temp_y;
		else if (temp_y > max_y)
			max_y = temp_y;
	}
	return abs(max_x-min_x)*abs(max_y-min_y);
}

void print_map(vector<coord_t> in)//, int min_x, int min_y, int max_x, int max_y)
{
	long long int min_x=100000;
	long long int min_y=100000;
	long long int max_x=0;
	long long int max_y=0;
	long long int temp_x,temp_y;
	for (auto it=in.begin(); it!=in.end(); ++it)
	{
		temp_x = it->x;
		temp_y = it->y;
		if (temp_x<min_x)
			min_x = temp_x;
		else if (temp_x > max_x)
			max_x = temp_x;
		
		if (temp_y<min_y)
			min_y = temp_y;
		else if (temp_y > max_y)
			max_y = temp_y;
	}
	for (long long int y=(min_y-3); y<(max_y+3); y++)
	{
		for (long long int x=(min_x-3); x<(max_x+3); x++)
		{
			coord_t temp;
			temp.x=x;
			temp.y=y;
			if(find(in.begin(), in.end(), temp)!=in.end())
				cout << "# ";
			else
				cout << ". ";
		}
		cout << endl;
	}
}

int main(int argc, char** argv)
{
	string loc = "../inputs/day10.txt";
	if (argc >= 2)
		loc = argv[1];

	vector<string> in = read_input(loc);
	auto [coord, vel] = input_to_coords(in);
	vector<coord_t> prev = coord;
	int time = 0;
	unsigned long int size = get_square(coord);
	unsigned long int prev_size = size;
	while (size<=prev_size)
	{
		prev = coord;
		for (int i=0;i<(int)coord.size();i++)
		{
			coord[i].x += vel[i].x;
			coord[i].y += vel[i].y;
		}
		prev_size = size;
		size = get_square(coord);
		time++;
		//cout << size << ',' << prev_size << endl;
	}
	print_map(prev);
	cout << "Time: " << time-1 << endl;
	return 0;
}