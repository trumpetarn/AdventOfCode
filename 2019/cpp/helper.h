#ifndef helper_h
#include <iostream>


struct Point {
	int x;
	int y;
};
bool operator==(const Point& p1, const Point& p2) {
	return (p1.x==p2.x && p1.y == p2.y);
}
bool operator!=(const Point& p1, const Point& p2) {
	return !(p1==p2);
}
bool operator<(const Point& p1, const Point& p2) {
	std::pair<int,int> pair1(p1.x, p1.y);
	std::pair<int,int> pair2(p2.x, p2.y);
	return pair1 < pair2;
}
Point operator+(const Point& p1, const Point& p2) {
	Point p3 = {p1.x+p2.x, p1.y+p2.y};
	return p3;
}
Point operator-(const Point& p1, const Point& p2) {
	Point p3 = {p1.x-p2.x, p1.y-p2.y};
	return p3;
}
Point operator*(const int& c, const Point& p2){
	return {c*p2.x, c*p2.y};
}
std::ostream &operator<<(std::ostream &os, const Point& p) { 
    return os << p.x << ',' << p.y;
}
#endif //helper_h