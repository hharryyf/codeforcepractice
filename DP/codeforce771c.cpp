#include <bits/stdc++.h>
#define MAX_SIZE 200111

typedef long long ll;

using namespace std;

vector<int> g[MAX_SIZE];

ll dp[MAX_SIZE][5];

ll subsz[MAX_SIZE][5];

ll ans = 0ll;

int n, k;

void dfs(int v, int pre) {
	int i, j;
	for (auto nextv : g[v]) {
		if (nextv != pre) {
			vector<int> tmpsz = vector<int>(k, 0);
			vector<ll> tmpcnt = vector<ll>(k, 0ll);
			dfs(nextv, v);
			
			for (i = 0 ; i < k; i++) {
				tmpsz[i] += subsz[nextv][((i-1) + k) % k];
				if (i == 1 || k == 1) {
					tmpcnt[i] += dp[nextv][((i-1) + k) % k] + subsz[nextv][((i-1) + k) % k];	
				} else {
					tmpcnt[i] += dp[nextv][((i-1) + k) % k];
				}
				// cout << v << " " << tmpcnt[i] << endl;
			}
			
			for (i = 0 ; i < k; i++) {
				for (j = 0 ; j < k; j++) {
					ans += dp[v][i] * tmpsz[j] + tmpcnt[j] * subsz[v][i];
					// currently there are many cases such as 1 + 1, 1 + 2
					// would result in adding more to the final answer
					if (i > 0 && j > 0 && i + j <= k) {
						ans = ans - subsz[v][i] * tmpsz[j];
					}
				}
			}
			
			for (i = 0 ; i < k; i++) {
				dp[v][i] += tmpcnt[i];
				subsz[v][i] += tmpsz[i];
			}
		}
	}
	
	for (i = 0 ; i < k; i++) {
		ans = ans + dp[v][i];
	}
	
	subsz[v][0]++;
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i < n; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	dfs(1, -1);
	/*
	for (int i = 1; i <= n; i++) {
		cout << i << ": ";
		for (int j = 0; j < k; j++) {
			cout << subsz[i][j] << " " << dp[i][j] << ", ";
		}
		cout << endl;
	}*/
	
	printf("%lld\n", ans);
	return 0;
}
