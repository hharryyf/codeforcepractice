#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MID ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
#define MAX_SIZE 262192
using namespace std;

int tree[MAX_SIZE];
const int maxn = 100000;
void update(int pt, int l, int r, int index, int val) {
	if (pt < l || pt > r || l > r) return;
	if (l == r && pt == l) {
		tree[index] = max(tree[index], val);
		return;
	}
	
	if (pt <= MID) {
		update(pt, l, MID, LEFT, val);
	} else {
		update(pt, MID + 1, r, RIGHT, val);
	}
	tree[index] = max(tree[LEFT], tree[RIGHT]);
}

int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return 0;
	if (start <= l && r <= end) return tree[index];
	if (end <= MID) {
		return query(start, end, l, MID, LEFT);
	}
	
	if (start >= MID + 1) {
		return query(start, end, MID + 1, r, RIGHT);
	}
	
	return max(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

int a[MAX_SIZE];
int dp[MAX_SIZE];
int n;
// dp[idx] -> (a[idx],idx)
priority_queue<pair<int, int>> st[MAX_SIZE];
char ans[MAX_SIZE];

int main() {
	int ret = 0, i;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		dp[i] = query(1, a[i] - 1, 1, maxn, 1) + 1;
		update(a[i], 1, maxn, 1, dp[i]);
		ret = max(dp[i], ret);
	}
	
	int idx = n;
	// then we are actually interested in whether there's an element j on the right of
	// i which dp[j] = dp[i] + 1 and a[j] > a[i] and j is in at least 1 LIS
	for (i = n; i >= 1; --i) {
		if (dp[i] == ret) {
			idx = i;
			break;
		}
	}
	
	for (i = idx; i >= 1; --i) {
		if (dp[i] == ret) {
			st[dp[i]].push(make_pair(a[i], i));
		} else {
			if (!st[dp[i] + 1].empty()) {
				auto p = st[dp[i] + 1].top().first;
				if (p > a[i]) {
					st[dp[i]].push(make_pair(a[i], i));
				}
			}
		}
	}
	
	for (i = 1; i <= ret; ++i) {
		int sz = st[i].size();
		while (!st[i].empty()) {
			auto p = st[i].top();
			st[i].pop();
			if (sz == 1) {
				ans[p.second] = '3';
			} else {
				ans[p.second] = '2';
			}
		}
	}
	
	for (i = 1; i <= n; ++i) {
		if (ans[i] == 0) ans[i] = '1';
		putchar(ans[i]);
	}
	printf("\n");
	return 0;
}