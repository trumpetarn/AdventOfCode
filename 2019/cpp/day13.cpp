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
namespace day13{

enum TileId{
	empty=0,
	wall=1,
	block=2,
	hpaddle=3,
	ball=4
};

struct Instruction{
	helper::Point p;
	TileId id;
};

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

vector<Instruction> task1(vector<llint> pgm){
	Intcode ic;
	ic.set_program(pgm);
	ic.increase_memory(5000);
	//ic.print_program();
	vector<Instruction> output;
	int i=0;
	int num_block = 0;
	Instruction instr;
	while (ic.run2output()){
		llint tmp = ic.get_last_output();
		switch(i%3){
			case 0:
				instr.p.x=tmp;
			break;
			case 1:
				instr.p.y=tmp;
			break;
			case 2:
				instr.id=static_cast<TileId>(tmp);
				if (instr.id == block){
					num_block++;
				}
				output.push_back(instr);
			break;
		}
		i++;
	}
	cout << "Star 1: " << num_block << endl;
	return output;
}

vector<Instruction> task2(vector<llint> pgm){
	Intcode ic;
	pgm[0]=2;
	ic.set_program(pgm);
	ic.increase_memory(5000);
	//ic.print_program();
	vector<Instruction> output;
	int i=0;
	const helper::Point point = {-1, 0};
	int score = -1;
	Instruction instr;
	llint joystick = 0;
	helper::Point ball_pos;
	helper::Point paddle_pos;
	while (ic.run2output()){
		ic.set_input(joystick);
		llint tmp = ic.get_last_output();
		switch(i%3){
			case 0:
				instr.p.x=tmp;
			break;
			case 1:
				instr.p.y=tmp;
			break;
			case 2:
				if (instr.p == point){
					score = tmp;
					cout << score << endl;
				}else{
					instr.id=static_cast<TileId>(tmp);
					output.push_back(instr);
				}
				if (instr.id == ball){
					ball_pos = instr.p;
				}else if (instr.id == hpaddle){
					paddle_pos = instr.p;
				}
			break;
		}
		i++;
		/*if (ball_pos.x < paddle_pos.x){
			joystick = -1;
		}else if(ball_pos.x > paddle_pos.x) {
			joystick = 1;
		}else{*/
			joystick = 0;
		//}
	}
	cout << "Star 2: " << score << endl;
	return output;
}

int main()
{
	string path = "../inputs/day13.txt";
	vector<llint> in = read_input(path);
	task1(in);
	task2(in);
	return 0;
}
}//namespace day13