#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> f_change;

int part_one() {
	string line;
	int freq = 0;
	ifstream input ("../inputs/day01.txt");

	if (input.is_open())
  {
    while ( getline (input,line) )
    {
    	f_change.push_back(stoi(line));
      freq += stoi(line);
    }
    input.close();
  }
	return freq;
}

int part_two() {
	string line;
	int freq = 0;
	set<int> freqs;
	int i = 0;
  while (!(freqs.find(freq) != freqs.end()))
  {
  	freqs.insert(freq);
    freq += f_change[i];
    i = (i+1)%f_change.size();
  }
	return freq;
}

int main(int, char**)
{
	int result = part_one();
	cout << "Part 1: Frequency: " << result << "\n";
	result = part_two();
	cout << "Part 2: Frequency: " << result << "\n";
	return 0;
}