#include <bits/stdc++.h>
#define MAX_SIZE 262192
typedef long long ll;
using namespace std;

ll tree[MAX_SIZE], h[MAX_SIZE >> 1], disc[MAX_SIZE >> 1], a[MAX_SIZE >> 1], dp[MAX_SIZE >> 1];

void update(int pt, int l, int r, int index, ll val) {
	if (l > r) return;
	if (l == r && r == pt) {
		tree[index] = val;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, val);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, val);
	}
	
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

ll query(int st, int ed, int l, int r, int index) {
	if (st > ed || l > r || st > r || l > ed) return 0ll;
	if (st <= l && r <= ed) return tree[index];
	int mid = l + (r - l) / 2;
	return max(query(st, ed, l, mid, index * 2), query(st, ed, mid + 1, r, index * 2 + 1));
}

int getlow(ll arr[], ll value,int l, int r) {
	int low = l, high = r;
	int ans = -1;
	while (low <= high) {
		// cout << "debug" << endl;
		int mid = low + (high - low) / 2;
		if (arr[mid] <= value) {
			ans = mid;
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	
	return ans;
}

int gethigh(ll arr[], ll value, int l, int r) {
	int low = l, high = r;
	int ans = MAX_SIZE;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (arr[mid] >= value) {
			ans = mid;
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	
	return ans;
}

int main() {
	int n, i;
	ll d;
	ll ans = 1ll;
	scanf("%d%lld", &n, &d);
	for (i = 0 ; i < n; i++) {
		ll v;
		scanf("%lld", &v);
		h[i] = a[i] = v;
	}
	
	sort(a, a + n);
	
	int total = 0;
	for (i = 0 ; i < n; i++) {
		if (i == 0) {
			disc[total++] = a[i];
		} else if (a[i] != a[i-1]) {
			disc[total++] = a[i];
		}
	}	
	
	dp[0] = 1ll;
	int l = getlow(disc, h[0], 0, total - 1);
	update(l, 0, total - 1, 1, dp[0]);
	for (i = 1; i < n; i++) {
		int low_index = getlow(disc, h[i] - d, 0, total - 1);
		int high_index = gethigh(disc, h[i] + d, 0, total - 1);
		int curr = getlow(disc, h[i], 0, total - 1);
		ll L = query(0, low_index, 0, total - 1, 1), R = query(high_index, total - 1, 0, total - 1, 1);
		dp[i] = max(L, R) + 1;
		update(curr, 0, total - 1, 1, dp[i]);
		ans = max(ans, dp[i]);
	}
	
	cout << ans << endl;
	
	vector<ll> ret = vector<ll>();
	i = n - 1;
	ll maxheight = -1;
	while (i >= 0) {
		if (ans == dp[i]) {
			if ((int) ret.size() == 0) {
				maxheight = h[i];
				ret.push_back(i+1);
				ans--;
			} else if (abs(maxheight - h[i]) >= d) {
				maxheight = h[i];
				ret.push_back(i+1);
				ans--;
			}
		}
		i--;
	}
	
	for (i = (int) ret.size() - 1; i >= 0; i--) {
		cout << ret[i] << " ";
	}
	cout << endl;
	return 0;
}
