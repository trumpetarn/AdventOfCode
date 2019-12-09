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
namespace day05{
/*
ABCDE
 1002

DE - two-digit opcode,      02 == opcode 2
 C - mode of 1st parameter,  0 == position mode
 B - mode of 2nd parameter,  1 == immediate mode
 A - mode of 3rd parameter,  0 == position mode,
                                  omitted due to being a leading zero
                                  */


int intcode(vector<int> n, int input = 1){
	int p1,p2;
	for (uint pos = 0;pos<n.size();){
		int opcode = n[pos];
		int A = (opcode/10000)%10;
		int B = (opcode/1000)%10;
		int C = (opcode/100)%10;
		int DE = (opcode)%100;
		//cout << A << B << C << ',' << DE << " " << opcode << endl;
		if (A==1){
			cout << 1;
		}
		switch(DE){
			case 1: //Add
				p1 = (C==1) ? n[pos+1] : n[n[pos+1]];
				p2 = (B==1) ? n[pos+2] : n[n[pos+2]];
				n[n[pos+3]] = p1 + p2;
				pos += 4;
				break;
			case 2: //Multiply
				p1 = (C==1) ? n[pos+1] : n[n[pos+1]];
				p2 = (B==1) ? n[pos+2] : n[n[pos+2]];
				n[n[pos+3]] = p1 * p2;
				pos += 4;
				break;
			case 3: //Write
				n[n[pos+1]] = input;
				pos += 2;
				break;
			case 4: //Print
				p1 = (C==1) ? n[pos+1] : n[n[pos+1]];
				cout << p1 << endl;
				pos += 2;
				break;
			case 5: //jump if true
				p1 = (C==1) ? n[pos+1] : n[n[pos+1]];
				p2 = (B==1) ? n[pos+2] : n[n[pos+2]];
				if (p1 != 0){
					pos = p2;
				}else{
					pos += 3;
				}
				break;
			case 6: //jump is false
				p1 = (C==1) ? n[pos+1] : n[n[pos+1]];
				p2 = (B==1) ? n[pos+2] : n[n[pos+2]];
				if (p1 == 0){
					pos = p2;
				}else{
					pos += 3;
				}
				break;
			case 7: //less than
				p1 = (C==1) ? n[pos+1] : n[n[pos+1]];
				p2 = (B==1) ? n[pos+2] : n[n[pos+2]];
				n[n[pos+3]] = (p1 < p2) ? 1 : 0;
				pos += 4;
				break;
			case 8: //Equals
				p1 = (C==1) ? n[pos+1] : n[n[pos+1]];
				p2 = (B==1) ? n[pos+2] : n[n[pos+2]];
				n[n[pos+3]] = (p1 == p2) ? 1 : 0;
				pos += 4;
				break;
			case 99:
				return n[0];
			default:
				cout << "ERROR!" << endl;
				return -1;
		}
	}
	return -1;
}

void task1(vector<int> input){
	int res = 0;
	res = intcode(input);
	cout << "Star 1: " << res << endl;
}

void task2(vector<int> input){
	int res = 0;
	res = intcode(input, 5);
	cout << "Star 2: " << res << endl;
}

int main()
{
	vector<int> input = {3,225,1,225,6,6,1100,1,238,225,104,0,1102,88,66,225,101,8,125,224,101,-88,224,224,4,224,1002,223,8,223,101,2,224,224,1,224,223,223,1101,87,23,225,1102,17,10,224,101,-170,224,224,4,224,102,8,223,223,101,3,224,224,1,223,224,223,1101,9,65,225,1101,57,74,225,1101,66,73,225,1101,22,37,224,101,-59,224,224,4,224,102,8,223,223,1001,224,1,224,1,223,224,223,1102,79,64,225,1001,130,82,224,101,-113,224,224,4,224,102,8,223,223,1001,224,7,224,1,223,224,223,1102,80,17,225,1101,32,31,225,1,65,40,224,1001,224,-32,224,4,224,102,8,223,223,1001,224,4,224,1,224,223,223,2,99,69,224,1001,224,-4503,224,4,224,102,8,223,223,101,6,224,224,1,223,224,223,1002,14,92,224,1001,224,-6072,224,4,224,102,8,223,223,101,5,224,224,1,223,224,223,102,33,74,224,1001,224,-2409,224,4,224,1002,223,8,223,101,7,224,224,1,223,224,223,4,223,99,0,0,0,677,0,0,0,0,0,0,0,0,0,0,0,1105,0,99999,1105,227,247,1105,1,99999,1005,227,99999,1005,0,256,1105,1,99999,1106,227,99999,1106,0,265,1105,1,99999,1006,0,99999,1006,227,274,1105,1,99999,1105,1,280,1105,1,99999,1,225,225,225,1101,294,0,0,105,1,0,1105,1,99999,1106,0,300,1105,1,99999,1,225,225,225,1101,314,0,0,106,0,0,1105,1,99999,107,677,677,224,1002,223,2,223,1006,224,329,101,1,223,223,108,677,677,224,1002,223,2,223,1005,224,344,101,1,223,223,1007,677,677,224,1002,223,2,223,1006,224,359,101,1,223,223,1107,226,677,224,1002,223,2,223,1006,224,374,1001,223,1,223,8,677,226,224,1002,223,2,223,1006,224,389,101,1,223,223,1108,677,677,224,1002,223,2,223,1005,224,404,1001,223,1,223,7,226,226,224,1002,223,2,223,1006,224,419,101,1,223,223,1107,677,677,224,1002,223,2,223,1005,224,434,101,1,223,223,107,226,226,224,102,2,223,223,1005,224,449,101,1,223,223,107,677,226,224,1002,223,2,223,1006,224,464,1001,223,1,223,8,226,677,224,102,2,223,223,1006,224,479,1001,223,1,223,108,677,226,224,102,2,223,223,1005,224,494,1001,223,1,223,1108,677,226,224,1002,223,2,223,1005,224,509,1001,223,1,223,1107,677,226,224,1002,223,2,223,1005,224,524,101,1,223,223,1008,226,226,224,1002,223,2,223,1006,224,539,101,1,223,223,1008,226,677,224,1002,223,2,223,1005,224,554,1001,223,1,223,7,226,677,224,1002,223,2,223,1005,224,569,101,1,223,223,1007,677,226,224,1002,223,2,223,1006,224,584,1001,223,1,223,7,677,226,224,102,2,223,223,1006,224,599,101,1,223,223,1007,226,226,224,102,2,223,223,1006,224,614,101,1,223,223,1008,677,677,224,1002,223,2,223,1006,224,629,101,1,223,223,108,226,226,224,102,2,223,223,1006,224,644,101,1,223,223,1108,226,677,224,1002,223,2,223,1005,224,659,101,1,223,223,8,226,226,224,1002,223,2,223,1005,224,674,101,1,223,223,4,223,99,226};
	//vector<int> debug = {3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99};

	task1(input);
	task2(input);
	return 0;
}
}//namespace day02