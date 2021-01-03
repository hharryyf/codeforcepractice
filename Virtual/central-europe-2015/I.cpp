#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-9;
int cnt[504][504][11];
int pre[504][504][11];
int N;

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

double Length(Vector A){
    return sqrt(Dot(A, A));
}

double Angle(Vector A, Vector B){
    return acos(Dot(A, B)/Length(A)/Length(B));
}

double Cross(Vector A, Vector B){
    return A.x*B.y-A.y*B.x;
}

double DistanceToLine(point P, point A, point B){
    Vector v1 = B-A, v2 = P-A;
    return fabs(Cross(v1, v2)/Length(v1));
}

double DistanceToSegment(point P, point A, point B){
    Vector v1 = B-A, v2 = P-A, v3 = P-B;
    if(sgn(Dot(v1, v2)) < 0)
        return Length(v2);
    if(sgn(Dot(v1, v3)) > 0)
        return Length(v3);
    return DistanceToLine(P, A, B);
}

int main() {
	int i;
	scanf("%d", &N);
	for (i = 1; i <= N; ++i) {
		int x, y;
		double r;
		scanf("%d%d%lf", &x, &y, &r);
		int cid = round(r * 10.0);
		cnt[x][y][cid]++;
	}


	for (i = 1; i <= 500; ++i) {
		for (int j = 1; j <= 500; ++j) {
			for (int k = 0; k <= 10; ++k) {
				if (k > 0)
					pre[i][j][k] += pre[i][j][k-1];
				pre[i][j][k] += cnt[i][j][k];
			}
		}
	}
	int Q;
	scanf("%d", &Q);
	while (Q-- > 0) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (x1 > x2) {
			swap(x1, x2);
			swap(y1, y2);
		}
		int ret = 0;

		if (x1 == x2) {
			if (y1 > y2) swap(y1, y2);
			for (i = y1; i <= y2; ++i) {
				ret = ret + pre[x1][i][10];		
			}

			printf("%d\n", ret);
			continue;
		}

		Line l = Line(point(x1, y1), point(x2, y2) - point(x1, y1));
		l.p.y /= l.p.x;
		l.p.x = 1;
		
		for (i = x1; i <= x2; ++i) {
			point down = l.v + point(l.p.x * (i - x1 - 1), l.p.y * (i - x1 - 1));
			point up = l.v + point(l.p.x * (i - x1 + 1), l.p.y * (i - x1 + 1));
			int lowy = floor(down.y), upy = ceil(up.y);
			if (lowy > upy) swap(lowy, upy);
			lowy--, upy++;
			for (int j = lowy; j <= upy; ++j) {
				if (j < 0 || j > 500) continue;
				double d = DistanceToSegment(point(i, j), point(x1, y1), point(x2, y2));
				// cout << "(" << i << ", " << j << ")" << " = " << d << endl;
				if (sgn(d - 1.0) > 0) continue;
				int cid = ceil((d - eps) * 10);
				ret = ret + pre[i][j][10] - (cid > 0 ? pre[i][j][cid - 1] : 0);
			}
		}

		printf("%d\n", ret);
	}
	return 0;
}