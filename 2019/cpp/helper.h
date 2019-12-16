#ifndef helper_h
#include <iostream>

typedef long long int llint;
namespace helper{
	struct Point {
		int x;
		int y;
	};
	inline bool operator==(const Point& p1, const Point& p2) {
		return (p1.x==p2.x && p1.y == p2.y);
	}
	inline bool operator!=(const Point& p1, const Point& p2) {
		return !(p1==p2);
	}
	inline bool operator<(const Point& p1, const Point& p2) {
		std::pair<int,int> pair1(p1.x, p1.y);
		std::pair<int,int> pair2(p2.x, p2.y);
		return pair1 < pair2;
	}
	inline Point operator+(const Point& p1, const Point& p2) {
		Point p3 = {p1.x+p2.x, p1.y+p2.y};
		return p3;
	}
	inline Point operator-(const Point& p1, const Point& p2) {
		Point p3 = {p1.x-p2.x, p1.y-p2.y};
		return p3;
	}
	inline Point operator*(const int& c, const Point& p2){
		return {c*p2.x, c*p2.y};
	}
	inline std::ostream &operator<<(std::ostream &os, const Point& p) { 
	    return os << p.x << ',' << p.y;
	}
}//helper

class Direction{
public:
	enum Directions{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};
	Direction(Directions d){
		this->d = d;
	}
	void turn_left();
	void turn_right();
	const Directions get_direction() {return this->d;};
	const helper::Point get_point_direction();
private:
	Directions d;
};

#endif //helper_h