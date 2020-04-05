#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 101111
using namespace std;

int a[MAX_SIZE], b[MAX_SIZE];
int tmp[MAX_SIZE << 1];
int n, m;
int ans;

int cid(int x, int step, bool up) {
	if (up) {
		return (x + step) % (step << 1);
	}
	return x % (step << 1);
}

void solve(int step) {
	int i;
	unordered_map<int, int> h;
	for (i = 1; i <= n; ++i) {
		h[cid(a[i], step, false)]++;
		ans = max(ans, h[cid(a[i], step, false)]);
	}
	
	for (i = 1; i <= m; ++i) {
		h[cid(b[i], step, true)]++;
		ans = max(ans, h[cid(b[i], step, true)]);
	}
}

int main() {
	int y, i;
	scanf("%d%d", &n, &y);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	scanf("%d%d", &m, &y);
	for (i = 1; i <= m; ++i) {
		scanf("%d", &b[i]);
		if (binary_search(a+1, a + 1 + n, b[i])) {
			ans = 2;
		}
	}
	
	for (i = 0 ; i <= 29; ++i) {
		solve(1 << i);
	}
	
	printf("%d\n", ans);
	return 0;
}