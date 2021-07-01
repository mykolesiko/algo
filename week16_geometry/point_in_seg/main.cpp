#include <iostream>
#include <math.h>
 
 
using namespace std;
 
using namespace std;
 
class Point {
 
    public:
        int x,y;
        Point(int x_ = 0, int y_ = 0): x(x_), y(y_) {};
        bool operator==(const Point& p) {
           return ((p.x == x) && (p.y == y));
        }
 
         friend std::istream& operator>>(std::istream &in, Point& p) {
            int x_, y_;
            in >> x_ >> y_;
            p.x = x_;
            p.y = y_;
            return in;
        }

};
  
class Vector {
    public:
 
        Point p1, p2;
        int x, y;
        Vector(Point p1_, Point p2_): p1(p1_), p2(p2_) {
            x = p2.x - p1.x;
            y = p2.y - p1.y;
        };
        
        int operator*(const Vector& vec2) {
            int dp = 0;
            dp = x * vec2.x + y * vec2.y;
            return (dp);
        }
 
        int operator%(const Vector& vec2) {
            int dp = 0;
            dp = x * vec2.y - vec2.x * y;
            return (dp);
        }
        
};
 
 class Segment {
    public:
        
        Point p1, p2;
        Segment(Point p1_={0, 0}, Point p2_= {0, 0}): p1(p1_), p2(p2_) {};
 
        bool includes(Point p) {
            Vector vec1(p1, p), vec2(p2, p);
            if ((p1 == p) || (p2 == p)) return true;
            if (p1 == p2) return (false);
            if (fabs(vec1 % vec2) != 0) return false;
            if ((vec1 * vec2) < 0) return true;
            return false;
        }
 
        friend std::istream& operator>>(std::istream &in, Segment& seg) {
            Point p1, p2;
            in >> p1 >> p2;
            seg.p1 = p1;
            seg.p2 = p2;
            return in;
        }
 
        
};
int main() {
    Point p;
    cin >> p;
    Segment seg;
    cin >> seg;
    if (seg.includes(p)) {
        cout << "YES";
    } else {
        cout << "NO";
    }
        
    return (0);
}