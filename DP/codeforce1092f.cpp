#include <bits/stdc++.h>
#define MAX_SIZE 201111
typedef long long ll;

using namespace std;

ll subsz[MAX_SIZE];
ll a[MAX_SIZE];
ll f[MAX_SIZE], p[MAX_SIZE];
vector<int> g[MAX_SIZE];
int n;

void dfs_1(int v, int pre) {
	subsz[v] = a[v];
	for (auto nv : g[v]) {
		if (nv != pre) {
			dfs_1(nv, v);
			f[v] += f[nv] + subsz[nv];
			subsz[v] += subsz[nv];
		}
	}
}

void dfs_2(int v, int pre) {
	
	for (auto nv : g[v]) {
		if (nv != pre) {
			ll tmp = f[v] - f[nv] - subsz[nv];
			tmp += p[v];
			p[nv] = tmp + subsz[1] - subsz[nv]; 
			// cout << nv << " " << subsz[1] - subsz[nv] << endl;
			// cout << v << " " << nv << " --> " << f[v] << " " << p[v] << " " << p[nv] << endl;
			dfs_2(nv, v);
		}
	}
}

int main() {
	ll ans = 0;
	int i;
	
	scanf("%d", &n);
	
	for (i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}
	
	for (i = 1; i < n; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
	}
	
	dfs_1(1, -1);
	
	dfs_2(1, -1);
	
	for (i = 1 ; i <= n; i++) {
		ans = max(ans, f[i] + p[i]);
	}
	
	printf("%lld\n", ans);
	return 0;
}
