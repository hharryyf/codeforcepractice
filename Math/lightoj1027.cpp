#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
	int T, n, t, i;
	scanf("%d", &T);
	for (t = 1; t <= T; ++t) {
		int bad = 0, cnt = 0;
		scanf("%d", &n);
		for (i = 1; i <= n; ++i) {
			int x;
			scanf("%d", &x);
			if (x < 0) {
				bad++;
				x = -x;
			}
			cnt += x;
		}
		
		if (bad == n) {
			printf("Case %d: inf\n", t);
		} else {
			// ans is cnt / (n-bad)
			int g = gcd(cnt, n - bad);
			printf("Case %d: %d/%d\n", t, cnt/g, (n-bad)/g);
		}
	}
	return 0;
}