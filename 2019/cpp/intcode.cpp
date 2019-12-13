#include "intcode.h"
#include <iostream>

using namespace std;
/*
ABCDE
 1002

DE - two-digit opcode,      02 == opcode 2
 C - mode of 1st parameter,  0 == position mode
 B - mode of 2nd parameter,  1 == immediate mode
 A - mode of 3rd parameter,  0 == position mode,
                                  omitted due to being a leading zero
                                  */

int Intcode::get_param(int pos, int opcode) {
	int p=-1;
	switch(opcode){
		case 0:
			p= program[program[pos]];
			break;
		case 1:
			p=program[pos];
			break;
		default:
			cout << "ERROR: Invalid opcode";
	}
	return p;
}

bool Intcode::get_input(int &in){
	in = provided_input;
	return input_set;
}

int Intcode::tick(){
	int p1,p2,val;
	int opcode = program[program_pos];
	int A = (opcode/10000)%10;
	int B = (opcode/1000)%10;
	int C = (opcode/100)%10;
	int DE = (opcode)%100;
	//cout << A << B << C << ',' << DE << " " << opcode << endl;
	if (A!=0){
		cout << "A != 0";
		return -1;
	}
	switch(DE){
		case 1: //Add
			p1 = get_param(program_pos+1, C);
			p2 = get_param(program_pos+2, B);
			program[program[program_pos+3]] = p1 + p2;
			program_pos += 4;
			break;
		case 2: //Multiply
			p1 = get_param(program_pos+1, C);
			p2 = get_param(program_pos+2, B);
			program[program[program_pos+3]] = p1 * p2;
			program_pos += 4;
			break;
		case 3: //Write
			val = 0;
			if (break_next_input){
				break_next_input = false; 
				return 0;
			}else if (get_input(val) ){
				program[program[program_pos+1]] = val;
				program_pos += 2;
			}else{
				cout << "NO INPUT AVAILABLE" << endl;
				return -1;
			}
			break;
		case 4: //Print
			p1 = get_param(program_pos+1, C);
			if (p1!=0){
				last_output = p1;
			}
			program_pos += 2;
			if (break_next_output){
				break_next_output = false; 
				return 0;
			}
			break;
		case 5: //jump if true
			p1 = get_param(program_pos+1, C);
			p2 = get_param(program_pos+2, B);
			if (p1 != 0){
				program_pos = p2;
			}else{
				program_pos += 3;
			}
			break;
		case 6: //jump is false
			p1 = get_param(program_pos+1, C);
			p2 = get_param(program_pos+2, B);
			if (p1 == 0){
				program_pos = p2;
			}else{
				program_pos += 3;
			}
			break;
		case 7: //less than
			p1 = get_param(program_pos+1, C);
			p2 = get_param(program_pos+2, B);
			program[program[program_pos+3]] = (p1 < p2) ? 1 : 0;
			program_pos += 4;
			break;
		case 8: //Equals
			p1 = get_param(program_pos+1, C);
			p2 = get_param(program_pos+2, B);
			program[program[program_pos+3]] = (p1 == p2) ? 1 : 0;
			program_pos += 4;
			break;
		case 99:
			//cout << "Returns " << program[0] << endl;
			return program[0];
		default:
			cout << "ERROR!" << endl;
			return -3;
	}
	return 0;
}

bool Intcode::run2input(){
	break_next_input = true;
	int ret=0;
	while (break_next_input && ret==0){
		ret = tick();
	}
	return ret==0; //true means the program have not halted
}

bool Intcode::run2output(){
	break_next_output = true;
	int ret=0;
	while (break_next_output && ret==0){
		ret = tick();
	}
	return ret==0; //true means the program have not halted
}

int Intcode::run2input_output(){
	break_next_input = true;
	break_next_output = true;
	int res=0;
	while (break_next_input && break_next_output && res==0){
		res = tick();
	}
	int ret = 0;
	if (!break_next_output){
		ret = 1;
	}
	if (!break_next_input){
		ret = 2;
	}

	break_next_input = false;
	break_next_output = false;
	return ret; //0 = halted
}

void Intcode::provide_input(int in){
	set_input(in);
	tick();
}

int Intcode::run(int input){
	set_input(input);
	int ret = 0;
	while (ret == 0){
		ret = tick();
	}
	return ret;
}

void Intcode::set_program(std::vector<int> n){
	program = n;
}

void Intcode::set_input(int in){
	input_set = true;
	provided_input = in;
}

void Intcode::reset_program(){
	program_pos = 0;
	input_set = false;
}