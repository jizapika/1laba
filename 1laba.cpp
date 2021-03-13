#include <bits/stdc++.h>
using namespace std;

class Point
{
    friend bool Is_3dots_on_line(Point &A, Point &B, Point &C);
    friend double Length(Point &A, Point &B);
private:
    double x;
    double y;
public:
    void PrintX() const
    {
        cout << this -> x;
    }
    void PrintY() const
    {
        cout << this -> y;
    }
    explicit Point(double x = 0, double y = 0)
    : x(x)
    , y(y)
    {

    }
    Point(const Point &copy)
    : x(copy.x)
    , y(copy.y)
    {

    }
    Point& operator= (const Point &point)
    {
        this -> x = point.x;
        this -> y = point.y;
    }
    bool operator!= (const Point &point) const
    {
        return (this -> x != point.x) || (this -> y != point.y);
    }
    bool operator== (const Point &point) const
    {
        return (this -> x == point.x) && (this -> y == point.y);
    }
};
bool Is_3dots_on_line(Point &A, Point &B, Point &C)
{
    return abs((A.x - B.x) * (C.y - B.y) - (A.y - B.y) * (C.x - B.x)) < 1e-8;
}
double Length(Point &A, Point &B)
{
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}
class Polyline
{
protected:
    Point *points;
    size_t quantity_vertex;
    bool is_equal(const Point *p1, const Point *p2, size_t quantity) const
    {
        for(int i = 0; i < quantity; i++) if(p1[i] != p2[i]) return 0;
        return 1;
    }
public:
    Polyline(Point *A, size_t quantity)
    {
        quantity_vertex = 1;
        for(int i = 1; i < quantity; i++) if(A[i] != A[i-1]) quantity_vertex++;
        points = new Point[quantity_vertex];
        int this_iterator = 0, other_iterator = 0;
        points[this_iterator] = A[other_iterator];
        for(other_iterator = 1; other_iterator < quantity; other_iterator++)
        {
            if(A[other_iterator - 1] != A[other_iterator])
            {
                this_iterator++;
                points[this_iterator] = A[other_iterator];
            }
        }
    }
    Polyline(const Polyline &copy)
    {
        quantity_vertex = copy.quantity_vertex;
        points = new Point[quantity_vertex];
        for(int i = 0; i < copy.quantity_vertex; i++)
        {
            points[i] = copy.points[i];
        }
    }
    Polyline& operator=(const Polyline &other)
    {
        if(this == &other)
        {
            return *this;
        }
        delete[] points;
        quantity_vertex = other.quantity_vertex;
        points = new Point[quantity_vertex];
        for(int i = 0; i < other.quantity_vertex; i++)
        {
            points[i] = other.points[i];
        }
    }
    bool operator!= (const Polyline &other) const
    {
        return quantity_vertex != other.quantity_vertex || !is_equal(points, other.points, quantity_vertex);
    }
    bool operator== (const Polyline &other) const
    {
        return quantity_vertex == other.quantity_vertex && is_equal(points, other.points, quantity_vertex);
    }
    double perimeter() const
    {
        double p = 0;
        for(int i = 1; i < quantity_vertex; i++) p += Length(points[i], points[i-1]);
        return p;
    }
    ~Polyline()
    {
        delete[] points;
    }
};
class Closed_polyline : public Polyline
{
public:
  /*  Closed_polyline& operator=(const Polyline &other)
    {
        delete[] points;
        quantity_vertex = other.quantity_vertex;
        points = new Point[quantity_vertex];
        for(int i = 0; i < other.quantity_vertex; i++)
        {
            points[i] = other.points[i];
        }
    }*/
    double perimeter() const
    {
        double p = 0;
        for(int i = 0; i < quantity_vertex; i++) p += Length(points[i], points[i-1]);
        p += Length(points[0], points[quantity_vertex - 1]);
        return p;
    }
};
class Polygon
{
private:
    Point *vertex;
    size_t quantity_vertex;
public:

};
int main()
{
    Point A(1,2), B(2,3), C(4,4);
    Point *t = new Point[3];
    t[0] = A;
    t[1] = B;
    t[2] = C;
    Polyline X(t, 3);
    Closed_polyline Y(t, 3);
    cout << Y.perimeter();
}
