#pragma GCC optimize(3)
#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 150011
using namespace std;

// we define dp[i][j] as the maximum happiness
// that can be gained when seeing the ith firework
// at the jth position
// then dp[i][j] = max(dp[i-1][k]) + b[i] - |a[i] - j|
// here let's define ti = t[i] - t[i-1]
// -d*ti + j <= k <= d*ti + j
// in other words, for each i, we need to maintain a window
// of length 2(d * ti) and support range max query

ll dp[2][MAX_SIZE];
ll a[311], b[311], t[311];

int idx(int x) {
	return (x & 1);
}

int main() {
	int i, j;
	int n, m, d;
	scanf("%d%d%d", &n, &m, &d);
	for (i = 1; i <= m; ++i) {
		scanf("%I64d%I64d%I64d", &a[i], &b[i], &t[i]);
	}
	
	for (i = 1; i <= n; ++i) {
		dp[1][i] = b[1] - abs(a[1] - i);
	}
	
	
	for (j = 2; j <= m; ++j) {
		deque<int> q;
		// we want to maintain a window of size d*(t[j] - t[j-1])
		ll width = 1ll * d * (t[j] - t[j-1]);
		if (width > n) width = n;
		int r = 1;
		for (i = 1; i <= n; ++i) {
			while (!q.empty()) {
				auto p = q.front();
				if (p + width < i) {
					q.pop_front();
				} else {
					break;
				}
			}
			
			while (r <= n && r - i <= width) {
				while (!q.empty() && dp[idx(j-1)][r] >= dp[idx(j-1)][q.back()]) {
					q.pop_back();
				}
				
				q.push_back(r);
				r++;
			}
			
			dp[idx(j)][i] = dp[idx(j-1)][q.front()] + b[j] - abs(a[j] - i); 
		}
		q.clear();
	}
	
	ll ans = dp[idx(m)][1];
	for (i = 2; i <= n; ++i) {
		ans = max(ans, dp[idx(m)][i]);
	}
	
	printf("%I64d\n", ans);
	
	return 0;
}