#include <bits/stdc++.h>
#define MAX_SIZE 2097312
typedef long long ll;
using namespace std;

struct segt {
	ll value, lz;
};

segt tree[MAX_SIZE];

void pushdown(int l, int r, int index) {
	if (l > r) return;
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

pair<ll, int> query(int start, int end, int l, int r, int index) {
	if (start > end || l > r) return make_pair(-1, -1);
	pushdown(l, r, index);
	if (start > r || l > end) return make_pair(-1, -1);
	int mid = l + (r - l) / 2;
	if (start <= l && r <= end) {
		if (l == r) { 
			return make_pair(tree[index].value, l);
		}
		if (tree[index * 2].value >= tree[index * 2 + 1].value) {
			return query(start, end, l, mid, index * 2);
		}
		return query(start, end, mid + 1, r, index * 2 + 1);
	}
	
	return max(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

void update(int start, int end, int l, int r, int index, ll val) {
	if (start > end || l > r) return;
	pushdown(l, r, index);
	if (start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].lz += val;
		tree[index].value += val;	
		return;
	}
	
	int mid = l + (r - l) / 2;
	update(start, end, l, mid, index * 2, val);
	update(start, end, mid + 1, r, index * 2 + 1, val);
	tree[index].value = max(tree[index * 2].value, tree[index * 2 + 1].value);
}

// x->(y, cost)
unordered_map<int, multiset<pair<int, ll>, greater<pair<int, ll> > > > mp;
// all the useful x-coord for the left-edge
vector<int> disc;
int tmp[MAX_SIZE >> 1];


// ans and (L, L), (R, R)
int L = 2000000000, R = 2000000000;
ll ans = 0;
int n;

int main() {
	int i;
	int cnt = 0;
	scanf("%d", &n);
	for (i = 0 ; i < n; i++) {
		int x, y;
		ll p;
		scanf("%d%d%lld", &x, &y, &p);
		if (y > x) {
			swap(x, y);
		}
		tmp[cnt++] = x, tmp[cnt++] = y;
		mp[x].insert(make_pair(y, p));
	}
	
	sort(tmp, tmp + cnt);
	
	for (i = 0 ; i < cnt; i++) {
		if (i == 0 || tmp[i] != tmp[i-1]) {
			disc.push_back(tmp[i]);
		}
	}
	
	int m = (int) disc.size();
	for (i = 0; i < m; i++) {
		if (i != 0) {
			update(0, i - 1, 0, m - 1, 1, -disc[i] + disc[i-1]);
		}
		
		auto iter = mp[disc[i]].begin();
		while (iter != mp[disc[i]].end()) {
			int y = iter->first;
			ll cost = iter->second;
			// cout << disc[i] << " " << y << " " << cost << endl;
			int index = lower_bound(disc.begin(), disc.end(), y) - disc.begin();
			update(0, index, 0, m - 1, 1, cost);
			iter++;
			if (iter != mp[disc[i]].end()) {
				y = iter->first;
				index = upper_bound(disc.begin(), disc.end(), y) - disc.begin();
				auto curr = query(index, i, 0, m - 1, 1);
				if (curr.first > ans) {
					R = disc[i];
					L = disc[curr.second];
					ans = curr.first;
				}
			} else {
				auto curr = query(0, i, 0, m - 1, 1);
				if (curr.first > ans) {
					R = disc[i];
					L = disc[curr.second];
					ans = curr.first;
				}
			}
			
		}
	}
	printf("%lld\n%d %d %d %d\n", ans, L, L, R, R);
	return 0;
}
