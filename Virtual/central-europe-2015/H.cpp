#include <bits/stdc++.h>
#define MAX_SIZE 500011
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

double area(const vector<point>& fig) {
    double res = 0;
    for (unsigned i = 0; i < fig.size(); i++) {
        point p = i ? fig[i - 1] : fig.back();
        point q = fig[i];
        res += (p.x - q.x) * (p.y + q.y);
    }
    return fabs(res) / 2;
}

segment seg[4];
point pt[4];

double solve_1() {
	int i;
	vector<point> curr;
	for (i = 0 ; i < 4; ++i) {
		if (pt[i].x >= 0.5) curr.push_back(pt[i]);
	}

	Line l = Line(point(0.5, 0.5), point(0, 1));
	for (i = 0 ; i < 4; ++i) {
		vector<point> itc = GetLineIntersection(l, Line(seg[i].v1, seg[i].v2 - seg[i].v1));
		if (itc.empty()) continue;
		if (OnSegment(itc[0], seg[i].v1, seg[i].v2)) {
			curr.push_back(itc[0]);
		}
	}

	convex_hull(curr);
	/*for (auto p : curr) {
		cout << p.x << " " << p.y << endl;
	}*/
	return area(curr);
}

double solve_3() {
	int i;
	vector<point> curr;
	for (i = 0 ; i < 4; ++i) {
		if (pt[i].y >= 0.5) curr.push_back(pt[i]);
	}

	Line l = Line(point(0.5, 0.5), point(1, 0));
	for (i = 0 ; i < 4; ++i) {
		vector<point> itc = GetLineIntersection(l, Line(seg[i].v1, seg[i].v2 - seg[i].v1));
		if (itc.empty()) continue;
		if (OnSegment(itc[0], seg[i].v1, seg[i].v2)) {
			curr.push_back(itc[0]);
		}
	}

	convex_hull(curr);
	return area(curr);
}

double solve_4() {
	int i;
	vector<point> curr;
	for (i = 0 ; i < 4; ++i) {
		if (pt[i].y <= -0.5) curr.push_back(pt[i]);
	}

	Line l = Line(point(-0.5, -0.5), point(1, 0));
	for (i = 0 ; i < 4; ++i) {
		vector<point> itc = GetLineIntersection(l, Line(seg[i].v1, seg[i].v2 - seg[i].v1));
		if (itc.empty()) continue;
		if (OnSegment(itc[0], seg[i].v1, seg[i].v2)) {
			curr.push_back(itc[0]);
		}
	}

	convex_hull(curr);
	return area(curr);
}

double solve_6() {
	int i;
	vector<point> curr;
	for (i = 0 ; i < 4; ++i) {
		if (pt[i].x <= -0.5) curr.push_back(pt[i]);
	}

	Line l = Line(point(-0.5, -0.5), point(0, 1));
	for (i = 0 ; i < 4; ++i) {
		vector<point> itc = GetLineIntersection(l, Line(seg[i].v1, seg[i].v2 - seg[i].v1));
		if (itc.empty()) continue;
		if (OnSegment(itc[0], seg[i].v1, seg[i].v2)) {
			curr.push_back(itc[0]);
		}
	}

	convex_hull(curr);
	return area(curr);
}



int main() {
	int i;
	double ans = 4.0 * 5.0 * 5.0 * 5.0 / 124.0;
	for (i = 0 ; i < 4; ++i) scanf("%lf%lf", &pt[i].x, &pt[i].y);
	for (i = 0 ; i < 4; ++i) {
		seg[i].v1 = pt[i], seg[i].v2 = pt[(i + 1) % 4];
	}

	ans = ans + solve_1() * 3.0 * 5.0 / 124.0;
	// cout << solve_1() << endl;
	ans = ans + solve_6() * 4.0 * 5.0 / 124.0;
	ans = ans + solve_3() * 6.0 * 5.0 / 124.0;
	ans = ans + solve_4() * 1.0 * 5.0 / 124.0;
	printf("%.10lf\n", ans);
	return 0;
}