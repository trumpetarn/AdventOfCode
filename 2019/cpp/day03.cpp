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

struct line
{
	point start;
	point end;
};

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

line input2line(Direction d, int len, point start){
	line l;
	l.start = start;
	l.end = calc_endpoint(start, d, len);
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
					l = input2line(d, stoi(str), start);
					cable.push_back(l);
					start = l.end;
					cout << str << ',';
					str = "";
				}else if (c == 'R') {
					cout << c;
					d = right;
				} else if (c == 'U') {
					cout << c;
					d = up;
				} else if (c == 'L') {
					cout << c;
					d = left;
				} else if (c == 'D'){
					cout << c;
					d = down;
				}else{
					str+=c;
				}
			}
			l = input2line(d, stoi(str), start);
			cout << str << endl;
			in.push_back(cable);
		}
	}
	return in;
}

point calc_intersection(line l, line m) {
	point p = {0,0};
	if (l.start.x == l.end.x && m.start.y == m.end.y){
		if ((l.start.y >= m.start.y && m.start.y >= l.end.y) 
			|| (l.start.y <= m.start.y && m.start.y <= l.end.y)) {
			p.x = l.start.x;
			p.y = m.start.y;
			return p;
		}
	}else if (l.start.y == l.end.y && m.start.x == m.end.x){
		if ((l.start.y <= m.start.y && m.start.y <= l.end.y) 
			|| (l.start.y >= m.start.y && m.start.y >= l.end.y)) {
			p.x = m.start.x;
			p.y = l.start.y;
			return p;
		}
	}else if (l.start.x == l.end.x && m.start.x == m.end.x && m.start.x==l.start.x) {
		if (l.start.y <= m.start.y && l.end.y>=m.start.y) {
			p.x = l.start.x;
			p.y = m.start.y;
			return p;
		} else if (m.start.y <= l.start.y && m.end.y>=l.start.y) {
			p.x = l.start.x;
			p.y = l.start.y;
			return p;
		}
	}else if (l.start.y == l.end.y && m.start.y == m.end.y && m.start.y==l.start.y) {
		if (l.start.x <= m.start.x && l.end.x>=m.start.x) {
			p.x = l.start.x;
			p.y = m.start.y;
			return p;
		} else if (m.start.x <= l.start.x && m.end.x>=l.start.x) {
			p.x = l.start.x;
			p.y = l.start.y;
			return p;
		}
	}
	return p;
}

bool isEqual(point p1, point p2) {
	return (p1.x==p2.x && p1.y == p2.y);
}

vector<point> calc_intersections(vector<line> l1, vector<line> l2) {
	vector<point> ps;
	int closeest = 9999999;
	for (line l : l1) {
		for (line m : l2) {
			point p = calc_intersection(l,m);
			if (!isEqual(p, {0,0})){
				ps.push_back(p);
				int manhattan = abs(p.x) + abs(p.y);
				cout << manhattan << ',';
				if (manhattan < closeest) {
					cout << closeest << endl;
					closeest = manhattan;
				}
			}
		}
	}
	cout << closeest << endl;
	return ps;
}

int main()
{
	string loc = "../inputs/day03.txt";

	vector<vector<line>> in = read_input(loc);
	cout << in.size() << endl;
	calc_intersections(in[0], in[1]);
	return 0;
}
}