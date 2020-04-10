#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

struct point {
	double x, y;
};

point pt[MAX_SIZE];
int n;

bool valid(double mid) {
	double l = -1e8, r = 1e8;
	int i;
	for (i = 1; i <= n; ++i) {
		if (pt[i].y < 0) pt[i].y = -pt[i].y;
		double dy = (pt[i].y - mid) * (pt[i].y - mid);
		if (dy > mid * mid) return false;
		double dx = sqrt(2 * mid * pt[i].y - pt[i].y * pt[i].y);
		l = max(l, pt[i].x - dx);
		r = min(r, pt[i].x + dx);
	}
	
	return r >= l;
}

int main() {
	double low = 0.0, high = 1e14;
	int i;
	bool haspos = false, hasneg = false;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%lf%lf", &pt[i].x, &pt[i].y);
		haspos |= (pt[i].y > 0);
		hasneg |= (pt[i].y < 0);
	}
	
	if (haspos && hasneg) {
		printf("-1\n");
		return 0;
	}
	double ans = 0.0;
	for (i = 0 ; i < 90; ++i) {
		double mid = 0.5 * (low + high);
		if (valid(mid)) {
			ans = mid;
			high = mid;
		} else {
			low = mid;
		}
	}
	
	printf("%.7lf\n", ans);
	return 0;
}