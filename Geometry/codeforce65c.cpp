#include <bits/stdc++.h>
#define MAX_SIZE 11111
using namespace std;

struct point {
	double x, y, z;
};

double dist(point p1, point p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + 
	            (p1.y - p2.y) * (p1.y - p2.y) + 
				(p1.z - p2.z) * (p1.z - p2.z));
}

point pt[MAX_SIZE];
point st;
int n, vs, vp;
const double eps = 1e-8;

point move(double t) {
	point p = pt[n];
	int i;
	for (i = 0; i < n; ++i) {
		if (dist(pt[i], pt[i+1]) - t * vs >= -eps) {
			double r = t * vs / dist(pt[i], pt[i+1]);
			double dx = r * (-pt[i].x + pt[i+1].x);
			double dy = r * (-pt[i].y + pt[i+1].y);
			double dz = r * (-pt[i].z + pt[i+1].z);
			p = point{pt[i].x + dx, pt[i].y + dy, pt[i].z + dz};
			// cout << t << " " << r << " " << dx << " " << dy << " " << dz << " " << t << endl;
			break;
		} else {
			t = t - dist(pt[i], pt[i+1]) / (1.0 * vs);
			p = pt[i+1];
		}
	}
	return p;
}
/*
point move2(double t) {
	point p = pt[n];
	int i;
	for (i = 0; i < n; ++i) {
		if (dist(pt[i], pt[i+1]) - t * vs >= -eps) {
			double r = t * vs / dist(pt[i], pt[i+1]);
			double dx = r * (-pt[i].x + pt[i+1].x);
			double dy = r * (-pt[i].y + pt[i+1].y);
			double dz = r * (-pt[i].z + pt[i+1].z);
			p = point{pt[i].x + dx, pt[i].y + dy, pt[i].z + dz};
			cout << t << " " << r << " " << dx << " " << dy << " " << dz << " " << t << endl;
			break;
		} else {
			t = t - dist(pt[i], pt[i+1]) / (1.0 * vs);
			p = pt[i+1];
		}
	}
	return p;
}
*/
bool valid(double t) {
	point p = move(t);
	return dist(p, st) - eps <= t * vp;
}

int main() {
	int i;
	double dis = 0.0;
	scanf("%d", &n);
	for (i = 0; i <= n; ++i) {
		scanf("%lf%lf%lf", &pt[i].x, &pt[i].y, &pt[i].z);
		if (i > 0) {
			dis += dist(pt[i-1], pt[i]);
		}
		// cout << dist(pt[i-1], pt[i]) << endl;
	}
	
	scanf("%d%d", &vp, &vs);
	scanf("%lf%lf%lf", &st.x, &st.y, &st.z);
	// cout << move2(25.5).x << endl;
    // cout << move2(25.5).y << endl;
    // cout << move2(25.5).z << endl;
	double low = 0.0, high = dis / (1.0 * vs);
	double ans = -1.0;
	for (i = 1; i <= 70; ++i) {
		double mid = 0.5 * (low + high);
		if (valid(mid)) {
			ans = mid;
			high = mid;
		} else {
			low = mid;
		}
	}
	
	if (ans < 0) {
		printf("NO\n");
		return 0;
	}
	
	printf("YES\n");
	printf("%.10lf\n", ans);
	auto p = move(ans);
	printf("%.10lf %.10lf %.10lf\n", p.x, p.y, p.z);
	return 0;
}