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

llint Intcode::get_param(int pos, int opcode) {
	llint p=-1;
	switch(opcode){
		case 0:
			p= program[program[pos]];
			break;
		case 1:
			p=program[pos];
			break;
		case 2: //Relative mode
			p=program[relative_base + program[pos]];
			break;
		default:
			cout << "ERROR: Invalid opcode: " << opcode << endl;
	}
	return p;
}

bool Intcode::get_input(llint &in){
	in = provided_input;
	return input_set;
}

void Intcode::write(llint val, int pos, int opcode){
	switch (opcode){
		case 0:
			program[program[pos]] = val;
			break;
		case 2:
			program[relative_base + program[pos]] = val;
			break;
		default:
			cout << "ERROR: Invalid opcode: " << opcode << endl;
	}
}

llint Intcode::tick(){
	llint p1,p2,val;
	llint opcode = program[program_pos];
	llint A = (opcode/10000)%10;
	llint B = (opcode/1000)%10;
	llint C = (opcode/100)%10;
	llint DE = (opcode)%100;
	if (A==1){
		cout << program_pos << ": " << A << B << C << ',' << DE << " " << opcode << endl;
		return -1;
	}
	switch(DE){
		case 1: //Add
			p1 = get_param(program_pos+1, C);
			p2 = get_param(program_pos+2, B);
			write(p1+p2,program_pos+3, A);
			program_pos += 4;
			break;
		case 2: //Multiply
			p1 = get_param(program_pos+1, C);
			p2 = get_param(program_pos+2, B);
			write(p1*p2,program_pos+3, A);
			program_pos += 4;
			break;
		case 3: //Write
			if (break_next_input){
				break_next_input = false; 
				return 0;
			}else{
				if (get_input(val)){
					write(val,program_pos+1, C);
				}else{
					cout << "ERROR: NO INPUT AVAILABLE" << endl;
					return -1;
				}
				program_pos += 2;
			}
			break;
		case 4: //Print
			p1 = get_param(program_pos+1, C);
			if (print_all==true){
				cout << p1 << endl;
			}
			last_output = p1;
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
		case 6: //jump if false
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
			write(((p1 < p2) ? 1 : 0),program_pos+3, A);
			program_pos += 4;
			break;
		case 8: //Equals
			p1 = get_param(program_pos+1, C);
			p2 = get_param(program_pos+2, B);
			write(((p1 == p2) ? 1 : 0),program_pos+3, A);
			program_pos += 4;
			break;
		case 9:
			relative_base += get_param(program_pos+1, C);;
			program_pos += 2;
			break;
		case 99:
			//cout << "Returns " << program[0] << endl;
			return program[0];
		default:
			cout << "ERROR! Unknown code (" << DE << ")" << endl;
			return -3;
	}
	return 0;
}

bool Intcode::run2input(){
	break_next_input = true;
	llint ret=0;
	while (break_next_input && ret==0){
		ret = tick();
	}
	return ret==0; //true means the program have not halted
}

bool Intcode::run2output(){
	break_next_output = true;
	llint ret=0;
	while (break_next_output && ret==0){
		ret = tick();
	}
	return ret==0; //true means the program have not halted
}

llint Intcode::run2input_output(){
	break_next_input = true;
	break_next_output = true;
	llint res=0;
	while (break_next_input && break_next_output && res==0){
		res = tick();
	}
	llint ret = 0;
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

void Intcode::provide_input(llint in){
	set_input(in);
	tick();
}

llint Intcode::run(int input){
	set_input(input);
	llint ret = 0;
	while (ret == 0){
		ret = tick();
	}
	return ret;
}

void Intcode::set_program(std::vector<llint> n){
	program = n;
}

void Intcode::set_program(std::vector<int> n){
	vector<llint> m;
	for (int i : n){
		m.push_back((llint) i);
	}
	set_program(m);
}

void Intcode::set_input(llint in){
	input_set = true;
	provided_input = in;
}

void Intcode::reset_program(){
	program_pos = 0;
	input_set = false;
}

int Intcode::increase_memory(int mem_size){
	int current_size = (int)program.size();
	while (mem_size>current_size){
		program.push_back(0);
		current_size++;
	}
	return mem_size-current_size;
}

void Intcode::print_program(){
	for (auto i : program){
		cout << i << ',';
	}
	cout << endl;
}