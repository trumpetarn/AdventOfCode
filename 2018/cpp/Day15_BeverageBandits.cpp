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

#define MAX_SIZE 100 

bool debug = false;

enum race_t
{
	goblin,
	elf
};

struct coord_t
{
	int x;
	int y;
	bool operator <(const coord_t& rhs) const{
		if (y == rhs.y)
			return x < rhs.x;
		else
			return y < rhs.y;
	}
	bool operator >(const coord_t& rhs) const{
		if (y == rhs.y)
			return x > rhs.x;
		else
			return y > rhs.y;
	}
	bool operator ==(const coord_t& rhs) const{
		return (x==rhs.x) && (y==rhs.y);
	}
};

struct path_t
{
	coord_t pos;
	list<coord_t> path;
	int dist;
};

struct unit_t
{
	int id;
	coord_t pos;
	race_t race;
	int health;
	int attack_power;
	bool operator <(const unit_t& rhs) const{
		return pos < rhs.pos;
	}
	bool operator >(const unit_t& rhs) const{
		return pos > rhs.pos;
	}
};


void print_maze (char maze[MAX_SIZE][MAX_SIZE], int width, int height)
{
	for (int y=0; y<height; y++)
	{
		for (int x=0; x<width; x++)
		{
			cout << maze[y][x];
		}
		cout << endl;
	}
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

list<coord_t> BFS(char maze[MAX_SIZE][MAX_SIZE], coord_t start, coord_t end)
{
	list<path_t> queue;
	list<coord_t> adj;
	list<coord_t> p;
	list<coord_t> shortest;
	char visited[MAX_SIZE][MAX_SIZE];
	if (start == coord_t{end.x, end.y-1} || start == coord_t{end.x-1, end.y}
		|| start == coord_t{end.x+1, end.y} || start == coord_t{end.x, end.y+1})
	{
		p.push_back(start);
		return p;
	}

	if (maze[end.y-1][end.x] == '.')
		adj.push_back({end.x, end.y-1});
	if (maze[end.y][end.x-1] == '.')
		adj.push_back({end.x-1, end.y});
	if (maze[end.y][end.x+1] == '.')
		adj.push_back({end.x+1, end.y});
	if (maze[end.y+1][end.x] == '.')
		adj.push_back({end.x, end.y+1});

	//sort(adj.begin(),adj.end());
	bool first = true;
	for (auto it=adj.begin(); it!=adj.end(); ++it)
	{
		path_t q;
		copy(&maze[0][0],&maze[0][0]+MAX_SIZE*MAX_SIZE,&visited[0][0]);
		visited[start.y][start.x] = 'S';
		queue.clear();
		p.clear();
		queue.push_back({start, p,0});
		while (!queue.empty())
		{
			q = queue.front();
			queue.pop_front();
			if (q.pos == (*it))
			{
				q.path.push_back((*it));
				if (first || q.path.size() < shortest.size())
				{
					if (debug && !first)
						cout << shortest.size() << '>' << q.path.size() << endl;
					first=false;
					shortest = q.path;
				}
				break;
			}
			if (visited[q.pos.y-1][q.pos.x] == '.')
			{
				visited[q.pos.y-1][q.pos.x] = 'v';
				path_t next = q;
				next.path.push_back(q.pos);
				next.pos.y = next.pos.y-1;
				next.dist=next.dist+1;
				queue.push_back(next);
				//accessible.push_back({q.pos.x,q.pos.y-1});
			}
			if (visited[q.pos.y][q.pos.x-1] == '.')
			{
				visited[q.pos.y][q.pos.x-1] = 'v';
				path_t next = q;
				next.path.push_back(q.pos);
				next.pos.x = next.pos.x-1;
				next.dist=next.dist+1;
				queue.push_back(next);
				//accessible.push_back({q.pos.x-1,q.pos.y});
			}
			if (visited[q.pos.y][q.pos.x+1] == '.')
			{
				visited[q.pos.y][q.pos.x+1] = 'v';
				path_t next = q;
				next.path.push_back(q.pos);
				next.pos.x = next.pos.x+1;
				next.dist=next.dist+1;
				queue.push_back(next);
				//accessible.push_back({q.pos.x+1,q.pos.y});
			}
			if (visited[q.pos.y+1][q.pos.x] == '.')
			{
				visited[q.pos.y+1][q.pos.x] = 'v';
				path_t next = q;
				next.path.push_back(q.pos);
				next.pos.y = next.pos.y+1;
				next.dist=next.dist+1;
				queue.push_back(next);
				//accessible.push_back({q.x,q.y+1});
			}
		}
	}
	return shortest;
}

int combat_sim(vector<string> in, int elf_attack_power){
	int y = (int)in.size();
	int x = (int)in[0].size();
	char cavern_map[MAX_SIZE][MAX_SIZE];
	int num_elfs=0;
	int num_goblins=0;
	//char next_iter[y][x] = cavern_map;
	vector<unit_t> units;
	int id = 0;
	for (int i=0; i<y; i++)
	{
		for (int j=0; j<x; j++)	
		{
			char next = in[i][j];
			if (next == 'G')
			{
				num_goblins++;
				//create goblin
				unit_t g;//create goblin
				g.id = id++;
				g.pos.x = j;
				g.pos.y = i;
				g.race = goblin;
				g.health = 200;
				g.attack_power = 3;
				units.push_back(g);
				next = 'G';
			}
			else if (next == 'E')
			{
				num_elfs++;
				//create elf
				unit_t e;//create goblin
				e.id = id++;
				e.pos.x = j;
				e.pos.y = i;
				e.race = elf;
				e.health = 200;
				e.attack_power = elf_attack_power;
				units.push_back(e);
				next = 'E';
			}
			cavern_map[i][j] = next;
		}
	}
	int round = 0;
	print_maze(cavern_map, x, y);
	int start_num_elf = num_elfs;
	bool full_round = true;
	while(num_elfs>0 && num_goblins>0)
	{
		round++;
		sort(units.begin(), units.end());
		for (auto it=units.begin(); it!=units.end(); ++it)
		{
			//cout << it->pos.x <<','<<it->pos.y << endl;
			list<coord_t> shortest;
			list<coord_t> temp;
			list<unit_t*> shortest_it;
			int closest = MAX_SIZE*MAX_SIZE;
			if (it->health>0)
			{
				for (auto it2=units.begin(); it2!=units.end(); ++it2)
				{
					// find all possible targets	
					if (it->id != it2->id && it->race != it2->race && it2->health>0)
					{
						cavern_map[it2->pos.y][it2->pos.x] = '.';
						temp= BFS(cavern_map, it->pos, it2->pos);
						if (it2->race == elf)
							cavern_map[it2->pos.y][it2->pos.x] = 'E';
						else
							cavern_map[it2->pos.y][it2->pos.x] = 'G';
						//cout << it->id<< "->"<< it2->id << ": " <<temp.size()<<endl;
						if (temp.size()>0 && (int)temp.size()<closest)
						{
							shortest_it.clear();
							closest = temp.size();
							shortest = temp;
							shortest_it.push_back(&(*it2));
						}else if ((int)temp.size()==closest){
							if ((*(--temp.end()))<(*(--shortest.end())))
								shortest = temp;
							shortest_it.push_back(&(*it2));
						}
						if (shortest.size()!=0 && debug)
						{
							cout << it->pos.x << ':' << it->pos.y << endl;
							for (auto it3=shortest.begin();it3!=shortest.end(); ++it3)
								cout << it3->x << ',' << it3->y << endl;
							cout << endl;
						}
						//find shortest way between M and E
						//store 
					}
				}
				//move if not any target in range 
				if (shortest.size()>0)
				{
					//cout << ":" << shortest.size() << endl;
					shortest.pop_front(); //first is starting point
					if (shortest.size()>0)
					{
						cavern_map[it->pos.y][it->pos.x] = '.';
						coord_t pos = shortest.front();
						it->pos = pos;
						if (it->race == elf)
							cavern_map[it->pos.y][it->pos.x] = 'E';
						else
							cavern_map[it->pos.y][it->pos.x] = 'G';
						shortest.pop_front();
					}
					if (shortest.size()==0)
					{
						int lowest_health = 201;
						unit_t *to_be_attacked;
						for (auto enemy=shortest_it.begin(); enemy!=shortest_it.end(); ++enemy)
						{
							if ((*enemy)->health < lowest_health)
							{
								lowest_health = (*enemy)->health;
								to_be_attacked = (*enemy);
							}else if ((*enemy)->health == lowest_health){
								if ((*enemy)->pos < to_be_attacked->pos)
									to_be_attacked = (*enemy);
							}
						}
						if (debug)
							cout << it->id << " attacks " << to_be_attacked->id << endl;
						to_be_attacked->health -= it->attack_power;
						if (to_be_attacked->health <= 0)
						{
							cavern_map[to_be_attacked->pos.y][to_be_attacked->pos.x] = '.';
							int n1=0;
							int n2=0;
							for (auto unit=units.begin(); unit!=units.end(); ++unit)
							{
								if (unit->health>0)
								{
									if (unit->race == elf)
										n1++;
									else
										n2++;
								}
							}
							if (n1*n2==0)
							{
								full_round = ((++it)==units.end());
								break;
							}
						}
					}
				}
				// if in range attack
			}
		}
		num_elfs = 0;
		num_goblins = 0;
		sort(units.begin(), units.end());
		if (debug)
		{
			cout << "Round: " << round << endl;
			print_maze(cavern_map, x, y);
		}
		for (auto unit=units.begin(); unit!=units.end(); ++unit)
		{
			if (debug)
			{
				cout << unit->id <<" (" << unit->pos.x << ',' << unit->pos.y <<") :"<< unit->health<<endl;
			}
			if (unit->health>0)
			{
				if (unit->race == elf)
					num_elfs++;
				else
					num_goblins++;
			}
		}
	}
	if (!full_round)
		round--;
	int health =0;
	for (auto unit=units.begin(); unit!=units.end(); ++unit)
	{
		if (unit->health>0)
		{
			health+= unit->health;
		}
	}
	cout << "Attack Power: " << elf_attack_power << endl;
	cout << "num_goblins" << num_goblins << endl;
	cout << "num_elfs" << num_elfs << endl;
	cout << "Outcome: " << round << '*' << health << '=' << health*round << endl;
	return start_num_elf - num_elfs;
}

int main(int argc, char** argv)
{
	string loc = "../inputs/day15.txt";
	if (argc >= 2)
	{
		loc = argv[1];
		if (argc >2)
			debug = true;
	}
	vector<string> in = read_input(loc);
	int losses = combat_sim(in, 19);
	int str = 4;
	//while (losses!=0)
	{
		//losses = combat_sim(in, ++str);
	}
	return 0;
}