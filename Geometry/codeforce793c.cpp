#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;

struct line {
	double rx, ry, dx, dy;
};

double x1, y1, x2, y2;
const double inf = 2e5;
const double eps = 1e-15;
line li[MAX_SIZE];
const pair<double, double> invalid = make_pair(inf, -inf);
int sgn(double x, double y) {
	if (abs(x-y) <= eps) return 0;
	if (x > y) return 1;
	return -1;
}

bool inside(line l) {
	if (sgn(x1, l.rx) < 0 && sgn(x2, l.rx) > 0 && sgn(y1, l.ry) < 0 && sgn(y2, l.ry) > 0) {
		return true;
	}
	return false;
}

pair<double, double> valid(line l) {
	if (sgn(l.dx, 0.0) == 0 && sgn(l.dy, 0.0) == 0) {
		if (inside(l)) {
			return make_pair(0, inf);
		}
		return invalid;
	}
	// if the ants move in a vertical direction, consider
	// if the ant is on a vertical line, return the invalid pair
	if (sgn(l.dx, 0.0) == 0) {
		if (sgn(l.rx, x1) <= 0 || sgn(l.rx, x2) >= 0) {
			return invalid;
		}
		
		double t1 = (y1 - l.ry) / l.dy, t2 = (y2 - l.ry) / l.dy;
		if (sgn(t1, t2) > 0) swap(t1, t2);
		return make_pair(max(t1, 0.0), t2);
	}
	
	if (sgn(l.dy, 0.0) == 0) {
		if (sgn(l.ry, y1) <= 0 || sgn(l.ry, y2) >= 0) {
			return invalid;
		}
		
		double t1 = (x1 - l.rx) / l.dx, t2 = (x2 - l.rx) / l.dx;
		if (sgn(t1, t2) > 0) swap(t1, t2);
		return make_pair(max(t1, 0.0), t2);
	}
	
	double th1 = (y1 - l.ry) / l.dy;
	if (th1 < 0 || sgn(l.rx + th1 * l.dx, x1) < 0 || sgn(l.rx + th1 * l.dx, x2) > 0) {
		th1 = -inf;
	}
	
	double th2 = (y2 - l.ry) / l.dy;
	if (th2 < 0 || sgn(l.rx + th2 * l.dx, x1) < 0 || sgn(l.rx + th2 * l.dx, x2) > 0) {
		th2 = -inf;
	}
	
	double th3 = (x1 - l.rx) / l.dx;
	if (th3 < 0 || sgn(l.ry + th3 * l.dy, y1) < 0 || sgn(l.ry + th3 * l.dy, y2) > 0) {
		th3 = -inf;
	}
	
	double th4 = (x2 - l.rx) / l.dx;
	if (th4 < 0 || sgn(l.ry + th4 * l.dy, y1) < 0 || sgn(l.ry + th4 * l.dy, y2) > 0) {
		th4 = -inf;
	}
	
	vector<double> vc;
	vc.push_back(th1);
	vc.push_back(th2);
	vc.push_back(th3);
	vc.push_back(th4);
	sort(vc.begin(), vc.end());
	if (vc[1] >= 0.0) swap(vc[1], vc[2]);
	if (inside(l)) {
		return make_pair(0, vc[3]);
	}
	return make_pair(max(vc[2], 0.0), vc[3]);
}

int main() {
	pair<double, double> ans = {0, inf};
	int n, i;
	scanf("%d", &n);
	scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
	if (x1 == x2 || y1 == y2) {
		printf("-1\n");
		return 0;
	}
	for (i = 1; i <= n; ++i) {
		scanf("%lf%lf%lf%lf", &li[i].rx, &li[i].ry, &li[i].dx, &li[i].dy);
		auto p = valid(li[i]);
		// cout << p.first << " " << p.second << endl;
		ans.first = max(ans.first, p.first);
		ans.second = min(ans.second, p.second);
	}
	
	if (sgn(ans.first, ans.second) >= 0) {
		printf("-1\n");
		return 0;
	}
	printf("%.19lf\n", ans.first);
	return 0;
}