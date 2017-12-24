#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<limits.h>
#define N 1000

typedef struct Coordinates{
	int x;
	int y;
	int z;
}coords;

typedef struct Particle{
	coords p;
	coords v;
	coords a;
	int death_tick;
	bool alive;
}particle;

static particle particles[N];

/* Initiates the particles struct */
void init(void){
	FILE *fp = fopen("/repo/AdventOfCode/2017/inputs/input_day20.txt", "r");
	int px,py,pz,vx,vy,vz,ax,ay,az;
	for (int i=0;i<N;i++) {
		fscanf(fp, "p=< %d,%d,%d>, v=< %d,%d,%d>, a=< %d,%d,%d>\n", &px, &py, &pz, &vx, &vy, &vz, &ax, &ay, &az);
		particles[i].p.x = px;
		particles[i].p.y = py;
		particles[i].p.z = pz;

		particles[i].v.x = vx;
		particles[i].v.y = vy;
		particles[i].v.z = vz;

		particles[i].a.x = ax;
		particles[i].a.y = ay;
		particles[i].a.z = az;
		particles[i].death_tick = -1;
		particles[i].alive = true;
	}
	fclose(fp);
	return;
}


void accelerate(particle *p){
	if (p->alive) {
		p->v.x += p->a.x;
		p->v.y += p->a.y;
		p->v.z += p->a.z;
	}
	return;
}

/* Returns the manhattan distance from 0,0,0 */
int manhattan(coords c){
	return (abs(c.x)+abs(c.y)+abs(c.z));
}

void move(particle *p){
	p->p.x += p->v.x;
	p->p.y += p->v.y;
	p->p.z += p->v.z;
	return;
}

bool is_equal(coords a, coords b) {
	return (a.x==b.x) && (a.y==b.y) && (a.z == b.z);
}

/* Returns number of collitions */
bool collition_detection(int len, coords c, int i) {
	bool ret = false;
	for (int j=0; j<len; j++) {
		if (particles[j].alive && is_equal(c, particles[j].p)) {
			//printf("%d:", j);
			particles[j].death_tick = i;
			ret = true;
		}
	}
	return ret;
}

int find_lowest_acc(int lowest_p[N]) {
	int lowest_a = 100000000;
	int acc, k;
	for (int i=0;i<N;i++){
		acc = manhattan(particles[i].a);
		if (acc < lowest_a)
		{
			lowest_a = acc;
			k = 0;
			lowest_p[k] = i;
			k++;
		}else if (acc == lowest_a){
			lowest_p[k] = i;
			k++;
		}
	}
}

void kill_particles(int k) {
	for (int i=0; i<N; i++) {
		if (particles[i].death_tick == k) {
			particles[i].alive = false;
			//printf("%d ", i);
		}
	}
}

int still_alive(void) {
	int alive = 0;
	for (int i=0; i<N; i++) {
		if (particles[i].alive)
			alive++;
	}
	return alive;
}

/* TODO: Improve efficency */
int main(void){
	init();
	int closest = 100000000;
	int acc, idx_len, small, l, collitions =0;
	int index[N];
	idx_len = find_lowest_acc(index);
	for (int k=0; k<100; k++) {
		closest = 100000000;	
		for (int i=0; i<N; i++) {
			if (k==0) {
				if (collition_detection(i, particles[i].p, k)) {
					printf("%s\n", "HEj");
					particles[i].death_tick = k;
				}
			}else if (particles[i].alive) {
				accelerate(&particles[i]);
				move(&particles[i]);
				if (collition_detection(i, particles[i].p, k)) {
					particles[i].death_tick = k;
				}
			}
			if (i<idx_len) {
				small = manhattan(particles[index[i]].p);
				if (small < closest) {
					closest = small;
					l = index[i];
				}
			}
		}
		kill_particles(k);
	}
	printf("Part 1: %d\n", l);
	printf("Part 2: %d\n", still_alive());
	return 0;
}