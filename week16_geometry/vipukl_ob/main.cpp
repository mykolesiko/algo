#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;
#define EPS 1

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

        friend std::ostream& operator<<(std::ostream &out, Point& p) {
            out << p.x << " " <<  p.y << endl;
            return out;
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

        double length() {
            return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
        } 
        
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
            if ((p1 == p) || (p2 == p)) {
                return true;
            }
            if (p1 == p2) {
                return (false);
            }
            if (fabs(vec1 % vec2) > EPS) {
                return false;
            }
            if ((vec1 * vec2) < 0) {
                return true;
            }
            return false;
        }

        double length() {
            return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
        }

        friend std::istream& operator>>(std::istream &in, Segment& seg) {
            Point p1, p2;
            in >> p1 >> p2;
            seg.p1 = p1;
            seg.p2 = p2;
            return in;
        }
};


Point pLeftBottom;

bool compare(Point p1, Point p2) {
            Vector vec1(pLeftBottom, p1);
            Vector vec2(pLeftBottom, p2);
            long long dp = vec1 % vec2;
            if (dp < 0) return true;
            if  (dp == 0) {
                if (vec1.length() < vec2.length()) {
                    return true;
                } else {
                    return false;
                }
            }
            return (false);

}

class Polygon  {
    public:
        Polygon(const vector<Point>& vertices_) {
            vertices.assign(vertices_.begin(), vertices_.end());
        };
        Polygon() {};

        friend std::istream& operator>>(std::istream &in, Polygon& pol) {
            Point p, pprev;
            bool first = true;
            while (cin >> p) {
                if (!first) {
                    if (pprev == p) {
                        continue;
                    }
                }
                pol.vertices.push_back(p);    
                first = false;
                pprev = p;
            }
            return in;
        }

        friend std::ostream& operator<<(std::ostream &out, Polygon& pol) {
            for (auto el : pol.vertices) {
                cout << el.x << " " << el.y << endl;
            }
            return out;
        }

        vector<Point> vertices;
        
        double perimiter() {
            double sum = 0;
            for (int i = 0; i < vertices.size(); i++) {

                int next = (i + 1) % vertices.size();
                Segment seg(vertices[i], vertices[next]);

                double len = seg.length();
                sum +=len;
            }    
            return sum;
        }

        Polygon get_convex() {
            vector<Point> convex;
            long long y_min = vertices[0].y;
            long long x_min = vertices[0].x;
            int ind_min = 0;
            for (int i = 0; i < vertices.size(); i++) {
                if (vertices[i].y < y_min) {
                    ind_min = i;
                    y_min = vertices[i].y;
                    x_min = vertices[i].x;
                } else if (vertices[i].y == y_min) {
                    if (vertices[i].x < x_min) {
                        x_min = vertices[i].x;
                        ind_min = i;
                    }
                }

            }

            Point p0 = pLeftBottom = vertices[ind_min];
            vector<Point> polar;
            polar.assign(vertices.begin(), vertices.end());
            sort(polar.begin(), polar.end(), compare);
            Point p1 = polar[0];
            Point p2 = polar[1];
            convex.push_back(p1);
            convex.push_back(p2);
            for (int i = 2; i < polar.size(); i++) {
                Vector vec1(p1, p2);
                Point p3 = polar[i];
                Vector vec2(p2, p3);
                long long dp = vec1 % vec2;
                while (dp >= 0) {
                    convex.pop_back();
                    p2 = convex.back();
                    if (convex.size() == 1) {
                        break;
                    }
                    p1 = convex[convex.size() - 2]; 
                    vec1 = Vector(p1, p2);
                    vec2 = Vector(p2, p3);
                    dp = vec1 % vec2;
                }
                convex.push_back(p3);
                p2 = convex.back();
                p1 = convex[convex.size() - 2]; 
            }
            return Polygon(convex);
        }
};

int main() {
    Point p;
    int N;
    cin >> N;
    Polygon pol;
    cin >> pol;
    Polygon convex = pol.get_convex();       
    cout << convex.perimiter() << '\n';
    return (0);
}
