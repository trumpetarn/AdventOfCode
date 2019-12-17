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

using namespace std;
using namespace helper;
namespace day11{

static constexpr int Black = 0;
static constexpr int White = 1;

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
	ic.increase_memory(1000);
	//ic.print_program();
	Direction d(Direction::Directions::UP);
	Point p = {0,0};
	int color = Black;
	map<Point,int> visited;
	int input = color;
	for (;;){
		//cout << p << endl;
		if (visited.find(p)!=visited.end()){
			input = visited[p];
		}else{
			input = Black;
		}
		ic.set_input(input);
		if(!ic.run2output())
			break;
		visited[p] = ic.get_last_output();
		if(!ic.run2output())
			break;
		if (ic.get_last_output() == 0){
			d.turn_left();
		}else{
			d.turn_right();
		}
		p = p+d.get_point_direction();
	}
	cout << "Star 1: " << visited.size() << endl;
}

void task2(vector<llint> v){
	Intcode ic;
	ic.set_program(v);
	ic.increase_memory(1000);
	//ic.print_program();
	Direction d(Direction::Directions::UP);
	Point p = {0,0};
	map<Point,int> visited;
	int input = White;
	bool first = true;
	for (;;){
		//cout << p << endl;
		if (visited.find(p)!=visited.end()){
			input = visited[p];
		}else if(first){
			first = false;
			input = White;
		}else{
			input = Black;
		}
		ic.set_input(input);
		if(!ic.run2output())
			break;
		visited[p] = ic.get_last_output();
		if(!ic.run2output())
			break;
		if (ic.get_last_output() == 0){
			d.turn_left();
		}else{
			d.turn_right();
		}
		p = p+d.get_point_direction();
	}
	vector<Point> white;
	for (auto it : visited){
		if (it.second == White){
			white.push_back(it.first);
		}
	}
	cout << "Star 2: " << endl;
	print_points(white);
}

int main()
{
	string path = "../inputs/day11.txt";
	vector<llint> in = read_input(path);
	task1(in);
	task2(in);
	return 0;
}
}//namespace day11