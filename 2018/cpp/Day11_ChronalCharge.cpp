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

struct coord_t
{
	int x;
	int y;
};

int power_level(int x, int y, int serial)
{
	int rack_id = x+10;
	int power_level = rack_id*y+serial;
	power_level *= rack_id;
	power_level = (power_level/100) % 10;
	power_level -= 5;
	return power_level;
}

void task_one(int power_levels[300][300])
{
	coord_t maximum;
	maximum.x = 0;
	maximum.y = 0;
	int max=0,pl;
	for (int x=0; x<298; x++)
	{
		for (int y=0; y<298; y++)
		{
			pl = power_levels[x][y];
			pl += power_levels[x][y+1];
			pl += power_levels[x][y+2];
			pl += power_levels[x+1][y];
			pl += power_levels[x+1][y+1];
			pl += power_levels[x+1][y+2];
			pl += power_levels[x+2][y];
			pl += power_levels[x+2][y+1];
			pl += power_levels[x+2][y+2];
			if (pl>max)
			{
				max = pl;
				maximum.x=x+1;
				maximum.y=y+1;
			}
		}
	}
	cout << "Task 1: " << maximum.x << ',' << maximum.y << endl;
}

void task_two(int power_levels[300][300])
{
	coord_t maximum;
	maximum.x = 0;
	maximum.y = 0;
	int max=0,pl,max_size;
	for (int size=1; size<=300; size++)
	{
		for (int x=0; x<301-size; x++)
		{
			for (int y=0; y<301-size; y++)
			{
				pl = 0;
				for (int i=0; i<(size); i++)
				{
					for (int j=0; j<(size);j++)
					{
						pl += power_levels[x+i][y+j];
					}
				}
				if (pl>max)
				{
					max = pl;
					maximum.x=x+1;
					maximum.y=y+1;
					max_size = size;
				}
			}
		}
	}
	cout << "Task 2: " << maximum.x << ',' << maximum.y << ',' << max_size << endl;
}

int main(int argc, char** argv)
{
	int serial = 8141;
	/*
	cout << power_level(122,79,57) << endl; // pl -5
	cout << power_level(217,196,39) << endl;// pl 0
	cout << power_level(101,153,71) << endl;// pl 4
	*/
	int power_levels[300][300] = { {0} };
	for (int x=1; x<=300; x++)
	{
		for (int y=1; y<=300; y++)
		{
			power_levels[x-1][y-1] = power_level(x,y,serial);
		}
	}
	
	task_one(power_levels);
	task_two(power_levels);

	return 0;
}