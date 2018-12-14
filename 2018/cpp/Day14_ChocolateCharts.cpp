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

int main(int argc, char** argv)
{
	int input = 540391;
	if (argc >= 2)
		input = stoi(argv[1]);
	vector<int> recipes;
	int posA = 0;
	int posB = 1;
	recipes.push_back(3);
	recipes.push_back(7);
	for (int i=0; i<input+10; i++)
	{
		/*
		for (int j=0; j<(int)recipes.size(); j++)
		{
			if (j == posA && j == posB)
				cout << "([" << recipes[j] << "])";
			else if (j == posA)
				cout << '(' << recipes[j] << ")";	
			else if (j == posB)
				cout << '[' << recipes[j] << "]";	
			else
				cout << recipes[j] << ' ';
		}
		cout << endl;
		*/

		//add recepies
		int new_recipe = recipes[posA] + recipes[posB];
		//cout << new_recipe << endl;
		if (new_recipe > 9)
		{
			//cout <<':'<< (new_recipe/10) << endl;
			recipes.push_back((new_recipe/10));
		}
		//cout <<"::"<< (new_recipe%10) << endl;
		recipes.push_back(new_recipe%10);
		//cout <<":::"<< (recipes.size()) << endl;
		//move
		int stepsA = recipes[posA]+1;
		int stepsB = recipes[posB]+1;
		//cout << "::::" << stepsA << ',' << stepsB << endl;
		posA = ((posA + stepsA)%(int)recipes.size());
		posB = ((posB + stepsB)%(int)recipes.size());
		//cout << "::::" << posA << ',' << posB << endl;
	}
	for (int j=input; j<input+10; j++)
	{
			cout << recipes[j];
	}
	cout << endl;
	return 0;
}