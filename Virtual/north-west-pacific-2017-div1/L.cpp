#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
	double K, P, X;
	cin >> K >> P >> X;
	int M = max(1, (int) floor(sqrt(K * P / X)));
	double ans = (K * P / M + 1.0 * M * X);
	if (M - 1 > 0) {
		ans = min(ans, (K * P / (M - 1) + 1.0 * (M - 1) * X));
	}

	if (M + 1 > 0) {
		ans = min(ans, (K * P / (M + 1) + 1.0 * (M + 1) * X));
	}
	printf("%.3lf\n", ans);
	return 0;
}