#include <iostream>
#include <math.h>
#include <vector>

#define EPS 1


using namespace std;

class Point {

    public:
        long long x,y;
        Point(long long x_ = 0, long long y_ = 0): x(x_), y(y_) {};
        bool operator==(const Point& p) {
           return ((p.x == x) && (p.y == y));
        }


        friend std::istream& operator>>(std::istream &in, Point& p) {
            long long x_, y_;
            in >> x_ >> y_;
            p.x = x_;
            p.y = y_;
            return in;
        }
        
};


class Vector {
    public:

        Point p1, p2;
        long long x, y;
        Vector(Point p1_, Point p2_): p1(p1_), p2(p2_) {
            x = p2.x - p1.x;
            y = p2.y - p1.y;
        };
        
        
        long long operator*(const Vector& vec2) {
            long long dp = 0;
            dp = x * vec2.x + y * vec2.y;
            return (dp);
        }

        long long operator%(const Vector& vec2) {
            long long dp = 0;
            dp = x * vec2.y - vec2.x * y;
            return (dp);
        }
        double getAngle(const Vector& vec) {
            return (atan2(double((*this) % vec), double((*this) * vec)));
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

        
};


class Polygon  {
    public:
        Polygon(const vector<Point>& vertices_);
        Polygon() {};

        friend std::istream& operator>>(std::istream &in, Polygon& pol) {
            Point p;
            while (cin >> p) {
                pol.vertices.push_back(p);    
                //cout << p;
            }
            return in;
        }



        
        vector<Point> vertices;
       
        bool includes(Point p) {
            double sum = 0;
            for (int i = 0; i < vertices.size(); i++) {
                int ind1 = i % vertices.size();
                int ind2 = (i + 1) % vertices.size();
                Vector vec1(p, vertices[ind1]);
                Vector vec2(p, vertices[ind2]);
                Segment seg(vertices[ind1], vertices[ind2]);
                if (seg.includes(p)) return true;
                double ang = vec1.getAngle(vec2);
                sum += ang;
                
            }
           // cout << sum;

            if (fabs(sum) < EPS) return false;
            return true;
        }
};

int main() {
    Point p;
    int N;
    cin >> N;
    cin >> p;
    Polygon pol;
    cin >> pol;
    //cout << "end\n";
    if (pol.includes(p)) {
        cout << "YES";
    } else {
        cout << "NO";
    }
        
    return (0);
}