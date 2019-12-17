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
#include <array>
#include "helper.h"

using namespace std;
namespace day12{
struct Velocity{
	int x;
	int y;
	int z;
};
inline bool operator==(const Velocity& v1, const Velocity& v2) {
	return (v1.x==v2.x && v1.y == v2.y && v1.z == v2.z);
}

struct Planet{
	int x;
	int y;
	int z;
	Velocity v = {0,0,0};
};
inline bool operator==(const Planet& p1, const Planet& p2) {
	return (p1.x==p2.x && p1.y == p2.y && p1.z == p2.z && p1.v == p2.v);
}

int calc_energy(Planet p){
	int pot = abs(p.x) + abs(p.y) + abs(p.z);
	int kin = abs(p.v.x) + abs(p.v.y) + abs(p.v.z);
	return kin*pot;
}

void update_velocity(Planet& p){
	p.x += p.v.x;
	p.y += p.v.y;
	p.z += p.v.z;
}

void update_gravity(Planet& p1, Planet& p2){
	const int step = 1;
	if (p1.x < p2.x){
		p1.v.x+=step;
		p2.v.x-=step;
	}else if(p1.x > p2.x){
		p1.v.x-=step;
		p2.v.x+=step;
	}
	if (p1.y < p2.y){
		p1.v.y+=step;
		p2.v.y-=step;
	}else if (p1.y > p2.y){
		p1.v.y-=step;
		p2.v.y+=step;
	}
	if (p1.z < p2.z){
		p1.v.z+=step;
		p2.v.z-=step;
	}else if (p1.z > p2.z){
		p1.v.z-=step;
		p2.v.z+=step;
	}
}

void task1(Planet p1,Planet p2,Planet p3,Planet p4){
	//cout << "pos=<" << p1.x << ','<< p1.y << ','<< p1.z << ">, vel=<"<< p1.v.x << ','<< p1.v.y << ','<< p1.v.z << ">" << endl;
	for (int ts=0; ts<1000; ts++){
		// Apply "gravity"
		update_gravity(p1,p2);
		update_gravity(p1,p3);
		update_gravity(p1,p4);
		update_gravity(p2,p3);
		update_gravity(p2,p4);
		update_gravity(p3,p4);

		// Apply velocity
		update_velocity(p1);
		update_velocity(p2);
		update_velocity(p3);
		update_velocity(p4);
		//cout << "pos=<" << p1.x << ','<< p1.y << ','<< p1.z << ">, vel=<"<< p1.v.x << ','<< p1.v.y << ','<< p1.v.z << ">" << endl;
	}
	int E_tot = calc_energy(p1)+calc_energy(p2)+calc_energy(p3)+calc_energy(p4);
	cout << "Star 1: " << E_tot << endl;
}

int gcd(llint a, llint b) { 
   if (b == 0) 
      return a; 
   return gcd(b, a % b);
}

void task2(Planet p1,Planet p2,Planet p3,Planet p4){
	array<Planet, 4> start = {p1,p2,p3,p4};
	bool x_found = false;
	bool y_found = false;
	bool z_found = false;
	llint xr,yr,zr;
	for (llint ts=0;; ts++){
		// Apply "gravity"
		update_gravity(p1,p2);
		update_gravity(p1,p3);
		update_gravity(p1,p4);
		update_gravity(p2,p3);
		update_gravity(p2,p4);
		update_gravity(p3,p4);

		// Apply velocity
		update_velocity(p1);
		update_velocity(p2);
		update_velocity(p3);
		update_velocity(p4);

		// Since the axis is independent we look for when each start repeating
		if (!x_found && (start[0].x == p1.x && start[1].x == p2.x && start[2].x == p3.x && start[3].x == p4.x) &&
				(start[0].v.x == p1.v.x && start[1].v.x == p2.v.x && start[2].v.x == p3.v.x && start[3].v.x == p4.v.x)){
			xr = ts+1;
			x_found = true;
		}
		if (!y_found && (start[0].y == p1.y && start[1].y == p2.y && start[2].y == p3.y && start[3].y == p4.y) &&
				(start[0].v.y == p1.v.y && start[1].v.y == p2.v.y && start[2].v.y == p3.v.y && start[3].v.y == p4.v.y)){
			yr = ts+1;
			y_found = true;
		}
		if (!z_found && (start[0].z == p1.z && start[1].z == p2.z && start[2].z == p3.z && start[3].z == p4.z) &&
				(start[0].v.z == p1.v.z && start[1].v.z == p2.v.z && start[2].v.z == p3.v.z && start[3].v.z == p4.v.z)){
			zr = ts+1;
			z_found = true;
		}
		if (x_found && y_found && z_found){
			break;
		}
	}
	// from when they are repeating we find the least common multiple
	// e.g. when will all axis start a new period at the same time
	llint gcd1 = gcd(xr,yr);
	llint lcm1 = xr*yr/gcd1;
	llint gcd2 = gcd(lcm1,zr);
	llint lcm2 = zr*lcm1/gcd2;
	cout << "Star 2: " << lcm2 << endl;
}

int main()
{
	Planet p1 = {-9, 10, -1};
	Planet p2 = {-14, -8, 14};
	Planet p3 = {1, 5, 6};
	Planet p4 = {-19, 7, 8};
	//Debug 1
	/*
	p1 = {-1, 0, 2};
	p2 = {2, -10,-7};
	p3 = {4,-8, 8};
	p4 = {3, 5, -1};
	*/
	/*E = 179 (10 steps)
	Step = 2772
	*/
	task1(p1,p2,p3,p4);
	task2(p1,p2,p3,p4);
	return 0;
}
}//namespace day12