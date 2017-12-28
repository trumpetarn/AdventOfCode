#include <stdio.h>
#include <stdbool.h>
#define N 20000
typedef enum state {A,B,C,D,E,F} State;
static int tape[N];

void init_array() {
	for (int i=0; i<N; i++) {
		tape[i] = 0;
	}
}

int count_array() {
	int ret=0;
	for (int i=0; i<N; i++) {
		if (tape[i]==1)
			ret++;
	}
	return ret;
}

int state_A(int pos) {
	
	return pos;
}


int main(void) {
	State s = A;
	int pos = N/2;
	init_array();
	for (int i=0; i<12459852; i++) {
		if (pos < 0 || pos >= N) {
			printf("%d, %d\n", i, pos);
			break;
		}

		switch (s) {
			case A:
				if (tape[pos]==0) {
					tape[pos] =  1;
					pos++;
					s = B;
				}else{
					tape[pos] = 1;
					pos--;
					s = E;
				}
				break;
			case B:
				if (tape[pos]==0) {
					tape[pos] =  1;
					pos++;
					s = C;
				}else{
					tape[pos] = 1;
					pos++;
					s = F;
				}
				break;
			case C:
				if (tape[pos]==0) {
					tape[pos] =  1;
					pos--;
					s = D;
				}else{
					tape[pos] = 0;
					pos++;
					s = B;
				}
				break;
			case D:
				if (tape[pos]==0) {
					tape[pos] =  1;
					pos++;
					s = E;
				}else{
					tape[pos] = 0;
					pos--;
					s = C;
				}
				break;
			case E:
				if (tape[pos]==0) {
					tape[pos] =  1;
					pos--;
					s = A;
				}else{
					tape[pos] = 0;
					pos++;
					s = D;
				}
				break;
			case F:
				if (tape[pos]==0) {
					tape[pos] =  1;
					pos++;
					s = A;
				}else{
					tape[pos] = 1;
					pos++;
					s = C;
				}
				break;
		}
	}
	printf("%d\n",count_array());
}