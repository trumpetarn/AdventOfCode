#include<stdio.h>
#include<stdbool.h>
#define N 57

typedef struct Component{
	int port1;
	int port2;
}component;

component components[N];
component used[N];
int num_used = 0;
int longest = 0;
int long_str = 0;

void get_components(bool debug) {
	FILE *fp;
	if (debug) {
		fp = fopen("/repo/AdventOfCode/2017/inputs/input_test.txt", "r");
	}else{
		fp = fopen("/repo/AdventOfCode/2017/inputs/input_day24.txt", "r");
	}
	int p1, p2;
	for (int i=0;i<N;i++) {
		fscanf(fp, "%d/%d\n", &p1, &p2);
		components[i].port1 = p1;
		components[i].port2 = p2;
	}
}

bool is_used(component c) {
	for (int i=0; i<num_used; i++) {
		if ((c.port1 == used[i].port1) && (c.port2 == used[i].port2))
			return true;
	}
	return false;
}

int get_port(int port, int index[N]){
	int j = 0;
	for (int i=0; i<N; i++) {
		if (components[i].port1 == port || components[i].port2 == port) {
			if (!is_used(components[i])){
				index[j] = i;
				j++;
			}
		}
	}
	return j;
}

int get_used_strength(void) {
	int str=0;
	for (int i=0; i<num_used; i++) {
		str += (used[i].port1 + used[i].port2);
	}
	return str;
}

int foo(int port){
	int id[N], new, ret, str, tmp_str;
	int n = get_port(port, id);
	if (n==0) {
		if (num_used > longest) {
			longest = num_used;	
			long_str = get_used_strength();
		}else if (num_used == longest){
			tmp_str = get_used_strength();
			if (tmp_str > long_str) {
				long_str = tmp_str;
			}
		}
	}
	int max = 0;
	num_used++;
	for (int i=0; i<n; i++) {
		used[num_used-1] = components[id[i]];
		new = components[id[i]].port1 == port ? components[id[i]].port2 : components[id[i]].port1;
		str = new + port;
		ret = foo(new);
		if (ret+str > max){
			max = ret+str;
		}
	}
	num_used--;
	return max;
}

int main(void) {
	get_components(false);
	int max = foo(0);
	printf("Max: %d\n", max);
	printf("Longest: %d str:%d\n", longest, long_str);
	return 0;
}