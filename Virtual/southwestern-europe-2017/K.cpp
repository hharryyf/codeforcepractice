#include <bits/stdc++.h>
const double Pi = acos(-1.0);
using namespace std;
const double eps = 1e-9;
int sgn(double x) {
	if (fabs(x) <= eps) return 0;
	if (x > 0) return 1;
	return -1;
}

struct point {
	double x, y;
	point(double x=0, double y=0) : x(x), y(y) {}
	point operator -(point other) {
		return point(x - other.x, y - other.y);
	}
	
	point operator +(point other) {
		return point(x + other.x, y + other.y);
	}
	
	bool operator < (point other) {
		if (x != other.x) return x < other.x;
		return y < other.y;
	}
	
	point operator *(double p) {
		return point(x*p, y*p);
	}
};

typedef point Vector;

struct segment {
	point v1, v2;
};

struct Line {
	point v, p;
    Line(point v, point p):v(v), p(p) {}
};

double Dot(Vector A, Vector B){
    return A.x*B.x + A.y*B.y;
}

double Cross(Vector A, Vector B){
    return A.x*B.y-A.y*B.x;
}

double Length(Vector A){
    return sqrt(Dot(A, A));
}

double DistanceToLine(point P, point A, point B){
    Vector v1 = B-A, v2 = P-A;
    return fabs(Cross(v1, v2)/Length(v1));
}

// line l1 and line l2 interection
vector<point> GetLineIntersection(Line l1, Line l2){
    vector<point> ret;
	point P = l1.v, Q = l2.v;
	Vector v = l1.p, w = l2.p;
	if (sgn(Cross(v, w)) == 0) return ret; 
	Vector u = P-Q;
    double t = Cross(w, u)/Cross(v, w);
    point pp = P+v*t;
	ret.push_back(pp);
	return ret;
}
// check whether p is on the segment a1, a2
// the second equal sign is added only if p is the same as a1/a2 is allowed
bool OnSegment(point p, point a1, point a2){
    return sgn(Cross(a1-p, a2-p)) == 0 && sgn(Dot(a1-p, a2-p)) <= 0;
}

bool cmp(point a, point b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cw(point a, point b, point c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw(point a, point b, point c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull(vector<point>& a) {
    if (a.size() == 1)
        return;

    sort(a.begin(), a.end(), &cmp);
    point p1 = a[0], p2 = a.back();
    vector<point> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)a.size(); i++) {
        if (i == (int) a.size() - 1 || cw(p1, a[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == (int) a.size() - 1 || ccw(p1, a[i], p2)) {
            while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    a.clear();
    for (int i = 0; i < (int)up.size(); i++)
        a.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        a.push_back(down[i]);
}

int N, R;
vector<point> pt;

int main() {
    int i;
    double ans = 1e18;
    scanf("%d%d", &N, &R);
    for (i = 1; i <= N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        pt.push_back(point(u, v));
    }

    convex_hull(pt);
    if ((int) pt.size() <= 2) {
        printf("%.16lf\n", 0.0);
        return 0;
    }

    int sz = pt.size(), q = 1;
    pt.push_back(pt[0]);
    for (i = 0 ; i < sz; ++i) {
        while(fabs(Cross(pt[i+1] - pt[i],pt[q] - pt[i])) < fabs(Cross(pt[i+1] - pt[i], pt[q+1] - pt[i]))){
            q = (q + 1) % sz;
        }
        
        double tmp = DistanceToLine(pt[q], pt[i], pt[i+1]);
        ans = min(ans,tmp);
    }

    printf("%.16lf\n", ans);
    return 0;
}

