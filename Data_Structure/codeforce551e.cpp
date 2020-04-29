#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define MAX_BLOCK 711
typedef long long ll;
using namespace std;

struct block {
	// (value,index)
	vector<pair<ll, int>> mp;
	ll lz;
};

int n;
block blk[MAX_BLOCK];
int bid[MAX_BLOCK * MAX_BLOCK];
ll a[MAX_BLOCK * MAX_BLOCK];
int block_size;

int query(ll val) {
	int i, R = bid[n];
	int l = n + 1, r = -1;
	for (i = 1; i <= R; ++i) {
		int idxl = lower_bound(blk[i].mp.begin(), blk[i].mp.end(), make_pair(val - blk[i].lz, 0)) - blk[i].mp.begin();
		int idxh = upper_bound(blk[i].mp.begin(), blk[i].mp.end(), make_pair(val - blk[i].lz, n+1)) - blk[i].mp.begin() - 1;
		if (idxh != -1 && blk[i].mp[idxh].first == val - blk[i].lz) {
			r = max(r, blk[i].mp[idxh].second);
		}
		
		if (idxl != (int) blk[i].mp.size() && blk[i].mp[idxl].first == val - blk[i].lz) {
			l = min(l, blk[i].mp[idxl].second);
		}
	}
	return r >= l ? r - l : -1;
}

void update(int l, int r, ll val) {
	int L = bid[l], R = bid[r];
	int i, j;
	if (L == R) {
		j = 0;
		for (i = (L - 1) * block_size + 1; i <= L * block_size && i <= n; ++i) {
			a[i] += blk[L].lz + val * (i >= l && i <= r);
			blk[L].mp[j++] = {a[i], i};
		}
		blk[L].lz = 0;
		sort(blk[L].mp.begin(), blk[L].mp.end());
	} else {
		for (i = L + 1; i <= R - 1; ++i) {
			blk[i].lz += val;
		}
		
		j = 0;
		for (i = (L - 1) * block_size + 1; i <= L * block_size && i <= n; ++i) {
			a[i] += blk[L].lz + val * (i >= l && i <= r);
			blk[L].mp[j++] = {a[i], i};
		}
		sort(blk[L].mp.begin(), blk[L].mp.end());

		j = 0;
		for (i = (R - 1) * block_size + 1; i <= R * block_size && i <= n; ++i) {
			a[i] += blk[R].lz + val * (i >= l && i <= r);
			blk[R].mp[j++] = {a[i], i};
		}
		sort(blk[R].mp.begin(), blk[R].mp.end());

		
		blk[L].lz = blk[R].lz = 0;
	}
}

int main() {
	int q, i;
	scanf("%d%d", &n, &q);
	block_size = sqrt(n);
	for (i = 1; i <= n; ++i) {
		bid[i] = (i - 1) / block_size + 1;
		scanf("%I64d", &a[i]);
		blk[bid[i]].mp.emplace_back(a[i], i);
	}
	
	for (i = 1; i <= bid[n]; ++i) {
		sort(blk[i].mp.begin(), blk[i].mp.end());
	}
	
	while (q > 0) {
		int tp;
		ll val;
		scanf("%d", &tp);
		if (tp == 1) {
			int l, r;
			scanf("%d%d%I64d", &l, &r, &val);
			update(l, r, val);
		} else {
			scanf("%I64d", &val);
			printf("%d\n", query(val));
		}
		--q;
	}
	return 0;
}