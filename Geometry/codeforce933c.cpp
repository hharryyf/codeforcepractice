#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

const double eps = 1e-9;

struct point {
	double x, y;
	bool operator < (point other) const {
		if (x != other.x) return x < other.x;
		return y < other.y;
	}
};

struct circle {
	double x, y, r;
};

// each circle the on its arc
vector<point> g[MAX_SIZE];
circle c[MAX_SIZE];
vector<point> pt;

int sgn(double x) {
	if (fabs(x) <= eps) return 0;
	if (x > 0) return 1;
	return -1;
}

int dcmp(double d1, double d2) {
	return sgn(d1-d2);
}

point operator -(point x, point y) {
	return point{x.x-y.x, x.y-y.y};
}

double length(point x) {
	return sqrt(x.x * x.x + x.y * x.y);
}

double dist(point x, point y) {
	return length(x-y);
}

bool intersect(circle c1, circle c2) {
	double d = dist(point{c1.x, c1.y}, point{c2.x, c2.y});
	double d1 = c1.r + c2.r, d2 = fabs(c1.r - c2.r);
	return dcmp(d, d1) <= 0 && dcmp(d, d2) >= 0;
}

void disc(vector<point> &vc) {
	int i;
	vector<point> ret;
	for (i = 0 ; i < (int) vc.size(); ++i) {
		if (i == 0) {
			ret.push_back(vc[i]);
		} else if (dcmp(vc[i].x, vc[i-1].x) != 0 || dcmp(vc[i].y, vc[i-1].y) != 0){
			ret.push_back(vc[i]);
		}
	}
	vc = ret;
}

int f[MAX_SIZE];

int find(int x) {
	if (x == f[x]) return x;
	return f[x] = find(f[x]);
}

void unionset(int a, int b) {
	int x = find(a), y = find(b);
	f[x] = y;
}

// intersection of circle c with line Ax + By + C = 0
vector<point> linecircle(circle cr, double A, double B, double C) {
	vector<point> ret;
	double r = cr.r, a = A, b = B, c = C + A * cr.x + B * cr.y; 
	double x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);
	if (sgn(c * c - r * r * (a*a + b*b)) > 0) {
		return ret;
	} else if (sgn(c*c - r*r*(a*a+b*b)) == 0) {
		ret.push_back(point{x0, y0});
	} else {
		double d = r*r - c*c/(a*a+b*b);
		double mult = sqrt (d / (a*a+b*b));
		double ax, ay, bx, by;
		ax = x0 + b * mult;
		bx = x0 - b * mult;
		ay = y0 - a * mult;
		by = y0 + a * mult;
		ret.push_back(point{ax, ay});
		ret.push_back(point{bx, by});
	}
	return ret;
}

vector<point> circleintersect(circle c1, circle c2) {
	// reduce the problem to
	// find the line Ax + By + C = 0 intersect with c1
	circle c;
	c.r = c1.r;
	c.x = 0, c.y = 0;
	c2.x = c2.x - c1.x;
	c2.y = c2.y - c1.y;
	double A = -2.0 * c2.x;
	double B = -2.0 * c2.y;
	double C = c2.x * c2.x + c2.y * c2.y + c1.r * c1.r - c2.r * c2.r;
	vector<point> ret = linecircle(c, A, B, C);
	for (auto &r : ret) {
		r.x += c1.x;
		r.y += c1.y;
	}
	return ret;
}

int main() {
	int i, j, n;
	int V = 0, E = 0, C = 0;
	scanf("%d", &n);
	C = n;
	for (i = 1; i <= n; ++i) {
		scanf("%lf%lf%lf", &c[i].x, &c[i].y, &c[i].r);
		f[i] = i;
	}
	
	for (i = 1; i <= n; ++i) {
		for (j = i + 1; j <= n; ++j) {
			if (intersect(c[i], c[j])) {
				// cout << i << " " << j << " intersect " << endl;
				// add code here to calculate the 2 intersection points of the circles
				// and append the points to the circle list
				if (find(i) != find(j)) {
					unionset(i, j);
					C--;
				}
				
				vector<point> ret = circleintersect(c[i], c[j]);
				for (auto r : ret) {
					g[i].push_back(r);
					g[j].push_back(r);
					pt.push_back(r);
					// cout << r.x << " " << r.y << endl;
				}
			}
		}
	}
	
	sort(pt.begin(), pt.end());
	disc(pt);
	
	V = (int) pt.size();
	
	for (i = 1; i <= n; ++i) {
		sort(g[i].begin(), g[i].end());
		disc(g[i]);
		E += (int) g[i].size();
	}
	
	// cout << C << " " << E << " " << V << endl;
	// Euler's formula general case
	printf("%d\n", C + 1 + E - V);
	return 0;
}