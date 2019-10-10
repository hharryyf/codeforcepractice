#include <bits/stdc++.h>
typedef long long ll;

#define MAX_SIZE 524292
#define MOD 1000000007
using namespace std;

struct segt {
	ll lz, value, cnt;
};

segt tree[MAX_SIZE];
pair<ll,ll> arr[MAX_SIZE >> 1];
ll b[MAX_SIZE >> 1];
vector<ll> disc;
int n;

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].value = tree[index].cnt = 0ll;
		tree[index].lz = 1ll;
		return;
	}
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index].value = tree[index].cnt = 0ll;
	tree[index].lz = 1ll;
}

void pullup(int l, int r, int index) {
	if (l != r) {
		tree[index].value = (tree[index * 2].value + tree[index * 2 + 1].value) % MOD;
		tree[index].cnt = (tree[index * 2].cnt + tree[index * 2 + 1].cnt) % MOD;
	}
}

void pushdown(int l, int r, int index) {
	if (tree[index].lz != 1) {
		if (l != r) {
			tree[index * 2].value = (tree[index * 2].value * tree[index].lz) % MOD;
			tree[index * 2 + 1].value = (tree[index * 2 + 1].value * tree[index].lz) % MOD;
			tree[index * 2].cnt = (tree[index * 2].cnt * tree[index].lz) % MOD;
			tree[index * 2 + 1].cnt = (tree[index * 2 + 1].cnt * tree[index].lz) % MOD;
			tree[index * 2].lz = (tree[index * 2].lz * tree[index].lz) % MOD;
			tree[index * 2 + 1].lz = (tree[index * 2 + 1].lz * tree[index].lz) % MOD;
		}
		tree[index].lz = 1ll;
	}
}

// double the value and cnt of all the numbers in the range l, r
void mul2(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].value = (tree[index].value * 2) % MOD;
		tree[index].cnt = (tree[index].cnt * 2) % MOD;
		tree[index].lz = (tree[index].lz * 2) % MOD;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (end <= mid) {
		mul2(start, end, l, mid, index * 2);
	} else if (start >= mid + 1) {
		mul2(start, end, mid + 1, r, index * 2 + 1);	
	} else {
		mul2(start, end, l, mid, index * 2);
		mul2(start, end, mid + 1, r, index * 2 + 1);
	}
	pullup(l, r, index);
}

void update(int pt, int l, int r, int index, ll val) {
	if (l > r) return;
	pushdown(l, r, index);
	if (l == r && pt == l) {
		tree[index].cnt = val % MOD;
		tree[index].value = (tree[index].cnt * disc[pt]) % MOD;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, val);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, val);
	}
	pullup(l, r, index);
}

ll queryC(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0ll;
	pushdown(l, r, index);
	if (start > r || l > end) return 0ll;
	if (start <= l && r <= end) return tree[index].cnt;
	int mid = l + (r - l) / 2;
	return (queryC(start, end, l, mid, index * 2) + queryC(start, end, mid + 1, r, index * 2 + 1)) % MOD;
}

ll queryV(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return 0ll;
	pushdown(l, r, index);
	if (start > r || l > end) return 0ll;
	if (start <= l && r <= end) return tree[index].value;
	int mid = l + (r - l) / 2;
	return (queryV(start, end, l, mid, index * 2) + queryV(start, end, mid + 1, r, index * 2 + 1)) % MOD;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T > 0) {
		scanf("%d", &n);
		disc = vector<ll>();
		for (int i = 0 ; i < n; i++) {
			scanf("%lld", &arr[i].first);
		}
		
		for (int i = 0 ; i < n; i++) {
			scanf("%lld", &arr[i].second);
			b[i] = arr[i].second;
		}
		
		sort(arr, arr + n);
		sort(b, b + n);
		for (int i = 0 ; i < n; i++) {
			if (i == 0) {
				disc.push_back(b[i]);
			} else if (b[i] != b[i-1]) {
				disc.push_back(b[i]);	
			}
		}
		
		int m = (int) disc.size();
		build(0, m - 1, 1);
		
		ll ans = 0ll;
		for (int i = 0 ; i < n; i++) {
			int index = lower_bound(disc.begin(), disc.end(), arr[i].second) - disc.begin();
			ll sgb = queryV(index, m - 1, 0, m - 1, 1);
			ll clb = queryC(0, index - 1, 0, m - 1, 1);
			ll ceb = queryC(index, index, 0, m - 1, 1);
			ans = (ans + 
			(arr[i].first * ((sgb + (arr[i].second * (1ll + clb)) % MOD)) % MOD) % MOD) % MOD;
			mul2(index + 1, m - 1, 0, m - 1, 1);
			ll val = (clb + 2ll * ceb + 1ll) % MOD;
			update(index, 0, m - 1, 1, val);
		}
		
		printf("%lld\n", ans % MOD);
		T--;
	}
	return 0;
}
