#include <bits/stdc++.h>

#define MAX_SIZE 1048592
#define INF 10000000000000ll

typedef long long ll;

using namespace std;

/* 
	https://codeforces.com/contest/1216/problem/F
	the problem is equivalent to given m segments each could cover [l, r] with weight w
	what is the minimum cost to cover [1, n]
	
   solution:
   1. sort all the segments according to the right end point
   2. we define dp[i] as the minimum cost that could cover [1, seg[i].end] by using i as the last segment
   then dp[i] = cost[i] + min(dp[k], which k refers to all i such that seg[k].end >= seg[i].start - 1)
   3. if seg[i].end == n then ans = min(ans, dp[i])
*/

struct seg {
	int l, r;
	ll cost;
};

ll tree[MAX_SIZE];

ll dp[MAX_SIZE >> 1];

vector<seg> rgs;

int n, k;

char st[MAX_SIZE >> 2];

static bool cmp(const seg &a, const seg &b) {
	return a.r < b.r;
}

/* get the leftmost index such that rgs[i].r >= num */
int getindex(int num) {
	int m = (int) rgs.size();
	int low = 0, high = m - 1; 
	int ret = m - 1;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (rgs[mid].r < num) {
			low = mid + 1;
		} else {
			high = mid - 1;
			ret = min(ret, mid);
		}
	}
	return ret;
}

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
	
	tree[index] = min(tree[index * 2], tree[index * 2 + 1]);
}

ll query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return INF;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	return min(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

int main() {
	scanf("%d%d", &n, &k);
	scanf("%s", st);
	int i;
	ll ans = INF;
	rgs.push_back(seg{0,0,0ll});
	for (i = 1; i <= n; i++) {
		if (st[i-1] == '1') {
			rgs.push_back(seg{max(1, i - k), min(i + k, n), (ll) i});
		}
		rgs.push_back(seg{i, i, (ll) i});
	}
	
	sort(rgs.begin(), rgs.end(), cmp);
	
	dp[0] = 0ll;
	
	int m = (int) rgs.size();
	update(0, 0, m - 1, 1, 0ll);
	for (i = 1; i < m; i++) {
		int index = getindex(rgs[i].l - 1);
		dp[i] = query(index, i - 1, 0, m - 1, 1) + rgs[i].cost;
		if (rgs[i].r == n) {
			// cout << "hi" << endl;
			ans = min(dp[i], ans);
		}
		update(i, 0, m - 1, 1, dp[i]);
	}
	
	printf("%lld\n", ans);
	return 0;
}
