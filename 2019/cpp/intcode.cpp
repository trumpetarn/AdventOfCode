#include "intcode.h"
#include <iostream>

using namespace std;
namespace intcode{
/*
ABCDE
 1002

DE - two-digit opcode,      02 == opcode 2
 C - mode of 1st parameter,  0 == position mode
 B - mode of 2nd parameter,  1 == immediate mode
 A - mode of 3rd parameter,  0 == position mode,
                                  omitted due to being a leading zero
                                  */

int get_param(vector<int> n, int pos, int opcode) {
	int p=-1;
	switch(opcode){
		case 0:
			p= n[n[pos]];
			break;
		case 1:
			p=n[pos];
			break;
		default:
			cout << "ERROR: Invalid opcode";
	}
	return p;
}

int run(vector<int> n, vector<int> inputs, int &output){
	int p1,p2;
	int input_it = 0;
	int input_size = (int) inputs.size();
	for (uint pos = 0;pos<n.size();){
		int opcode = n[pos];
		int A = (opcode/10000)%10;
		int B = (opcode/1000)%10;
		int C = (opcode/100)%10;
		int DE = (opcode)%100;
		//cout << A << B << C << ',' << DE << " " << opcode << endl;
		if (A!=0){
			cout << "A != 0";
		}
		switch(DE){
			case 1: //Add
				p1 = get_param(n, pos+1, C);
				p2 = get_param(n, pos+2, B);
				n[n[pos+3]] = p1 + p2;
				pos += 4;
				break;
			case 2: //Multiply
				p1 = get_param(n, pos+1, C);
				p2 = get_param(n, pos+2, B);
				n[n[pos+3]] = p1 * p2;
				pos += 4;
				break;
			case 3: //Write
				//cout << "write: (" << inputs[input_it] << ") ";
				// TODO: We have to wait until we get the next input
				if (input_it>=input_size){
					return pos;
				}
				n[n[pos+1]] = inputs[input_it++];
				pos += 2;
				break;
			case 4: //Print
				p1 = get_param(n, pos+1, C);
				if (p1!=0){
					output = p1;
				}
				pos += 2;
				break;
			case 5: //jump if true
				p1 = get_param(n, pos+1, C);
				p2 = get_param(n, pos+2, B);
				if (p1 != 0){
					pos = p2;
				}else{
					pos += 3;
				}
				break;
			case 6: //jump is false
				p1 = get_param(n, pos+1, C);
				p2 = get_param(n, pos+2, B);
				if (p1 == 0){
					pos = p2;
				}else{
					pos += 3;
				}
				break;
			case 7: //less than
				p1 = get_param(n, pos+1, C);
				p2 = get_param(n, pos+2, B);
				n[n[pos+3]] = (p1 < p2) ? 1 : 0;
				pos += 4;
				break;
			case 8: //Equals
				p1 = get_param(n, pos+1, C);
				p2 = get_param(n, pos+2, B);
				n[n[pos+3]] = (p1 == p2) ? 1 : 0;
				pos += 4;
				break;
			case 99:
				//cout << "Returns " << n[0] << endl;
				return n[0];
			default:
				cout << "ERROR!" << endl;
				return -1;
		}
	}
	return -1;
}
int run(std::vector<int> n, std::vector<int> inputs){
	int out, ret;
	ret = run(n,inputs, out);
	cout << out << endl;
	return ret;
}

int run(vector<int> n, int input){
	vector<int> v = {input};
	return run(n,v);
}

}