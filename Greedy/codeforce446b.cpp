#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MOD 1000000000
typedef long long ll;
using namespace std;
int n, m, k;
ll p;
// row[i] refers to row operation i times
ll row[1011111], col[1011111];
ll a[1011][1011];

int main() {
	scanf("%d%d%d%lld", &n, &m, &k, &p);
	int i, j;
	priority_queue<ll> q;
	for (i = 1; i <= n; i++) {
		ll curr = 0;
		for (j = 1; j <= m; j++) {
			scanf("%lld", &a[i][j]);
			curr += a[i][j];
		}
		q.push(curr);
	}
	
	for (i = 1; i <= k; i++) {
		row[i] = row[i-1] + q.top();
		q.pop();
		q.push(row[i] - row[i-1] - p * m);
	}
	
	while (!q.empty()) q.pop();
	
	for (i = 1; i <= m; i++) {
		ll curr = 0;
		for (j = 1; j <= n; j++) {
			curr += a[j][i];
		}
		q.push(curr);
	}
	
	for (i = 1; i <= k; i++) {
		col[i] = col[i-1] + q.top();
		q.pop();
		q.push(col[i] - col[i-1] - p * n);
	}
	
	ll ans = -1ll * MOD * MOD;
	for (i = 0; i <= k; i++) {
		ans = max(ans, row[i] + col[k-i] - 1ll * i * (k-i) * p);
	}
	printf("%lld\n", ans);
	return 0;
}
