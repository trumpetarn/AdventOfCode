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
#include "helper.h"

using namespace std;
using namespace helper;
namespace day10{
static int map_width;
static int map_height;

vector<Point> read_input(string loc)
{
	vector<Point> in;
	string line;
	ifstream infile (loc);
	int col,row = 0;
	if (infile.is_open())
	{
		while (getline(infile,line))
		{
			col=0;
			for (char& c : line){
				if (c == '#'){
					Point p;
					p.x = col;
					p.y = row;
					in.push_back(p);
				}
				col++;
			}
			row++;
		}
	}
	map_height = row;
	map_width = col;
	return in;
}

Point task1(vector<Point> asteroids){
	set<double> angles;
	int max = 0;
	Point best;
	for (Point p : asteroids){
		angles.clear();
		for (Point q : asteroids){
			if (p.x != q.x || p.y != q.y){
				double dx = p.x-q.x;
				double dy = p.y-q.y;
				double rad = atan2(dy, dx);	
				angles.insert(angles.end(), rad);
			}
		}
		//cout << p.x << ',' << p.y << ':' << angles.size() << endl;
		if ((int)angles.size()>max){
			max = angles.size();
			best.x = p.x;
			best.y = p.y;
			//cout << p.x << ',' << p.y << endl;
		}
	}
	cout << "Star 1: " << max << " asteroids at {" << best.x << ',' << best.y << "}" << endl;
	return best;
}

Point remove_closest(vector<Point>& points, Point p){
	int min_dist = 999999;
	int dist;
	Point closest;
	for (auto it : points){
		dist = abs(it.x-p.x) + abs(it.y-p.y);
		if (dist < min_dist){
			min_dist = dist;
			closest = it;
		}
	}
	points.erase(find(points.begin(), points.end(), closest));
	return closest;
}

void task2(vector<Point> asteroids, Point p){
	map<double,vector<Point>> points;
	set<double> angles;
	for (Point q : asteroids){
		if (p.x != q.x || p.y != q.y){
			double dx = p.x-q.x;
			double dy = p.y-q.y;
			double rad = atan2(dy, dx);	
			points[rad].push_back(q);
			angles.insert(angles.end(), rad);
		}
	}
	double start_angle = atan2(1,0);
	auto start = find(angles.begin(), angles.end(), start_angle);
	int i = 0;
	Point removed = p;
	Point q = {8,2};
	while (i<200){
		for (auto it=start;it!=angles.end();++it){
			if (points[(*it)].size() > 0){
				removed = remove_closest(points[(*it)],p);
				if (removed == q){
					cout << i << endl;
				}
				i++;
			}
			if (i==200){
				break;
			}
		}
		for (auto it=angles.begin(); it!=start; ++it){
			if (points[(*it)].size() > 0){
				removed = remove_closest(points[(*it)],p);
				if (removed == q){
					cout << i << endl;
				}
				i++;
			}
			if (i==200){
				break;
			}
		}
	}
	cout << "Star 2: " << removed.x*100 + removed.y << endl;
}

int main()
{
	string path = "../inputs/day10.txt";
	vector<Point> asteroids = read_input(path);
	cout << asteroids.size() << endl;
	Point p = task1(asteroids);
	task2(asteroids, p);
	return 0;
}
}//namespace day10