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

using namespace std;

enum turn_t
{
	L,
	S,
	R
};

enum dir_t
{
	LEFT,
	DOWN,
	RIGHT,
	UP
};

struct cart_t
{
	dir_t direction;
	turn_t next_turn;
	char current_sym;
	int last_tick;
	bool has_crashed;
	bool is_dead;
	int x;
	int y;
};

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

int main(int argc, char** argv)
{
	string loc = "../inputs/day13.txt";
	if (argc >= 2)
		loc = argv[1];
	bool debug = argc > 2;
	vector<string> in = read_input(loc);
	int i = (int)in.size();
	int j = (int)in[0].size();
	char mine_map[i][j];
	int cart = 0;
	vector<cart_t> carts;
	for (int k=0; k<i; ++k)
	{
		for (int l=0; l<j; ++l)
		{
			if (in[k][l]=='v')
			{
				mine_map[k][l] = cart + 'A';
				carts.push_back({DOWN,L,'|',0,false,false,0,0});
				cart++;
			}
			else if (in[k][l]=='<')
			{
				mine_map[k][l] = cart + 'A';
				carts.push_back({LEFT,L,'-',0,false,false,0,0});
				cart++;
			}
			else if (in[k][l]=='>')
			{
				mine_map[k][l] = cart + 'A';
				carts.push_back({RIGHT,L,'-',0,false,false,0,0});
				cart++;
			}
			else if (in[k][l]=='^')
			{
				mine_map[k][l] = cart + 'A';
				carts.push_back({UP,L,'|',0,false,false,0,0});
				cart++;
			}
			else
			{
				mine_map[k][l] = in[k][l];
			}
		}
	}
	int tick = 0;
	int num_carts = (int)carts.size();
	cout << num_carts << endl;
	if (debug)
	{
		for (int k=0; k<i; ++k)
		{
			for (int l=0; l<j; ++l)
			{
				cout << mine_map[k][l];
			}
			cout << endl;
		}
	}
	while (num_carts > 1)
	{
		tick++;
		for (int k=0; k<i; ++k)
		{
			for (int l=0; l<j; ++l)
			{
				if (mine_map[k][l]>='A' && mine_map[k][l]<'A'+cart)
				{
					int index = mine_map[k][l]-'A';
					if (carts[index].last_tick<tick && !carts[index].is_dead)
					{
						if (carts[index].direction == LEFT)
						{
							char next = mine_map[k][l-1];
							if (next == '/'){
								carts[index].direction = DOWN;
							}else if (next == '\\'){
								carts[index].direction = UP;
							}else if (next == '+'){
								if (carts[index].next_turn == L)
								{
									carts[index].direction = DOWN;
									carts[index].next_turn = S;
								}else if (carts[index].next_turn == S){
									carts[index].next_turn = R;
								}else if (carts[index].next_turn == R){
									carts[index].direction = UP;
									carts[index].next_turn = L;
								}
							}else if (next != '-' && !carts[index].has_crashed){
								cout << "Crash at: " << l-1 << ',' << k << endl;
								carts[index].has_crashed=true;
								carts[next-'A'].has_crashed=true;
								mine_map[k][l] = carts[next-'A'].current_sym;
							}
							carts[index].x = l-1;
							carts[index].y = k;
							mine_map[k][l-1] = mine_map[k][l];
							mine_map[k][l] = carts[index].current_sym;
							carts[index].current_sym = next;
						}else if (carts[index].direction == RIGHT){
							char next = mine_map[k][l+1];
							if (next == '/'){
								carts[index].direction = UP;
							}else if (next == '\\'){
								carts[index].direction = DOWN;
							}else if (next == '+'){
								if (carts[index].next_turn == L)
								{
									carts[index].direction = UP;
									carts[index].next_turn = S;
								}else if (carts[index].next_turn == S){
									carts[index].next_turn = R;
								}else if (carts[index].next_turn == R){
									carts[index].direction = DOWN;
									carts[index].next_turn = L;
								}
							}else if (next != '-' && !carts[index].has_crashed){
								cout << "Crash at: " << l+1 << ',' << k << endl;
								carts[index].has_crashed=true;
								carts[next-'A'].has_crashed=true;
								mine_map[k][l] = carts[next-'A'].current_sym;
							}
							carts[index].x = l+1;
							carts[index].y = k;
							mine_map[k][l+1] = mine_map[k][l];
							mine_map[k][l] = carts[index].current_sym;
							carts[index].current_sym = next;
						}else if (carts[index].direction == UP){
							char next = mine_map[k-1][l];
							if (next == '/'){
								carts[index].direction = RIGHT;
							}else if (next == '\\'){
								carts[index].direction = LEFT;
							}else if (next == '+'){
								if (carts[index].next_turn == L)
								{
									carts[index].direction = LEFT;
									carts[index].next_turn = S;
								}else if (carts[index].next_turn == S){
									carts[index].next_turn = R;
								}else if (carts[index].next_turn == R){
									carts[index].direction = RIGHT;
									carts[index].next_turn = L;
								}
							}else if (next != '|' && !carts[index].has_crashed){
								cout << "Crash at: " << l << ',' << k-1 << endl;
								carts[index].has_crashed=true;
								carts[next-'A'].has_crashed=true;
								mine_map[k][l] = carts[next-'A'].current_sym;
							}
							carts[index].x = l;
							carts[index].y = k-1;
							mine_map[k-1][l] = mine_map[k][l];
							mine_map[k][l] = carts[index].current_sym;
							carts[index].current_sym = next;
						}else if (carts[index].direction == DOWN){
							char next = mine_map[k+1][l];
							if (next == '/'){
								carts[index].direction = LEFT;
							}else if (next == '\\'){
								carts[index].direction = RIGHT;
							}else if (next == '+'){
								if (carts[index].next_turn == L)
								{
									carts[index].direction = RIGHT;
									carts[index].next_turn = S;
								}else if (carts[index].next_turn == S){
									carts[index].next_turn = R;
								}else if (carts[index].next_turn == R){
									carts[index].direction = LEFT;
									carts[index].next_turn = L;
								}
							}else if (next != '|' && !carts[index].has_crashed){
								cout << "Crash at: " << l << ',' << k+1 << endl;
								carts[index].has_crashed=true;
								carts[next-'A'].has_crashed=true;
								mine_map[k][l] = carts[next-'A'].current_sym;
							}
							carts[index].x = l;
							carts[index].y = k+1;
							mine_map[k+1][l] = mine_map[k][l];
							mine_map[k][l] = carts[index].current_sym;
							carts[index].current_sym = next;
						}else{
							cout << "NOOOO!!!" << endl;
						}
					}else{
						//cout << mine_map[k][l];
					}
					carts[index].last_tick = tick;
				}
			}
		}
		for (auto it=carts.begin(); it!=carts.end(); ++it)
		{
			if (it->has_crashed)
			{
				//cout << "Crash: " << tick << endl;
				it->has_crashed=false;
				it->is_dead=true;
				//mine_map[it->y][it->x] = it->current_sym;
				num_carts--;
			}
		}
		if (debug)
		{
			for (int k=0; k<i; ++k)
			{
				for (int l=0; l<j; ++l)
				{
					cout << mine_map[k][l];
				}
				cout << endl;
			}
		}
	}
	for (auto it=carts.begin(); it!=carts.end(); ++it)
	{
		if (!it->has_crashed && !it->is_dead)
		{
				cout << "Task 2: " << it->x << ',' << it->y << endl;
		}
	}
	return 0;
}