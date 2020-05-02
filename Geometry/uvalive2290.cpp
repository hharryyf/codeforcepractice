#include <bits/stdc++.h>
#define MAX_SIZE 10005
using namespace std;

const double eps = 1e-9;

struct point {
	double x, y;
	point(double x = 0, double y = 0):x(x),y(y){}
	point operator - (point B) const {
    	return point(x-B.x, y-B.y);
	}
	double operator ^ (point B) const {
		return x * B.y - y * B.x;
	}
};



double Dot(point A, point B){
    return A.x*B.x + A.y*B.y;
}

double dist(point p1, point p2) {
	return sqrt(Dot(p2-p1, p2-p1));
}

double mul(point p0, point p1, point p2) {
	return (p1 - p0) ^ (p2 - p0);
}

int sgn(double x) {
	if (x > eps) return 1;
	if (x < -eps) return -1;
	return 0;
}

double r;
point pt[MAX_SIZE];

int main() {
	int n, i, j;
	while (scanf("%lf%lf%lf", &pt[0].x, &pt[0].y, &r) != EOF) {
		if (r < 0) break;
		scanf("%d", &n);
		for (i = 1 ; i <= n; ++i) {
			scanf("%lf%lf", &pt[i].x, &pt[i].y);
		}
		
		int ans = 0;
		for (i = 1; i <= n; ++i) {
			int cnt = 0;
			
			for (j = 1; j <= n; ++j) {
				if (sgn(dist(pt[j], pt[0]) - r) != 1) {
					if (sgn(mul(pt[0], pt[i], pt[j])) != -1) {
						++cnt;
					}
				}
			}
			ans = max(ans, cnt);
		}
		
		printf("%d\n", ans);
	}
	return 0;
}