#include <bits/stdc++.h>
#define Pi acos(-1.0)
using namespace std;

const double eps = 1e-12;

int main() {
	int q, i;
	double r, v;
	scanf("%d%lf%lf", &q, &r, &v);
	while (q > 0) {
		double s, f;
		scanf("%lf%lf", &s, &f);
		double low = 0, high = 1e9, ans = 1e9;
		for (i = 0 ; i < 70; ++i) {
			// mid is the attempted time
			double mid = 0.5 * (low + high);
			// the number of rounds made by the bike
			double round = v * mid / (Pi * r * 2);
			double theta = round - floor(round);
			
			theta = 1.0 * Pi * min(1 - theta, theta);
			// cout << floor(round) << " " << theta << endl;
			double dist = v * mid + sin(theta) * r * 2.0;
			if (dist >= f - s + eps) {
				ans = mid;
				high = mid;
			} else {
				low = mid;
			}
		}
		
		printf("%.12lf\n", ans);
		--q;
	}
	return 0;
}