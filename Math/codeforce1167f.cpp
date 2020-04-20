#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 500111
typedef long long ll;
using namespace std;

const ll mod = 1e9 + 7;

struct BIT {
	ll tree[MAX_SIZE];
	int n;
	void init(int n) {
		int i;
		this->n = n;
		for (i = 0 ; i < MAX_SIZE; ++i) tree[i] = 0;
	}
	
	int shift(int x) {
		return x & (-x);
	}
	
	void update(int x, ll val) {
		if (x <= 0) return;
		while (x <= n) {
			tree[x] += val;
			x += shift(x);
		}
	}
	
	ll query(int pos) {
		ll ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			pos -= shift(pos);
		}
		return ret;
	}
};

BIT t;

ll num[MAX_SIZE];
vector<ll> disc;
// calculate the coefficient of num[i]
ll coef[MAX_SIZE];
int idx(ll val) {
	return lower_bound(disc.begin(), disc.end(), val) - disc.begin() + 1;
}

ll mul(ll v1, ll v2) {
	ll ret = (v1 * v2) % mod;
	if (ret < 0) ret += mod;
	return ret;
}

ll add(ll v1, ll v2) {
	return ((v1 + v2) % mod + mod) % mod;
}

int main() {
	int i, n;
	ll ans = 0;
	scanf("%d", &n);
	t.init(n);
	for (i = 1; i <= n; ++i) {
		scanf("%I64d", &num[i]);
		disc.push_back(num[i]);
	}
	
	sort(disc.begin(), disc.end());
	
	for (i = 1; i <= n; ++i) {
		coef[i] = mul(t.query(idx(num[i])), n - i + 1);
		t.update(idx(num[i]), i);
	}
	
	t.init(n);
	
	for (i = n; i >= 1; --i) {
		coef[i] = add(coef[i], mul(t.query(idx(num[i])), i));
		t.update(idx(num[i]), n - i + 1);
		coef[i] = add(coef[i], 1ll * i * (n-i + 1));
	}
	
	for (i = 1; i <= n; ++i) {
		ans = add(ans, mul(coef[i], num[i]));
	}
	
	printf("%I64d\n", ans);
	return 0;
}