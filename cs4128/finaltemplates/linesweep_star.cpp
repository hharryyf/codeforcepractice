#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#define MAX_SIZE 32792
typedef long long ll;
using namespace std;

struct segt {
	int value, lz;
};

segt tree[MAX_SIZE];

// stores all the appeared y coordinate
vector<ll> disc;

// all the points, (x, y, c)
vector<pair<pair<ll, ll>, int> > pt;

void init() {
	pt.clear();
	disc.clear();
	for (int i = 0 ; i < MAX_SIZE; i++) {
		tree[i].value = tree[i].lz = 0;
	}
}

void pushdown(int index, int l, int r) {
	if (tree[index].lz) {
		if (l != r) {
			tree[index * 2].lz += tree[index].lz;
			tree[index * 2 + 1].lz += tree[index].lz;
			tree[index * 2].value += tree[index].lz;
			tree[index * 2 + 1].value += tree[index].lz;
		}
		tree[index].lz = 0;
	}
}

// increment [l, r] by val
void update(int start, int end, int l, int r, int index, int val) {
	if (start > end || l > r) return;
	pushdown(index, l, r);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].value += val;
		tree[index].lz = val;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (end <= mid) {
		update(start, end, l, mid, index * 2, val);
	} else if (start >= mid + 1) {
		update(start, end, mid + 1, r, index * 2 + 1, val);
	} else {
		update(start, end, l, mid, index * 2, val);
		update(start, end, mid + 1, r, index * 2 + 1, val);
	}
	
	tree[index].value = max(tree[index * 2].value, tree[index * 2 + 1].value);
}

int query() {
	return tree[1].value;
}

int main() {
	int n;
	ll w, h;
	int i, j;
	while (scanf("%d%lld%lld", &n, &w, &h) != EOF) {
		init();
		vector<ll> tmp;
		ll x, y;
		int c;
		for (i = 0 ; i < n; i++) {
			scanf("%lld%lld%d", &x, &y, &c);
			pt.push_back(make_pair(make_pair(x, y), c));
			tmp.push_back(y);
		}
		
		sort(tmp.begin(), tmp.end());
		sort(pt.begin(), pt.end());
		
		for (i = 0 ; i < n; i++) {
			if (i == 0 || tmp[i] != tmp[i-1]) {
				disc.push_back(tmp[i]);
			}
		}
		
		int m = (int) disc.size();
		
		/* 
			each leaf of the tree maintain the rectangle sum with 
			lower y index at disc[i]
			
			when adding in a star at (x, y) the y-range it has effect is at
			[y-h+1, y], the x-range it has effect is at [x, x+w-1] 
		*/
		int ans = 0;
		j = 0;
		for (i = 0 ; i < n; i++) {
			int lowy, highy;
			while (j < n && pt[i].first.first + w - 1 >= pt[j].first.first) {
				lowy = lower_bound(disc.begin(), disc.end(), pt[j].first.second - h + 1) - disc.begin();
				highy = lower_bound(disc.begin(), disc.end(), pt[j].first.second) - disc.begin();
				update(lowy, highy, 0, m - 1, 1, pt[j].second);
				j++;
			}
			
			lowy = lower_bound(disc.begin(), disc.end(), pt[i].first.second - h + 1) - disc.begin();
			highy = lower_bound(disc.begin(), disc.end(), pt[i].first.second) - disc.begin();
			ans = max(ans, query());
			update(lowy, highy, 0, m - 1, 1, -pt[i].second);
		}
		
		printf("%d\n", ans);
	}
	return 0;
}
