#include <bits/stdc++.h>
#define Pi 3.14159265358979
using namespace std;

double l[3];

double calc(double a, int num) {
	double theta = Pi / (1.0 * num);
	double h = sqrt(1 - 1.0 / (4.0 * sin(theta) * sin(theta)));
	return a * a * a / (12.0 * tan(theta)) * h * num;
}

int main() {
	scanf("%lf%lf%lf", &l[0], &l[1], &l[2]);
	int i;
	double ans = 0;
	for (i = 0 ; i < 3; ++i) {
		ans += calc(l[i], i + 3);
	}
	
	printf("%.12lf\n", ans);
	return 0;
}