#include "helper.h"

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