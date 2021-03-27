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
    double GetX() const
    {
        return this -> x;
    }
    double GetY() const
    {
        return this -> y;
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
class Segment
{
    friend bool Is_cross(Segment &A1, Segment &A2);
    friend bool Is_segment_parallel(Segment &A, Segment &B);
private:
    Point f;
    Point s;
public:
    explicit Segment(Point f, Point s)
    : f(f)
    , s(s)
    {

    }
    Segment(const Segment &copy)
    : f(copy.f)
    , s(copy.s)
    {

    }
    Segment& operator= (const Segment &segment)
    {
        this -> f = segment.f;
        this -> s = segment.s;
    }
};
bool Is_cross(Segment &A1, Segment &A2)
{

}
bool Is_segment_parallel(Segment &A, Segment &B)
{
    return abs(A.f.GetY() - A.s.GetY()) < 1e-7 || abs(B.f.GetY() - B.s.GetY()) < 1e-7 || (abs((A.f.GetX() - A.s.GetX()) / (A.f.GetY() - A.s.GetY()) - (B.f.GetX() - B.s.GetX()) / (B.f.GetY() - B.s.GetY())) < 1e-7);
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
    size_t get_size()
    {
        return this -> quantity_vertex;
    }
    Point* get_points()
    {
        return this -> points;
    }
};
class Closed_polyline : public Polyline
{
public:
    using Polyline::Polyline;
    Closed_polyline& operator=(const Polyline &other)
    {
        this->Polyline::operator=(other);
    }
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
    bool is_equal(const Point *p1, const Point *p2, size_t quantity) const
    {
        for(int i = 0; i < quantity; i++) if(p1[i] != p2[i]) return 0;
        return 1;
    }
public:
    explicit Polygon(Point *A, size_t quantity)
    {
        Closed_Polyline X(A, quantity);
        int t = 1;
        for(size_t i = 0; i < X.get_size(); i++)
        {
            Segment A1(X.get_points()[i], X.get_points()[(i+3)%X.get_size()]);
            Segment A2(X.get_points()[(i+1)%X.get_size()], X.get_points()[(i+2)%X.get_size()]);
            if(!Is_cross(A1, A2)) t = 0;
        }
        for(size_t i = 0; i < X.get_size(); i++)
        {
            if(Is_3dots_on_line(X.get_points()[i], X.get_points()[(i+1)%X.get_size(), X.get_points()[(i+2)%X.get_size())) t = 0;
        }
        if(t)
        {
            vertex = new Point[3];
            Point v1(0, 0);
            Point v2(0, 1);
            Point v3(1, 0);
            vertex[0] = v1;
            vertex[1] = v2;
            vertex[2] = v3;
            quantity_vertex = 3;
        }
        else
        {
            quantity_vertex = X.get_size();
            vertex = X.get_points();
        }
    }
    Polygon(const Polygon &copy)
    {
        quantity_vertex = copy.quantity_vertex;
        vertex = new Point[quantity_vertex];
        for(int i = 0; i < copy.quantity_vertex; i++)
        {
            vertex[i] = copy.vertex[i];
        }
    }
    Polygon& operator=(const Polygon &other)
    {
        if(this == &other)
        {
            return *this;
        }
        delete[] vertex;
        quantity_vertex = other.quantity_vertex;
        vertex = new Point[quantity_vertex];
        for(int i = 0; i < other.quantity_vertex; i++)
        {
            vertex[i] = other.vertex[i];
        }
    }
    bool operator!= (const Polygon &other) const
    {
        return quantity_vertex != other.quantity_vertex || !is_equal(vertex, other.vertex, quantity_vertex);
    }
    bool operator== (const Polygon &other) const
    {
        return quantity_vertex == other.quantity_vertex && is_equal(vertex, other.vertex, quantity_vertex);
    }
    double perimeter() const
    {
        double p = 0;
        for(int i = 1; i < quantity_vertex; i++) p += Length(vertex[i], vertex[i-1]);
        p += Length(vertex[0], vertex[quantity_vertex - 1])
        return p;
    }
    double square() const
    {
        double s = 0;
        for(int i = 0; i < quantity_vertex; i++) s += GetX(vertex[i]) * GetY(vertex[(i+1) % quantity_vertex]);
        for(int i = 0; i < quantity_vertex; i++) s -= GetY(vertex[i]) * GetX(vertex[(i+1) % quantity_vertex]);
        s = abs(s);
        s /= 2;
        return s;
    }
    ~Polygon()
    {
        delete[] vertex;
    }
    size_t get_size()
    {
        return this -> quantity_vertex;
    }
    Point* get_vertex()
    {
        return this -> vertex;
    }
};
class Right_Polygon
{
protected:
    Point centre;
    Point vertex;
    int quantity;
public:
    explicit Right_Polygon(Point C, Point V, int q)
    {
        if(C == V)
        {
            Point V1(C.GetX(), C.GetY() + 1);
            V = V1;
        }
        if(q < 3) q = 3;
        quantity = q;
        centre = C;
        vertex = V;
    }
    Right_Polygon(const Right_Polygon &copy)
    {
        quantity = copy.quantity;
        centre = copy.centre;
        vertex = copy.vertex;
    }
    Right_Polygon& operator=(const Right_Polygon &other)
    {
        if(this == &other)
        {
            return *this;
        }
        vertex = other.vertex;
        centre = other.centre;
        quantity = other.quantity;
    }
    bool operator!= (const Right_Polygon &other) const
    {
        return quantity != other.quantity || centre != other.centre || vertex != other.vertex;
    }
    bool operator== (const Right_Polygon &other) const
    {
        return quantity == other.quantity && centre == other.centre && vertex == other.vertex;
    }
    double perimeter() const
    {
        double rad = Length(centre, vertex);
        double a = 2 * atan(1) * (quantity - 2) / quantity;
        return rad * cos(a) * 2 * quantity;
    }
    double square() const
    {
        double rad = Length(centre, vertex);
        double a = 2 * atan(1) * (quantity - 2) / quantity;
        return rad * cos(a) * rad * sin(a) * quantity;
    }
};
class Triangle : public Polygon
{
    using Polygon::Polygon;
    Triangle(Point *A, size_t quantity)
    {
        vertex = new Point[3];
        Point v1(0, 0);
        Point v2(0, 1);
        Point v3(1, 0);
        if(quantity == 3)
        {
            v1 = A[0];
            v2 = A[1];
            v3 = A[2];
        }
        vertex[0] = v1;
        vertex[1] = v2;
        vertex[2] = v3;
        quantity_vertex = 3;
    }
};
class Trapeze : public Polygon
{
    using Polygon::Polygon;
    Trapeze(Point *A, size_t quantity)
    {
        vertex = new Point[4];
        Point v1(0, 0);
        Point v2(1, 1);
        Point v3(2, 1);
        Point v4(3, 0);
        Segment s1(A[0], A[1]);
        Segment s2(A[1], A[2]);
        Segment s3(A[2], A[3]);
        Segment s4(A[3], A[0]);
        if(quantity == 4 && (Is_segment_parallel(s1, s3) ^ Is_segment_parallel(s2, s4)))
        {
            v1 = A[0];
            v2 = A[1];
            v3 = A[2];
            v4 = A[3];
        }
        vertex[0] = v1;
        vertex[1] = v2;
        vertex[2] = v3;
        vertex[3] = v4;
        quantity_vertex = 4;
    }
};
int main()
{
    Point A(1,2), B(2,3), C(4,4);
    Point *t = new Point[3];
    t[0] = A;
    t[1] = B;
    t[2] = C;
    Closed_polyline Y(t, 3);
    Polyline X(t, 3);
    cout << Y.perimeter();
}
