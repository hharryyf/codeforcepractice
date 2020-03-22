#include <bits/stdc++.h>
#define MAX_SIZE 100111
#define MOD 1000000007
typedef long long ll;
using namespace std;

int f[MAX_SIZE], subsz[MAX_SIZE];
ll dep[MAX_SIZE]; 
ll ans;

pair<int, ll> find(int x) {
	if (f[x] == x) return make_pair(x, dep[x]);
	auto p = find(f[x]);
	return make_pair(p.first, p.second + dep[x]);
}
// union 2 already calculated subtree
void unionset(int x, int y) {
	auto p1 = find(x), p2 = find(y);
	if (subsz[p1.first] < subsz[p2.first]) {
		subsz[p2.first] += subsz[p1.first];
		f[p1.first] = p2.first;
		dep[p1.first] = ((dep[p1.first] - dep[p2.first]) % MOD + MOD) % MOD;
	} else {
		subsz[p1.first] += subsz[p2.first];
		f[p2.first] = p1.first;
		dep[p2.first] = ((dep[p2.first] - dep[p1.first]) % MOD + MOD) % MOD;
	}
}

int main() {
	int n, i;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		f[i] = i, subsz[i] = 1;
	}
	
	for (i = 1; i <= n; ++i) {
		int k, v;
		ll x;
		scanf("%d", &k);
		if (k != 0) {
			while (k > 0) {
				scanf("%d%I64d", &v, &x);
				auto p = find(v);
				// weight of the new edge is p.second + x
				ans += p.second + x;
				ans %= MOD;
				dep[p.first] = (dep[p.first] + p.second + x) % MOD;
				unionset(v, i);
				--k;
			}
		}
	}
	printf("%I64d\n", (ans + MOD) % MOD);
	return 0;
}