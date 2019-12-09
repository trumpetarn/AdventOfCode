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
bool operator<(const point& p1, const point& p2) {
	pair<int,int> pair1(p1.x, p1.y);
	pair<int,int> pair2(p2.x, p2.y);
	return pair1 < pair2;
}
point operator+(const point& p1, const point& p2) {
	point p3 = {p1.x+p2.x, p1.y+p2.y};
	return p3;
}
point operator-(const point& p1, const point& p2) {
	point p3 = {p1.x-p2.x, p1.y-p2.y};
	return p3;
}
point operator*(const int& c, const point& p2){
	return {c*p2.x, c*p2.y};
}
std::ostream &operator<<(std::ostream &os, const point& p) { 
    return os << p.x << ',' << p.y;
}

vector<vector<point>> read_input(string loc)
{
	vector<vector<point>> in;
	ifstream infile (loc);
	string ln, str;
	str = "";
	point origin = {0,0};
	if (infile.is_open())
	{
		while (getline(infile,ln))
		{	
			point dir;
			vector<point> lv;
			lv.push_back(origin);
			for (char c : ln) {
				if (c == ',') {
					point last = lv.back();
					for (int i=0; i<stoi(str); i++){
						point p = (i+1)*dir + last;
						lv.push_back(p);
					}
					str = "";
				}else if (c == 'R') {
					dir = {1,0};
				} else if (c == 'U') {
					dir = {0,1};
				} else if (c == 'L') {
					dir = {-1,0};
				} else if (c == 'D'){
					dir = {0,-1};
				}else{
					str+=c;
				}
			}
			point last = lv.back();
			for (int i=0; i<stoi(str); i++){
				point p = (i+1)*dir + last;
				lv.push_back(p);
			}
			str = "";
			in.push_back(lv);
		}
	}
	return in;
}

void task1(vector<point> inter){
	int min = 9999999;
	int manhattan;
	point origin = {0,0};
	for (point& p : inter){
		if (p != origin){
			//cout << p.x << ',' << p.y << "::";
			manhattan = abs(p.x) + abs(p.y);
			if (manhattan < min){
				min = manhattan;
			}
			//cout << manhattan << endl;
		}
	}
	cout << "Star 1: " << min << endl;
}

void task2(vector<point> inter, vector<point> c1, vector<point> c2){
	int min = 9999999;
	int len;
	point origin = {0,0};
	for (point& p : inter){
		if (p != origin){
			auto l1 = find(c1.begin(),c1.end(),p);
			auto l2 = find(c2.begin(),c2.end(),p);
			len = distance(c1.begin(), l1) + distance(c2.begin(), l2);
			if (len < min){
				min = len;
			}
		}
	}
	cout << "Star 2: " << min << endl;
}

int main()
{
	string loc = "../inputs/day03.txt";
	vector<vector<point>> in = read_input(loc);
	vector<point> c1 = in[0];
	vector<point> c2 = in[1];
	vector<point> c1_ordered = in[0];
	vector<point> c2_ordered = in[1];
	sort(c1.begin(),c1.end());
	sort(c2.begin(),c2.end());

	vector<point> intersections;
	set_intersection(c1.begin(),c1.end(),c2.begin(),c2.end(),back_inserter(intersections));

	task1(intersections);
	task2(intersections,c1_ordered,c2_ordered);
	return 0;
}
}