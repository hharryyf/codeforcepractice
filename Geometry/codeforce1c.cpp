#include <bits/stdc++.h>
#define Pi 3.141592653589793238
using namespace std;
 
struct point {
	double x, y;
};
 
double len(point p1, point p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
 
double round(double r) {
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}
 
bool div(double x) {
    
	return fabs(x - round(x)) <= 1e-4;
}
 
int main() {
	double ans = -1;
	double theta;
	double cs;
	point p1, p2, p3;
	scanf("%lf%lf%lf%lf%lf%lf", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);
	double a = len(p1, p2), b = len(p2, p3), c = len(p1, p3);
	cs = (a * a + b * b - c * c) / (2.0 * a * b);
	theta = acos(cs);
	double r = c / (2.0 * sin(theta));
	// cout << r << endl;
	double aa[3];
	aa[0] = acos((r * r + r * r - a * a) / (2.0 * r * r));
	aa[1] = acos((r * r + r * r - b * b) / (2.0 * r * r));
	aa[2] = acos((r * r + r * r - c * c) / (2.0 * r * r));
	// cout << aa[0] << " " << aa[1] << " " << aa[2] << endl;
	int i, j;
	for (i = 3 ; i <= 100; ++i) {
		bool flag = true;
		for (j = 0 ; j < 3; ++j) {
			if (!div(aa[j] / (2.0 * Pi / (1.0 * i)))) {
				flag = false;
				// cout << "fail " << i << " "<< aa[j] / (2.0 * Pi / (1.0 * i)) << endl;
				break;
			}
		}
		
		if (flag) {
			// cout << i << endl;
			if (ans < 0) {
				ans = r * r * sin(2.0 * Pi / (1.0 * i)) * 0.5 * i;
			} else {
				ans = min(ans, r * r * sin(2.0 * Pi / (1.0 * i)) * 0.5 * i); 
			}
		}
	}
	printf("%.8lf\n", ans);
	return 0;
}
    