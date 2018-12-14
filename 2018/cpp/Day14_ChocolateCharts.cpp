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
#include <cmath>

using namespace std;

int num_digits(int in)
{
	int length = 1;
	while ( in /= 10 )
   length++;
 	return length;
}

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
	int lastDigits = 0;
	int lastDigits2 = 0;
	int numDigits = num_digits(input);
	while ((lastDigits != input)&&(lastDigits2 != input))
	{
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
		int size = (int)recipes.size();
		posA = ((posA + stepsA)%size);
		posB = ((posB + stepsB)%size);
		//cout << "::::" << posA << ',' << posB << endl;
		if (size>numDigits)
		{
			lastDigits = 0;
			lastDigits2 = 0;
			for (int i=0; i < numDigits; i++)
			{
				lastDigits += recipes[size-i-1]*pow(10,i);
				lastDigits2 += recipes[size-i-2]*pow(10,i);
			}
			//cout << numDigits << ':' << lastDigits << endl;
		}
	}
	if ((int)recipes.size()>input+10)
	{
		cout << "Task 1: ";
		for (int j=input; j<input+10; j++)
		{
				cout << recipes[j];
		}
	}
	cout << endl;
	if (lastDigits2 != input)
		cout << "Task 2: " << recipes.size()-numDigits << endl;
	else
		cout << "Task 2: " << recipes.size()-numDigits-1 << endl;
	return 0;
}