#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define MAX_SIZE 100111
typedef long long ll;
using namespace std;

// v1->v2 means v1 is going to be braged by v2
vector<int> g[MAX_SIZE];
int in[MAX_SIZE], out[MAX_SIZE];
// invariant, ans = sum(in[i] * out[i], i = 1..n)
ll ans = 0;

void update(int v) {
	ans = ans - 1ll * in[v] * out[v];
	in[v] = 0;
	for (auto nv : g[v]) {
		ans = ans - 1ll * out[nv] * in[nv];
		out[nv]--;
		in[nv]++;
		ans = ans + 1ll * out[nv] * in[nv];
		++out[v];
	}
	
	while (!g[v].empty()) {
		g[g[v].back()].push_back(v);
		g[v].pop_back();
	}
	
}

int main() {
	int n, m;
	int i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= m; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		if (v1 > v2) {
			swap(v1, v2);
		} 
		
		++in[v1], ++out[v2];
		g[v1].push_back(v2);
	}
	
	for (i = 1; i <= n; ++i) {
		ans = ans + 1ll * in[i] * out[i];
	}
	
	printf("%I64d\n", ans);
	int q;
	scanf("%d", &q);
	while (q--) {
		int v;
		scanf("%d", &v);
		update(v);
		printf("%I64d\n", ans);
	}
	return 0;
}