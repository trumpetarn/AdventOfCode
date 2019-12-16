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

const static int black = 0;
const static int white = 1;

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
	int color = black;
	map<Point,int> visited;
	int input = color;
	for (;;){
		//cout << p << endl;
		if (visited.find(p)!=visited.end()){
			input = visited[p];
		}else{
			input = black;
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

int main()
{
	string path = "../inputs/day11.txt";
	vector<llint> in = read_input(path);
	task1(in);
	return 0;
}
}//namespace day11