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

namespace day03{

struct point {
	int x;
	int y;
};
bool operator==(const point& p1, const point& p2) {
	return (p1.x==p2.x && p1.y == p2.y);
}
bool operator!=(const point& p1, const point& p2) {
	return !(p1==p2);
}
point operator+(const point& p1, const point& p2) {
	point p3 = {p1.x+p2.x, p1.y+p2.y};
	return p3;
}
point operator-(const point& p1, const point& p2) {
	point p3 = {p1.x-p2.x, p1.y-p2.y};
	return p3;
}

typedef vector<point> line;

enum Direction {
	up,
	down,
	left,
	right
};

point calc_endpoint(point start, Direction d, int len) {
	point end = start;
	switch (d) {
		case up:
			end.y += len;
			break;
		case down:
			end.y -= len;
			break;
		case left:
			end.x -= len;
			break;
		case right:
			end.x += len;
			break;
	}
	return end;
}

point next(point p, Direction d) {
	switch (d){
		case down:
			p.y -= 1;
			break;
		case up:
			p.y += 1;
			break;
		case left:
			p.x -= 1;
			break;
		case right:
			p.x += 1;
			break;
	}
	return p;
}

line input2line(Direction d, int len, point start){
	line l;
	point p = start;
	for (int i=0; i<len+1; ++i){
		l.push_back(p);
		p = next(p,d);
	}
	return l;
}

vector<vector<line>> read_input(string loc)
{
	vector<vector<line>> in;
	string ln;
	ifstream infile (loc);
	if (infile.is_open())
	{
		while (getline(infile,ln))
		{	
			vector<line> cable;
			point start = {0,0};
			line l;
			string str = "";
			Direction d = up;
			for (char c : ln) {
				if (c == ',') {
					// cout<< str << ',';
					l = input2line(d, stoi(str), start);
					cable.push_back(l);
					start = l.back();
					str = "";
				}else if (c == 'R') {
					// cout<< c;
					d = right;
				} else if (c == 'U') {
					// cout<< c;
					d = up;
				} else if (c == 'L') {
					// cout<< c;
					d = left;
				} else if (c == 'D'){
					// cout<< c;
					d = down;
				}else{
					str+=c;
				}
			}
			// cout<< str << endl;
			l = input2line(d, stoi(str), start);
			in.push_back(cable);
		}
	}
	return in;
}

bool is_orthogonal(line l1, line l2){
	point p = (l1[1]-l1[0]) + (l2[1]-l2[0]);
	return (abs(p.x)==1 && abs(p.y)==1);
}

point calc_intersection(line l1, line l2) {
	if (is_orthogonal(l1, l2) || l1[0].x == l2[0].x || l1[0].y == l2[0].y){
		for (point p1 : l1) {
			for (point p2 : l2) {
				if (p1 == p2){
					return p1;
				}
			}
		}
	}
	return {0,0};
}

vector<point> calc_intersections(vector<line> l1, vector<line> l2) {
	vector<point> ps;
	point origin = {0,0};
	for (line l : l1) {
		for (line m : l2) {
			point p = calc_intersection(l,m);
			if (!(p == origin)){

				ps.push_back(p);
			}
		}
	}
	return ps;
}

void task1(vector<point> pv){
	int closeest = 9999999;
	for (point p : pv){
		int manhattan = abs(p.x) + abs(p.y);
		// cout<< "M:" << manhattan << endl;
		if (manhattan < closeest) {
			// cout<< "C:" << closeest << endl;
			closeest = manhattan;
		}
	}
	cout << "Star 1:" << closeest << endl;
}

int calc_task2_len(line cab, point intersec){
	vector<point> visited1;
	vector<point> visited2;
	bool reached = false;

	for (point p : cab){
		if (!reached){
			auto pos = find(visited1.begin(),visited1.end(),p);
			if (pos!=visited1.end()){
				visited1.erase(pos, visited1.end());
			}
			visited1.push_back(p);
		}else{
			visited2.push_back(p);
			auto pos = find(visited1.begin(),visited1.end(),p);
			if (pos!=visited1.end()){
				if ((int)visited2.size() < distance(pos,visited1.end())){
					/*cout << pos->x << ',' << pos->y << endl;
					cout << distance(pos,visited1.end()) << ':' << (int)visited2.size() << endl;
					cout << (int)visited1.size() << endl;
					*/
					reverse(visited2.begin(),visited2.end());
					visited1.erase(pos, visited1.end());
					visited1.insert(visited1.end(),visited2.begin(),visited2.end());

					//cout << (int)visited1.size() << endl;
				}
			}
		}
		if (p == intersec){
			reached = true;
			visited2.push_back(p);
		}
	}
	return (int)visited1.size()-1; // Skip start point
}

void task2(vector<point> pv, vector<line> cable1, vector<line> cable2){
	int closeest = 9999999;
	vector<point> c1 = {{0,0}};
	vector<point> c2 = {{0,0}};
	for (line l1 : cable1){
		c1.insert(c1.end(), l1.begin()+1, l1.end());
	}
	for (line l2 : cable2){
		c2.insert(c2.end(), l2.begin()+1, l2.end());
	}
	for (point inter : pv){
		int c1_len = calc_task2_len(c1, inter);
		int c2_len = calc_task2_len(c2, inter);
		
		int len = c1_len+c2_len;
		if (len<closeest){
			closeest = len;
		}
	}
	cout << "Star 2:" << closeest << endl;
}

int main()
{
	bool debug = false;
	string loc = "../inputs/day03.txt";
	if (debug){
		loc = "../inputs/day03_debug.txt";
	}
	vector<vector<line>> in = read_input(loc);
	vector<point> pv = calc_intersections(in[0], in[1]);
	task1(pv);
	task2(pv,in[0],in[1]);
	if (debug) {
		pv = calc_intersections(in[2], in[3]);
		task1(pv);
		task2(pv,in[2],in[3]);
	}
	return 0;
}
}