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
#include <math.h>

using namespace std;
namespace day04{
static int still_ok = 0;

bool is_password(int i){
	vector<int> digits;
	vector<int> adjacent;
	bool adj = false;
	int prev = 99;
	while (i != 0) {
			int tmp = i % 10;
      digits.push_back(tmp);
      if (tmp > prev){
      	return false;
      }
      if (tmp == prev){
      	adj = true;
      	adjacent.push_back(tmp);
      }
      i /= 10;
      prev = tmp;
  }
  if (adj){
  	for (int d : adjacent){
  		if (count(adjacent.begin(),adjacent.end(),d) == 1){
  			still_ok++;
  			break;
  		}
  	}
  }
	return adj;
}

vector<int> find_all_passwords(int min, int max){
	vector<int> v;
	for (int i=min; i<max; i++){
		if (is_password(i)){
			v.push_back(i);
		}
	}
	return v;
}

int main()
{
	int min = 254032;
	int max = 789860;
	vector<int> pwd = find_all_passwords(min, max);
	cout << "Star 1: " << pwd.size() << endl;
	cout << "Star 2: " << still_ok << endl;
	return 0;
}
}//namespace day02