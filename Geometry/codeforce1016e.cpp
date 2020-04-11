#include <bits/stdc++.h>
#define MAX_SIZE 200111
using namespace std;

struct segt {
	double l, r;
};

double sy, a, b;
int n;
segt s[MAX_SIZE];
double pref[MAX_SIZE];
const double eps = 1e-8;

bool outleft(double x, double y, int idx) {
	double xcoord = x - (y - sy) * (x - s[idx].l) / y;
	//cout << idx << " -L-> " << xcoord << endl;
	return a - xcoord >= -eps;
}

bool outright(double x, double y, int idx) {
	double xcoord = x - (x - s[idx].r) * (y - sy) / y;
	//cout << idx << " -R-> " << xcoord << endl;
	return xcoord - b >= -eps;
}

double solve(double x, double y) {
	//cout << "solve " << x << " " << y << endl;
	int L = 0, R = n + 1;
	double ret = 0;
	int low = 1, high = n;
	while (low <= high) {
		int mid = (low + high) >> 1;
		if (outleft(x, y, mid)) {
			L = mid;
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	
	low = 1, high = n;
	while (low <= high) {
		int mid = (low + high) >> 1;
		if (outright(x, y, mid)) {
			R = mid;
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	
	//cout << "L= " << L << " R= " << R << endl;
	if (L + 1 <= R - 1) {
		ret += (y - sy) / y * (pref[R-1] - pref[L]);
	}
	
	double delta = 0;
	if (L != 0) {
		delta += max(0.0, min(b, x - (x - s[L].r) * (y - sy) / y) - a);
	}
	
	if (R != n+1) {
		delta += max(0.0, b - max(x - (y - sy) * (x - s[R].l) / y, a));
	}
	
	ret += min(delta, b - a);
	return ret;
}

int main() {
	int i;
	scanf("%lf%lf%lf", &sy, &a, &b);
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%lf%lf", &s[i].l, &s[i].r);
		pref[i] = pref[i-1] + s[i].r - s[i].l;
	}
	
	int q;
	scanf("%d", &q);
	while (q > 0) {
		double x, y;
		scanf("%lf%lf", &x, &y);
		printf("%.15lf\n", solve(x, y));
		q--;
	}
	return 0;
}