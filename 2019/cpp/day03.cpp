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
#include "helper.h"

using namespace std;
using namespace helper;

namespace day03{

vector<vector<Point>> read_input(string loc)
{
	vector<vector<Point>> in;
	ifstream infile (loc);
	string ln, str;
	str = "";
	Point origin = {0,0};
	if (infile.is_open())
	{
		while (getline(infile,ln))
		{	
			Point dir;
			vector<Point> lv;
			lv.push_back(origin);
			for (char c : ln) {
				if (c == ',') {
					Point last = lv.back();
					for (int i=0; i<stoi(str); i++){
						Point p = (i+1)*dir + last;
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
			Point last = lv.back();
			for (int i=0; i<stoi(str); i++){
				Point p = (i+1)*dir + last;
				lv.push_back(p);
			}
			str = "";
			in.push_back(lv);
		}
	}
	return in;
}

void task1(vector<Point> inter){
	int min = 9999999;
	int manhattan;
	Point origin = {0,0};
	for (Point& p : inter){
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

void task2(vector<Point> inter, vector<Point> c1, vector<Point> c2){
	int min = 9999999;
	int len;
	Point origin = {0,0};
	for (Point& p : inter){
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
	vector<vector<Point>> in = read_input(loc);
	vector<Point> c1 = in[0];
	vector<Point> c2 = in[1];
	vector<Point> c1_ordered = in[0];
	vector<Point> c2_ordered = in[1];
	sort(c1.begin(),c1.end());
	sort(c2.begin(),c2.end());

	vector<Point> intersections;
	set_intersection(c1.begin(),c1.end(),c2.begin(),c2.end(),back_inserter(intersections));

	task1(intersections);
	task2(intersections,c1_ordered,c2_ordered);
	return 0;
}
}