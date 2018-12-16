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
	char visited[MAX_SIZE][MAX_SIZE];
	copy(&maze[0][0],&maze[0][0]+MAX_SIZE*MAX_SIZE,&visited[0][0]);
	visited[start.y][start.x] = 'S';
	list<coord_t> p;
	queue.push_back({start, p,0});

	path_t q;

	while (!queue.empty())
	{
		q = queue.front();
		queue.pop_front();
		if (q.pos == end)
		{
			list<coord_t> path;
			/*path_t *trace = q.prev;
			while (trace != nullptr)
			{
				//path.push_back(trace->pos);
				//cout << "D:" << trace->dist << endl;
				trace = trace->prev;
			}*/
			//cout << q.dist << ':' << q.path.size() << endl;
			return q.path;
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
	return p;
}

int main(int argc, char** argv)
{
	string loc = "../inputs/day15.txt";
	if (argc >= 2)
		loc = argv[1];
	vector<string> in = read_input(loc);
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
				cavern_map[i][j] = '.';
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
				cavern_map[i][j] = '.';
				//create elf
				unit_t e;//create goblin
				e.id = id++;
				e.pos.x = j;
				e.pos.y = i;
				e.race = elf;
				e.health = 200;
				e.attack_power = 3;
				units.push_back(e);
				next = 'E';
			}
			cavern_map[i][j] = next;
		}
	}
	int round = 0;
	print_maze(cavern_map, x, y);
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
							//cout << "SHORT" << endl;
							shortest_it.clear();
							closest = temp.size();
							shortest = temp;
							shortest_it.push_back(&(*it2));
							//if (shortest.size()==1)
								//break;
							/*{
								attacked=true;
								it2->health -= it->attack_power;
								if (it2->health <= 0)
								{
									cavern_map[it2->pos.y][it2->pos.x] = '.';
								}
								break;
							}*/
						}else if ((int)temp.size()==closest){
							shortest_it.push_back(&(*it2));
						}
						/*if (shortest.size()!=0)
						{
							cout << it->pos.x << ':' << it->pos.y << endl;
							for (auto it3=shortest.begin();it3!=shortest.end(); ++it3)
								cout << it3->x << ',' << it3->y << endl;
							cout << endl;
						}*/
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
						cout << it->id << " attacks " << to_be_attacked->id << endl;
						to_be_attacked->health -= it->attack_power;
						if (to_be_attacked->health <= 0)
							cavern_map[to_be_attacked->pos.y][to_be_attacked->pos.x] = '.';
					}
				}
				// if in range attack
			}
		}
		num_elfs = 0;
		num_goblins = 0;
		cout << "Round: " << round << endl;
		//print_maze(cavern_map, x, y);
		for (auto unit=units.begin(); unit!=units.end(); ++unit)
		{
			cout << unit->id <<" (" << unit->pos.x << ',' << unit->pos.y <<") :"<< unit->health<<endl;
			if (unit->health>0)
			{
				if (unit->race == elf)
					num_elfs++;
				else
					num_goblins++;
			}
		}
	}
	int health =0;
	for (auto unit=units.begin(); unit!=units.end(); ++unit)
	{
		if (unit->health>0)
		{
			health+= unit->health;
		}
	}
	cout << "Outcome: " << health << '*' << round << '=' << health*round << endl;
	return 0;
}