#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 1000111
typedef long long ll;
using namespace std;

const int maxn = 1000000;
ll tree[MAX_SIZE];
// record the previous occurence contribution of a number
ll pre[MAX_SIZE];

int shift(int x) {
	return x & (-x);
}

void update(int x, ll val) {
	val %= MOD;
	while (x <= maxn) {  
        tree[x] += val;
        tree[x] %= MOD;
		x += shift(x);
	} 
}

ll query(int x) {
    ll ret = 0;
	while (x > 0) {
        ret += tree[x];
        ret %= MOD;
        x -= shift(x);
	}
	return ret;
}

void change(int x, ll val) {
    ll ret = query(x) - query(x-1);
    update(x, val - ret);
}

int main() {
	int n;
	scanf("%d", &n);
	int i;
	for (i = 1; i <= n; i++) {
		int v;
		scanf("%d", &v);  
		ll endv = 1ll * (v * (query(v-1) + 1 + pre[v])) % MOD;
		change(v, endv); 
		pre[v] = (1ll * (query(v) - query(v-1))) % MOD;
		// cout << endv << endl;
	}
	printf("%lld\n", query(maxn) % MOD);
	return 0;
}
