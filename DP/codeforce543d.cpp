#include <bits/stdc++.h>
#define MAX_SIZE 200011
#define MOD 1000000007ll
typedef long long ll;

using namespace std;

int n;
ll dp[MAX_SIZE], f[MAX_SIZE];

vector<int> g[MAX_SIZE];

ll ivt(ll num) {
	ll base = num;
	ll ret = 1ll;
	ll p = 1000000005;
	while (p > 0) {
		if (p % 2 == 0) {
			base = (base * base) % MOD;
			p = p / 2;
		} else {
			ret = (ret * base) % MOD;
			p = p - 1;
		}
	}
	
	return ret % MOD;
}

void dfs_1(int v, int pre) {
	f[v] = 1;
	for (auto nv : g[v]) {
		if (nv != pre) {
			dfs_1(nv, v);
			f[v] = f[v] * (1ll + f[nv]);
			f[v] %= MOD;
		}
	}
	
}

void dfs_2(int v, int pre) {
	int cnt = 0;
    ll tot = 1;
    for(auto nv : g[v]){
         if (nv == pre) continue;
         if ( (f[nv] + 1) % MOD == 0) ++cnt;
         else {
         	tot *= f[nv] + 1;
         	tot %= MOD;
         }
    }	
	
	for (auto nv : g[v]) {
		if (nv != pre) {
			if (cnt) {
				if ((f[nv] + 1) % MOD == 0 && cnt == 1) {
					dp[nv] = tot;
				} else {
					dp[nv] = 0;
				}
			} else {
				dp[nv] = (f[v] * ivt(f[nv] + 1)) % MOD;
			}
			
			dp[nv] *= dp[v] + 1;
			dp[nv] %= MOD;
			dfs_2(nv, v);
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		int v;
		scanf("%d", &v);
		g[v].push_back(i);
		g[i].push_back(v);
	}
	
	dfs_1(1, 0);
	dfs_2(1, 0);
	
	for(int i = 1; i <= n; i++){
         printf("%lld ",f[i] * (dp[i] + 1) % MOD);
    }
	
	cout << endl;
	return 0;
}
