#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

const double eps = 1e-8;

struct point {
	double x, y;
};

point p1[MAX_SIZE], p2[MAX_SIZE];
double d1, d2;

int sgn(double x, double y) {
	if (fabs(x - y) <= eps) return 0;
	if (x > y) return 1;
	return -1;
}

double dist(point v, point u) {
	return (v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y);
}

int main() {
	int n;
	while (scanf("%d", &n) != EOF) {
		int i, cnt = 0;
		scanf("%lf%lf", &d1, &d2);
		for (i = 1; i <= n; ++i) {
			scanf("%lf%lf%lf%lf", &p1[i].x, &p1[i].y, &p2[i].x, &p2[i].y);
		}
		bool far = (sgn(dist(p1[1], p2[1]), d2 * d2) == 1);
		// cout << far << endl;
		for (i = 2; i <= n; ++i) {
				double a1 = dist(p1[i-1], p2[i-1]);
				double a2 = dist(p1[i], p2[i]);
				double x1 = p1[i-1].x, y1 = p1[i-1].y, x2 = p1[i].x, y2 = p1[i].y;
				double w1 = p2[i-1].x, z1 = p2[i-1].y, w2 = p2[i].x, z2 = p2[i].y;
				double k1 = x2 + w1 - x1 - w2;
				double k2 = y2 - y1 - z2 + z1;
				double b1 = x1 - w1;
				double b2 = y1 - z1;
				double a3 = 0;
				if (sgn(k1 * k1 + k2 * k2, 0) == 0) {
					a3 = min(a1, a2);
				} else {
					double t = -(b1 * k1 + b2 * k2) / (k1 * k1 + k2 * k2);
					//cout << t << endl;
					if (sgn(t, 1) <= 0 && sgn(t, 0) > 0) {
						a3 = (k1 * t + b1) * (k1 * t + b1) + (k2 * t + b2) * (k2 * t + b2);
					} else {
						a3 = min(a1, a2);
					}
				}
				
				// cout << "point " << i <<" " << a3 << endl;
				if (sgn(a3, d1 * d1) <= 0 || sgn(a1, d1 * d1) <= 0 || sgn(a2, d1 * d1) <= 0) {
					if (far || cnt == 0) {
						++cnt;
						far = false;
					}
				}
			
				far = far || (sgn(dist(p1[i], p2[i]), d2 * d2) == 1);
		}
		
		printf("%d\n", cnt);
	}
	return 0;
}
