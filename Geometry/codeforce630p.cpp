#include <bits/stdc++.h>
#define Pi acos(-1.0)
using namespace std;

int main() {
	double k, r;
	scanf("%lf%lf", &k, &r);
	double a = Pi / (2.0 * k);
	double b = Pi / (1.0 * k);
	double g = Pi - a - b;
	printf("%.12lf\n", sin(a) * sin(b) * k * r * r / sin(g));
	return 0;
}