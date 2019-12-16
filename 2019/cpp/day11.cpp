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
#include <math.h>
#include "intcode.h"
#include "helper.h"

typedef long long int llint;

using namespace std;
namespace day11{

enum Direction{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

Direction turn_left(Direction d){
	Direction n;
	switch (d){
		case UP:
			n =LEFT;
			break;
		case RIGHT:
			n = UP;
			break;
		case DOWN:
			n = RIGHT;
			break;
		case LEFT:
			n = DOWN;
			break;
	}
	return n;
}

Direction turn_right(Direction d){
	Direction n;
	switch (d){
		case UP:
			n = RIGHT;
			break;
		case RIGHT:
			n = DOWN;
			break;
		case DOWN:
			n =LEFT;
			break;
		case LEFT:
			n = UP;
			break;
	}
	return n;
}

Point move(Point pos, Direction dir){
	cout << dir;
	switch (dir){
		case UP:
			pos.y += 1;
			break;
		case RIGHT:
			pos.x += 1;
			break;
		case DOWN:
			pos.y -= 1;
			break;
		case LEFT:
			pos.x -= 1;
			break;
	}
	cout << pos << endl;
	return pos;
}

vector<llint> read_input(string loc)
{
	vector<llint> in;
	string line;
	ifstream infile (loc);
	if (infile.is_open())
	{
		while (getline(infile,line,','))
		{
			in.push_back(stoll(line));
		}
	}
	return in;
}

void task1(vector<llint> v){
	Intcode ic;
	ic.set_program(v);
	ic.increase_memory(10000);
	map<Point,int> visited;
	Point pos = {0,0};
	Direction dir = UP;
	int out1,out2;
	int color = 0;
	bool ret = true;
	while(ret){
		ic.provide_input(color);
		ret = ic.run2output();
		if (!ret){
			cout << "first" << endl;
			break;
		}
		out1 = ic.get_last_output();
		visited[pos] = out1;


		ret = ic.run2output();
		if (!ret){
			cout << "second" << endl;
			break;
		}
		out2 = ic.get_last_output();
		cout << out2 << endl;


		switch (out2){
			case 0:
				cout << "left" << endl;
				dir = turn_left(dir);
				break;
			case 1:
				cout << "right" << endl;
				dir = turn_right(dir);
				break;
		}
		pos = move(pos, dir);


		if (visited.find(pos) != visited.end()){
			color = visited[pos];
		}else{
			color = 0;
		}
	}

	cout << "Star 1: " << visited.size() << endl;
}

int main()
{
	string path = "../inputs/day11.txt";
	vector<llint> in = read_input(path);
	task1(in);
	return 0;
}
}//namespace day11