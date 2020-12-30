#include <bits/stdc++.h>
#define MAX_SIZE 42
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
    Line getperpendicular() {
        Line ret(0,0);
        ret.v = this->v;
        ret.p.x = this->p.y;
        ret.p.y = -this->p.x;
        return ret;
    }
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

point pt[MAX_SIZE];
vector<Line> line;
vector<point> itc;
int N;

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) scanf("%lf%lf", &pt[i].x, &pt[i].y);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j < i; ++j) {
            point mid = point((pt[i].x + pt[j].x) / 2, (pt[i].y + pt[j].y) / 2);
            point dir = point(pt[i].x - pt[j].x, pt[i].y - pt[j].y);
            Line l = Line(mid, dir);
            line.push_back(l.getperpendicular()); 
            itc.push_back(mid);
        }
    }

    int sz = line.size(), ans = N;
    for (i = 0; i < sz; ++i) {
        for (j = 0 ; j < i; ++j) {
            auto ret = GetLineIntersection(line[i], line[j]);
            if (!ret.empty()) {
                itc.push_back(ret.front());
            }
        }
    }

    for (i = 1; i <= N; ++i) itc.push_back(pt[i]);

    if (ans >= 2) ans--;
    for (auto p : itc) {
        vector<double> dist;
        for (i = 1; i <= N; ++i) {
            point np = point(pt[i].x - p.x, pt[i].y - p.y);
            dist.push_back(Dot(np, np));
        }

        sort(dist.begin(), dist.end());
        int cnt = 0;
        for (i = 0 ; i < (int) dist.size(); ++i) {
            if (i == 0 || sgn(dist[i] - dist[i-1]) != 0) ++cnt;
            // cout << dist[i] << " ";
        }

        // cout << endl;
        ans = min(ans, cnt);
    }

    printf("%d\n", ans);
    return 0;
}