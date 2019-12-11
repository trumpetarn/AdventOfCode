#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <numeric>
#include <unistd.h>
#include <iterator>
#include <list>
#include <math.h>

using namespace std;
namespace day06{
static unordered_map<string, vector<string>> tree;
//static int direct_orbits = 0;
//static int indirect_orbits = 0;

unordered_map<string, vector<string>> read_input(string loc)
{
	unordered_map<string, vector<string>> in;
	string line;
	ifstream infile (loc);
	if (infile.is_open())
	{
		while (getline(infile,line))
		{
			string AAA = line.substr(0,3);
			string BBB = line.substr(4,3);
			//cout << AAA << ':' << BBB << endl;
			in[AAA].push_back(BBB);
		}
	}
	return in;
}


unsigned int calc_orbits(string key, int level, int& total){
	vector<string> v = tree[key];
	int direct_orbits = v.size();
	int indirect_orbits = level;
	total += direct_orbits+indirect_orbits;
	for (string s: v){
		// cout << calc_orbits(s, level+1, total) << ';';
		calc_orbits(s, level+1, total);
	}
	return direct_orbits+indirect_orbits;
}

int task1(){
	int ret=1; // Start ret with 1 to accomodate for the "indirect" fux to start at level -1
	calc_orbits("COM", -1, ret); 
	return ret;
}

bool find_branch(string key, string search_key, vector<string> &result){
	vector<string> v = tree[key];
	if (find(v.begin(),v.end(),search_key) != v.end()){
		return true;
	}
	for (string s : v){
		if (find_branch(s, search_key, result)){
			//cout << s << ',';
			result.push_back(s);
			return true;
		}
	}
	return false;
}

int task2(){
	vector<string> me;
	vector<string> santa;
	find_branch("COM", "YOU", me);
	find_branch("COM", "SAN", santa);
	int i = 0;
	for (auto it=me.begin(); it!=me.end(); ++it){
		auto pos = find(santa.begin(),santa.end(),*it);
		if (pos != santa.end()){
			// Since the vectors are reversed we calculate from the start
			return distance(me.begin(),it) + distance(santa.begin(),pos);
		}
		i++;
	}
	return i;
}

int main()
{
	string path = "../inputs/day06.txt";
	unordered_map<string, vector<string>> input = read_input(path);
	tree = input;
	cout << "Star 1: " << task1() << endl;
	cout << "Star 2: " << task2() << endl;
	return 0;
}
}//namespace day06