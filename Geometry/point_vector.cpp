#include <bits/stdc++.h>

using namespace std;

struct Point{
    double x, y;
    Point(double x = 0, double y = 0):x(x),y(y){}
};

typedef Point Vector;

Vector operator + (Vector A, Vector B){
    return Vector(A.x+B.x, A.y+B.y);
}

Vector operator - (Point A, Point B){
    return Vector(A.x-B.x, A.y-B.y);
}

Vector operator * (Vector A, double p){
    return Vector(A.x*p, A.y*p);
}

Vector operator / (Vector A, double p){
    return Vector(A.x/p, A.y/p);
}

bool operator < (const Point& a, const Point& b){
    if(a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

const double eps = 1e-6;

int sgn(double x){
    if(fabs(x) < eps)
        return 0;
    if(x < 0)
        return -1;
    return 1;
}

bool operator == (const Point& a, const Point& b){
    if(sgn(a.x-b.x) == 0 && sgn(a.y-b.y) == 0)
        return true;
    return false;
}

double Dot(Vector A, Vector B){
    return A.x*B.x + A.y*B.y;
}

double Length(Vector A){
    return sqrt(Dot(A, A));
}

double Angle(Vector A, Vector B){
    return acos(Dot(A, B)/Length(A)/Length(B));
}

double Cross(Vector A, Vector B){
    return A.x*B.y-A.y*B.x;
}

double Area2(Point A, Point B, Point C){
    return Cross(B-A, C-A);
}

Vector Rotate(Vector A, double rad){ // rotation anti-clockwise with rad
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}

Vector Normal(Vector A){ // left rotation 90 degree
    double L = Length(A);
    return Vector(-A.y/L, A.x/L);
}

bool ToLeftTest(Point a, Point b, Point c){
    return Cross(b - a, c - b) > 0;
}

struct Line{//直线定义
    Point v, p;
    Line(Point v, Point p):v(v), p(p) {}
    Point point(double t){//返回点P = v + (p - v)*t
        return v + (p - v)*t;
    }
};
//计算两直线交点
//调用前需保证 Cross(v, w) != 0
Point GetLineIntersection(Point P, Vector v, Point Q, Vector w){
    Vector u = P-Q;
    double t = Cross(w, u)/Cross(v, w);
    return P+v*t;
}
//点P到直线AB距离公式
double DistanceToLine(Point P, Point A, Point B){
    Vector v1 = B-A, v2 = P-A;
    return fabs(Cross(v1, v2)/Length(v1));
}//不去绝对值，得到的是有向距离
//点P到线段AB距离公式
double DistanceToSegment(Point P, Point A, Point B){
    if(A == B)
        return Length(P-A);
    Vector v1 = B-A, v2 = P-A, v3 = P-B;
    if(dcmp(Dot(v1, v2)) < 0)
        return Length(v2);
    if(dcmp(Dot(v1, v3)) > 0)
        return Length(v3);
    return DistanceToLine(P, A, B);
}
//点P在直线AB上的投影点
Point GetLineProjection(Point P, Point A, Point B){
    Vector v = B-A;
    return A+v*(Dot(v, P-A)/Dot(v, v));
}
//判断p点是否在线段a1a2上
bool OnSegment(Point p, Point a1, Point a2){
    return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}
//判断两线段是否相交
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2){
    double c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1);
    double c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);
    //if判断控制是否允许线段在端点处相交，根据需要添加
    if(!sgn(c1) || !sgn(c2) || !sgn(c3) || !sgn(c4)){
        bool f1 = OnSegment(b1, a1, a2);
        bool f2 = OnSegment(b2, a1, a2);
        bool f3 = OnSegment(a1, b1, b2);
        bool f4 = OnSegment(a2, b1, b2);
        bool f = (f1|f2|f3|f4);
        return f;
    }
    return (sgn(c1)*sgn(c2) < 0 && sgn(c3)*sgn(c4) < 0);
}

int main() {
	
	return 0;
}