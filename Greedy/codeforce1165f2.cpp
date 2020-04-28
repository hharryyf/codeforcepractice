#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

vector<int> g[MAX_SIZE];
int k[MAX_SIZE];
// the offers that ends at day[i]
vector<int> day[MAX_SIZE << 1];
int rem[MAX_SIZE];
int n, m;

bool valid(int T) {
	int i, curr = 0;
	for (i = 1; i <= n; ++i) {
		rem[i] = k[i];
	}
	
	for (i = 0; i < (MAX_SIZE << 1); ++i) day[i].clear();
	
	for (i = 1; i <= n; ++i) {
		int idx = upper_bound(g[i].begin(), g[i].end(), T) - g[i].begin() - 1;
		if (idx >= 0) {
			day[g[i][idx]].push_back(i);
		}
	}
	
	for (i = 1; i <= T; ++i) {
		curr++;
		for (auto tp : day[i]) {
			if (rem[tp] > 0) {
				int amount = min(curr, rem[tp]);
				rem[tp] -= amount;
				curr -= amount;
			}
		}
	}
	
	for (i = 1; i <= n; ++i) {
		curr -= 2 * rem[i];
	}
	
	return curr >= 0;
}

int main() {
	int i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i) scanf("%d", &k[i]);
	for (i = 1; i <= m; ++i) {
		int di, ti;
		scanf("%d%d", &di, &ti);
		g[ti].push_back(di);
	}
	
	for (i = 1; i <= n; ++i) {
		sort(g[i].begin(), g[i].end());
	}
	int l = 1, r = 400010, ans = 400010;
	while (l <= r) {
		int mid = (l+r) >> 1;
		if (valid(mid)) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	
	printf("%d\n", ans);
	return 0;
}