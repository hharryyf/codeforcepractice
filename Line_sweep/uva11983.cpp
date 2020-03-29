#include <bits/stdc++.h>
#define MAX_SIZE 131122
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
#define MID ((l+r) >> 1)
typedef long long ll;
using namespace std;

struct segt {
	// total cover
	int cover;
	// cover with at exactly i segments
	ll c[11];
};

struct event {
	int l, r, y, tp;
	bool operator < (event other) {
		if (y != other.y) return y < other.y;
		return tp > other.tp;
	}
};

vector<int> disc;
vector<event> evt;
segt tree[MAX_SIZE];
int tmp[MAX_SIZE];
int n, k;

void pullup(int l, int r, int index) {
	int i;
	for (i = 0 ; i <= k; ++i) tree[index].c[i] = 0;
	if (l == r) {
		tree[index].c[min(tree[index].cover, k)] = disc[l+1] - disc[l];
	} else {
		for (i = 0 ; i <= k; ++i) {
			tree[index].c[min(tree[index].cover + i, k)] += tree[LEFT].c[i] + tree[RIGHT].c[i];
		}
	}
}

void build(int l, int r, int index) {
	if (l > r) return;
	int i;
	for (i = 0 ; i <= k; ++i) {
		tree[index].c[i] = 0;
	}
	tree[index].cover = 0;
	if (l == r) {
		tree[index].c[0] = disc[l+1] - disc[l];
		return;
	} 
	
	build(l, MID, LEFT);
	build(MID + 1, r, RIGHT);
	tree[index].c[0] = tree[LEFT].c[0] + tree[RIGHT].c[0];
}

void update(int start, int end, int l, int r, int index, int tp) {
	if (start > end || l > r || start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].cover += tp;
		pullup(l, r, index);
		return;
	}
	
	if (end <= MID) {
		update(start, end, l, MID, LEFT, tp);
	} else if (start >= MID + 1) {
		update(start, end, MID + 1, r, RIGHT, tp);
	} else {
		update(start, end, l, MID, LEFT, tp);
		update(start, end, MID + 1, r, RIGHT, tp);
	}
	pullup(l, r, index);
}

int main() {
	int T, I;
	int i, x1, x2, y1, y2;
	scanf("%d", &T);
	for (I = 1; I <= T; ++I) {
		ll ans = 0;
		int cnt = 0;
		evt.clear();
		disc.clear();
		scanf("%d%d", &n, &k);
		for (i = 0 ; i < n; ++i) {
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			x2++, y2++;
			tmp[cnt++] = x1, tmp[cnt++] = x2;
			evt.push_back(event{x1, x2, y1, 1});
			evt.push_back(event{x1, x2, y2, -1});
		}
		
		sort(evt.begin(), evt.end());
		sort(tmp, tmp + cnt);
		for (i = 0 ; i < cnt; ++i) {
			if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
		}
		
		int sz = (int) disc.size();
		build(0, sz - 2, 1);
		for (i = 0 ; i < (int) evt.size() - 1; ++i) {
			int l = lower_bound(disc.begin(), disc.end(), evt[i].l) - disc.begin();
			int r = lower_bound(disc.begin(), disc.end(), evt[i].r) - disc.begin() - 1;
			update(l, r, 0, sz - 2, 1, evt[i].tp);
			// cout << "cover " << disc[l] << " " << disc[r] << endl;
			// cout << tree[1].c[1] << "---" << tree[1].c[k]<< endl;
			ans = ans + 1ll * tree[1].c[k] * (evt[i+1].y - evt[i].y);
		}
		
		cout << "Case " << I << ": " << ans << endl;
	}
	return 0;
}