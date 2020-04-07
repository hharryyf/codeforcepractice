#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;
const int maxn = 711;

struct point {
	int x, y;
};

point pt[maxn];


int main() {
	int ans = 0;
	int n, i, j, k;
	while (scanf("%d", &n) != EOF) {
		if (n == 0) break;
		for (i = 1; i <= n; ++i) {
			scanf("%d%d", &pt[i].x, &pt[i].y);
		}
		ans = 0;
		for (i = 1; i <= n; ++i) {
			for (j = i + 1; j <= n; ++j) {
				int cnt = 2;
				for (k = j + 1; k <= n; ++k) {
					point p1 = pt[i], p2 = pt[j], p = pt[k];
					if ((p1.y - p.y) * (p2.x - p.x) == (p2.y - p.y) * (p1.x - p.x)) {
						++cnt;
					}
				}
				ans = max(ans, cnt);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
