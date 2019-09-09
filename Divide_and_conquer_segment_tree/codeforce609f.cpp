#include <bits/stdc++.h>
#define MAX_SIZE 524312

typedef long long ll;

using namespace std;

typedef struct segt {
	int id;
	int masq;
	ll x;
	ll range;	
} segmenttree;

// initial frogs and 

typedef struct frog {
	int id;
	// x coordinate
	ll x;
	// length of the tonge
	ll t;
} Frog;

vector<Frog> frogs;

segmenttree tree[MAX_SIZE];

// the remaining mosquitoes, map from x-> all the size of the mosquitoes
map<ll, vector<ll> > remains;

pair<int, ll> ans[MAX_SIZE];

int n;

void fillans(int l, int r, int index);
void update(int pt, int l, int r, int index, ll val, ll masq);
void build(int start, int end, int index);
pair<int, ll> query(int start, int end, int l, int r, int index, ll x);
int getindex(ll x);

static bool cmp(const Frog &a, const Frog &b) {
	return a.x < b.x;
}

int main(int argc, char *argv[]) {
	int m, i;
	scanf("%d%d", &n, &m);
	for (i = 0 ; i < n; i++) {
		Frog fg;
		scanf("%lld%lld", &fg.x, &fg.t);
		fg.id = i;
		frogs.push_back(fg);
	}
	
	sort(frogs.begin(), frogs.end(), cmp);
	
	build(0, n - 1, 1);
	
	while (m > 0) {
		ll x, sz;
		scanf("%lld%lld", &x, &sz);
		int r = getindex(x);
		if (r != -1) {
			pair<int, ll> nextfg = query(0, r, 0, n - 1, 1, x);
			if (nextfg.first >= MAX_SIZE) {
				remains[x].push_back(sz);	
			} else {
				ll currentrange = sz + nextfg.second;
				ll eat = 1ll;
				map<ll, vector<ll> > :: iterator iter = remains.lower_bound(x);
				while (iter != remains.end()) {
					if (currentrange < iter->first) break;
					for (auto masqu : iter->second) {
						currentrange += masqu;
						eat++;
					}
					iter = remains.erase(iter);
				} 
				
				update(nextfg.first, 0, n - 1, 1, currentrange, eat);
			} 
		}
		m--;
	}
	
	fillans(0, n - 1, 1);
	
	for (i = 0 ; i < n; i++) {
		printf("%d %lld\n", ans[i].first, ans[i].second);
	}
	return 0;
}

// get the rightmost frog that has index no more than tx
int getindex(ll tx) {
	int ans = -1;
	int low = 0, high = (int) frogs.size() - 1;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (frogs[mid].x <= tx) {
			ans = max(ans, mid);
			low = mid + 1; 
		} else {
			high = mid - 1;
		}
	}
	return ans;
}

// return the index of the leftmost frog that has a range value at least x
// return MAX_SIZE as default
pair<int, ll> query(int start, int end, int l, int r, int index, ll x) {
	if (start > end || l > r) return pair<int, ll>(MAX_SIZE, 0ll);
	if (start > r || l > end) return pair<int, ll>(MAX_SIZE, 0ll);
	if (l == r) {
		if (tree[index].range >= x) return pair<int, ll>(l, tree[index].range);
		return pair<int, ll>(MAX_SIZE, 0ll);
	}
	
	int mid = l + (r - l) / 2;
	if (start <= l && r <= end) {
		if (tree[index].range < x) return pair<int, ll>(MAX_SIZE, 0ll);
		if (tree[index * 2].range >= x) return query(start, end, l, mid, index * 2, x);
		return query(start, end, mid + 1, r, index * 2 + 1, x); 
	}
	
	pair<int, ll> p1 =  query(start, end, l, mid, index * 2, x);
	pair<int, ll> p2 =  query(start, end, mid + 1, r, index * 2 + 1, x);
	return min(p1, p2);
}

void build(int start, int end, int index) {
	if (start > end) return;
	if (start == end) {
		tree[index].id = frogs[start].id;
		tree[index].x = frogs[start].x;
		tree[index].masq = 0;
		tree[index].range = frogs[start].x + frogs[start].t;
		return;
	}
	
	int mid = start + (end - start) / 2;
	build(start, mid, index * 2);
	build(mid + 1, end, index * 2 + 1);
	tree[index].masq = tree[index * 2].masq + tree[index * 2 + 1].masq;
	tree[index].range = max(tree[index * 2].range, tree[index * 2 + 1].range);
}

void update(int pt, int l, int r, int index, ll val, ll masq) {
	if (l > r) return;
	if (l == r && pt == l) {
		tree[index].range = val;
		tree[index].masq += masq;
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pt <= mid) {
		update(pt, l, mid, index * 2, val, masq);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, val, masq);
	}
	
	tree[index].masq = tree[index * 2].masq + tree[index * 2 + 1].masq;
	tree[index].range = max(tree[index * 2].range, tree[index * 2 + 1].range);
}

void fillans(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		ans[tree[index].id].first = tree[index].masq;
		ans[tree[index].id].second = tree[index].range - tree[index].x;
		return;
	}
	
	int mid = l + (r - l) / 2;
	fillans(l, mid, index * 2);
	fillans(mid + 1, r, index * 2 + 1);
}
