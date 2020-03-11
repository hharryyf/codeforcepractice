#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define INF 524292
using namespace std;
typedef long long ll;


int V;
struct position {
	int x, t;
	bool operator < (position other) const {
		if((x + V * t) != (other.x + V * other.t)) {
			return (x + V * t) <  (other.x + V * other.t);
		}
		return x - V * t > other.x - V * other.t;
	}
};

int tree[MAX_SIZE];
position pos[MAX_SIZE];
int tmp[MAX_SIZE];
// stores all the x - Vt
vector<int> disc;
int n;

int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return -INF;
	if (start <= l && r <= end) return tree[index];
	int mid = (l + r) >> 1;
	if (end <= mid) return query(start, end, l, mid, index << 1);
	if (start >= mid + 1) return query(start, end, mid + 1, r, index << 1 | 1);
	return max(query(start, end, l, mid, index << 1), 
	           query(start, end, mid + 1, r, index << 1 | 1));
}

void update(int pos, int l, int r, int index, int val) {
	if (pos < l || pos > r || l > r) return;
	if (l == r && pos == l) {
		tree[index] = max(val, tree[index]);
		return;
	}
	
	int mid = (l + r) >> 1;
	if (pos <= mid) {
		update(pos, l, mid, index * 2, val);
	} else {
		update(pos, mid + 1, r, index * 2 + 1, val);
	}
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

int solve(int tp) {
	int i, ans = 0, sz = (int) disc.size();
	if (tp == 1) {
		for (i = 0 ; i < MAX_SIZE; ++i) tree[i] = -INF;
		int idx = lower_bound(disc.begin(), disc.end(), 0) - disc.begin();
		update(idx, 0, sz - 1, 1, 0);
	} else {
		for (i = 0 ; i < MAX_SIZE; ++i) tree[i] = 0;
	}
	
	for (i = 1; i <= n; ++i) {
		if (tp == 1 && pos[i].x + pos[i].t * V < 0) continue;
		int idx = lower_bound(disc.begin(), disc.end(), pos[i].x - pos[i].t * V) - disc.begin();
		int v = query(idx, sz - 1, 0, sz - 1, 1);
		update(idx, 0, sz - 1, 1, v + 1);
		ans = max(v + 1, ans);
	}
	return ans;
}

int main() {
	int i;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d%d", &pos[i].x, &pos[i].t);
	}
	scanf("%d", &V);
	for (i = 1; i <= n; ++i) {
		tmp[i] = pos[i].x - pos[i].t * V;
	}
	
	sort(pos + 1, pos + 1 + n);
	
	sort(tmp, tmp + n + 1);
	
	for (i = 0; i <= n; ++i) {
		if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
	}
	
	printf("%d %d\n", solve(1), solve(2));
	
	return 0;
}