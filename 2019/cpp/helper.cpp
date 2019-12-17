#include "helper.h"
#include <algorithm>
#include <iostream>

namespace helper{
	const void print_points(std::vector<Point> points){
		int min_x = 99999;
		int max_x = 0;
		int min_y = 99999;
		int max_y = 0;
		for (auto p : points){
			if (p.x < min_x)
				min_x = p.x;
			if (p.y < min_y)
				min_y = p.y;
			if (p.x > max_x)
				max_x = p.x;
			if (p.y > max_y)
				max_y = p.y;
		}
		for (int y=max_y; y>=min_y; y--){
			for (int x=min_x; x<=max_x; x++){
				Point q = {x,y};
				if (std::find(points.begin(),points.end(),q) != points.end()){
					std::cout << "\u2589";
				}else{
					std::cout << " ";
				}
			}
			std::cout << std::endl;
		}
		return;
	}
} //ns helper

void Direction::turn_left(){
	switch (d){
		case UP:
			d =LEFT;
			break;
		case RIGHT:
			d = UP;
			break;
		case DOWN:
			d = RIGHT;
			break;
		case LEFT:
			d = DOWN;
			break;
	}
}
void Direction::turn_right(){
	switch (d){
		case UP:
			d = RIGHT;
			break;
		case RIGHT:
			d = DOWN;
			break;
		case DOWN:
			d =LEFT;
			break;
		case LEFT:
			d = UP;
			break;
	}
}

const helper::Point Direction::get_point_direction(){
	helper::Point p;
	switch (d){
		case UP:
			p={0,1};
			break;
		case RIGHT:
			p={1,0};
			break;
		case DOWN:
			p={0,-1};
			break;
		case LEFT:
			p={-1,0};
			break;
	}
	return p;
}	