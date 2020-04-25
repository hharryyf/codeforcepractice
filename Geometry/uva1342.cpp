#include <bits/stdc++.h>
#define MAX_SIZE 311
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

point pt[MAX_SIZE];
segment li[MAX_SIZE];
// all the intersection points on the ith segment
vector<point> g[MAX_SIZE];
vector<point> ap;

// unique the point vector vc
void disc(vector<point> &vc) {
	int i, sz = (int) vc.size();
	vector<point> ret;
	sort(vc.begin(), vc.end());
	for (i = 0; i < sz; ++i) {
		if (i == 0) {
			ret.push_back(vc[i]);
		} else {
			if (sgn(vc[i].x - vc[i-1].x) != 0 || sgn(vc[i].y - vc[i-1].y) != 0) {
				ret.push_back(vc[i]);
			}
		}
	}
	vc = ret;
}
// calculate the intersection of 2 segments
vector<point> Intersection(segment l1, segment l2) {
	Line L1 = Line(l1.v1, l1.v2-l1.v1);
	Line L2 = Line(l2.v1, l2.v2-l2.v1);
	auto ret = GetLineIntersection(L1, L2);
	if (ret.empty()) return ret;
	if (!OnSegment(ret[0], l1.v1, l1.v2) || !OnSegment(ret[0], l2.v1, l2.v2)) {
		return vector<point>();
	}
	return ret;
}

int main() {
	int T = 1;
	int n, i, j;
	while (scanf("%d", &n) != EOF) {
		int V = 0, E = 0;
		if (n == 0) break;
		ap.clear();
		for (i = 0; i <= n; ++i) g[i].clear();
		for (i = 1; i <= n; ++i) {
			scanf("%lf%lf", &pt[i].x, &pt[i].y);
			if (i > 1) {
				li[i-1].v1 = pt[i-1];
				li[i-1].v2 = pt[i];
				g[i-1].push_back(pt[i-1]);
				g[i-1].push_back(pt[i]);
			}
			ap.push_back(pt[i]);
		}
		
		for (i = 1; i <= n-1; ++i) {
			for (j = i + 1; j <= n-1; ++j) {
				// calculate the intersection points
				// of line li[i-1] and li[i]
				// return a vector<point>
				auto ret = Intersection(li[i], li[j]);
				for (auto r : ret) {
					ap.push_back(r);
					g[i].push_back(r);
					g[j].push_back(r);
				}
			}
		}

		disc(ap);
		V = (int) ap.size();
		for (i = 1; i <= n - 1; ++i) {
			disc(g[i]);
			E += (int) g[i].size();
			E -= 1;
		}
		
		// Euler's formula V-E + R = 2
		// R = E + 2 - V
		printf("Case %d: There are %d pieces.\n", T, E + 2 - V);
		++T;
	}
	return 0;
}
