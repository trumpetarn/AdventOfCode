#ifndef intcode_h
#include <vector>

class Intcode {
public:
	//int run(std::vector<int> inputs);
	int run(int input = 1);
	void set_program(std::vector<int> n);
	int get_last_output() {return last_output;};
	void reset_program();
	bool run2input();
	bool run2output();
	int run2input_output();
	void provide_input(int in);
private:
	int get_param(int pos, int opcode);
	int tick();
	bool get_input(int &in);
	void set_input(int in);

	std::vector<int> program;
	int program_pos = 0;
	int last_output = -1;
	bool input_set = false;
	bool break_next_input = false;
	bool break_next_output = false;
	int provided_input;
};
#endif