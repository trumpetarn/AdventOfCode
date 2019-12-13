#ifndef intcode_h
#include <vector>

typedef long long int llint;

class Intcode {
public:
	//int run(std::vector<int> inputs);
	llint run(int input = 1);
	void set_program(std::vector<llint> n);
	void set_program(std::vector<int> n);
	llint get_last_output() {return last_output;};
	void reset_program();
	bool run2input();
	bool run2output();
	llint run2input_output();
	void provide_input(llint in);
	int increase_memory(int mem_size);
	void turn_on_print() {print_all = true;};
private:
	llint get_param(int pos, int opcode);
	llint tick();
	bool get_input(llint &in);
	void set_input(llint in);
	void write(llint val, int pos, int opcode);

	std::vector<llint> program;
	int program_pos = 0;
	llint last_output = -1;
	bool input_set = false;
	bool break_next_input = false;
	bool break_next_output = false;
	llint provided_input;
	llint relative_base = 0;
	bool print_all = false;
};
#endif