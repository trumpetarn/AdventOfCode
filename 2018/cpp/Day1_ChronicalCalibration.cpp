#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

using namespace std;

int part_one() {
	string line;
	int freq = 0;
	ifstream input ("../inputs/day01.txt");

	if (input.is_open())
  {
    while ( getline (input,line) )
    {
      freq += stoi(line);
    }
    input.close();
  }
	return freq;
}

int main(int, char**)
{
	int result = part_one();
	cout << "Part 1: Frequency: " << result << "\n";

	return 0;
}