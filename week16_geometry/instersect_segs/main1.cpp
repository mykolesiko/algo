#include <iostream>
#include <math.h>

#define EPS 0.000000000001

using namespace std;

class Point {

    public:
        double x,y;
        Point(double x_ = 0, double y_ = 0): x(x_), y(y_) {};
        bool operator==(const Point& p) {
           return ((fabs(p.x - x) < EPS) && (fabs(p.y - y) < EPS));
        }


        friend std::istream& operator>>(std::istream &in, Point& p) {
            double x_, y_;
            in >> x_ >> y_;
            p.x = x_;
            p.y = y_;
            return in;
        }
        
};


class Vector {
    public:

        Point p1, p2;
        double x, y;
        Vector(Point p1_, Point p2_): p1(p1_), p2(p2_) {
            x = p2.x - p1.x;
            y = p2.y - p1.y;
        };
        /*Vector(Segment& seg) {
            p1 = seg.p1;
            p2 = seg.p2;                
            x = p2.x - p1.x;
            y = p2.y - p1.y;
        };*/
        
        
        double operator*(const Vector& vec2) {
            double dp = 0;
            dp = x * vec2.x + y * vec2.y;
            return (dp);
        }

        double operator%(const Vector& vec2) {
            double dp = 0;
            dp = x * vec2.y - vec2.x * y;
            return (dp);
        }
        double getAngle(const Vector& vec) {
            return (atan2((*this) % vec, (*this) * vec));
        }
};


class Segment {
    public:
        
        Point p1, p2;
        Segment(Point p1_={0, 0}, Point p2_= {0, 0}): p1(p1_), p2(p2_) {};

        bool includes(Point p) {
            Vector vec1(p1, p), vec2(p2, p);
            if ((p1 == p) || (p2 == p)) return true;
            if (fabs(vec1 % vec2) > EPS) return false;
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

        bool operator^(Segment& seg) {
            
            Vector vec1(p1, p2);
            Vector vec2(seg.p1, seg.p2);
            Vector vec11(p1, seg.p1), vec12(p1, seg.p2);
            Vector vec21(seg.p1, p1), vec22(seg.p1, p2);
            //double angle1 = vec1.getAngle(vec11);
            //double angle2 = vec1.getAngle(vec12);
            double angle1 = vec1 % vec11;
            double angle2 = vec1 % vec12;
            
            if (fabs(angle1 * angle2) < EPS) {
               if ((this->includes(seg.p1)) || (this->includes(seg.p2))) {
                   return true;
               } else {
                   return false;
               }
            } else if  (angle1 * angle2 < 0)  {
                double angle1 = vec2 % vec21;
                double angle2 = vec2 % vec22;
            
                if ((angle1 * angle2) < EPS) {
                    return (true);
                }
            }
            return false;
        }
};





int main() {
    Segment seg1, seg2;
    cin >> seg1 >> seg2;
    if (seg1^seg2) {
        cout << "YES";
    } else {
        cout << "NO";
    }
        
    return (0);
}