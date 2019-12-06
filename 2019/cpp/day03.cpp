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

typedef vector<point> line;

enum Direction {
	up,
	down,
	left,
	right
};
bool operator==(const point& p1, const point& p2) {
	return (p1.x==p2.x && p1.y == p2.y);
}
/*
Direction get_direction(line l){
	Direction d;
	if (l.start.x==l.end.x){
		// Move y
		if (l.start.y>l.end.y){
			d = down;
		}else{
			d = up;
		}
	}else{
		// Move x
		if (l.start.x>l.end.x){
			d = left;
		}else{
			d = right;
		}
	}
	return d;
}
*/
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
	for (int i=0; i<len; ++i){
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
					l = input2line(d, stoi(str), start);
					cable.push_back(l);
					start = l.back();
					str = "";
				}else if (c == 'R') {
					//cout << c;
					d = right;
				} else if (c == 'U') {
					//cout << c;
					d = up;
				} else if (c == 'L') {
					//cout << c;
					d = left;
				} else if (c == 'D'){
					//cout << c;
					d = down;
				}else{
					str+=c;
				}
			}
			l = input2line(d, stoi(str), start);
			in.push_back(cable);
		}
	}
	return in;
}

point calc_intersection(line l, line m) {
	for (point p1 : l) {
		auto it = find(m.begin(), m.end(), p1);
		if (it != m.end()) {
			return *it;
		}
	}
	return {0,0};
}

/*
point calc_intersection2(line l, line m) {
	point p1=l.start;
	point p2=m.start;
	Direction d1 = get_direction(l);
	Direction d2 = get_direction(m);
	point lend = next(l.end, d1);
	point mend = next(m.end, d2);
	while (!isEqual(p1,lend)) {
		while (!isEqual(p2,mend)) {
			if (isEqual(p1,p2) && !isEqual(p1, {0,0})){
				cout << p1.x << p2.y << endl;
				return p1;
			}
			p2 = next(p2,d2);
		}
		p1 = next(p1,d1);
	}
	return {0,0};
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
		if (l.start.y <= m.start.y && l.end.y >= m.start.y) {
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
*/
vector<point> calc_intersections(vector<line> l1, vector<line> l2) {
	vector<point> ps;
	int closeest = 9999999;
	point origin = {0,0};
	for (line l : l1) {
		for (line m : l2) {
			point p = calc_intersection(l,m);
			if (!(p == origin)){
				ps.push_back(p);
				int manhattan = abs(p.x) + abs(p.y);
				cout << manhattan << endl;
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
	calc_intersections(in[0], in[1]);
	return 0;
}
}