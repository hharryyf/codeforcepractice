#include <bits/stdc++.h>
#define MAX_SIZE 300011
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds ;
using namespace std;
typedef tree <pair<int, int> , null_type , less <pair<int, int> >, rb_tree_tag ,
tree_order_statistics_node_update> ordered_set ;

struct BIT {
	ordered_set t[MAX_SIZE];
	int n;
	int shift(int x) {
		return x & (-x);
	}
	
	void add(int pos, pair<int, int> v) {
		while (pos <= n) {
			t[pos].insert(v);
			pos += shift(pos);
		}
	}
	
	void del(int pos, pair<int, int> v) {
		while (pos <= n) {
			t[pos].erase(v);
			pos += shift(pos);
		}
	}
	
	int query(int pos, int v) {
		pair<int, int> p = make_pair(v, MAX_SIZE);
		int ret = 0;
		while (pos > 0) {
			ret += t[pos].order_of_key(p);
			pos -= shift(pos);
		}
		return ret;
	}
};

BIT t;

struct event {
	int x, y, bk, id, tp;
	// 0 add event, 1 query event, 2 delete event
	bool operator < (event other) const {
		if (other.x != x) return x < other.x;
		return tp < other.tp;
	}
};

vector<event> evt;
vector<int> disc;
int inc[MAX_SIZE >> 1], pref[MAX_SIZE >> 1];
int b[MAX_SIZE >> 1], p[MAX_SIZE >> 1], s[MAX_SIZE >> 1];
int tmp[MAX_SIZE];
int ans[MAX_SIZE];

int main() {
	int i, n, m;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i) scanf("%d", &p[i]);
	
	for (i = 1; i <= n; ++i) scanf("%d", &s[i]);
	
	for (i = 1; i <= n; ++i) scanf("%d", &b[i]);
	
	for (i = 1; i <= m; ++i) scanf("%d", &inc[i]);
	
	for (i = 1; i <= m; ++i) scanf("%d", &pref[i]);
	
	for (i = 1; i <= n; ++i) {
		evt.push_back(event{p[i], b[i], p[i], i, 0});
		evt.push_back(event{s[i], b[i], p[i], i, 2});
		// here we reverse the y-intersect so that the prefix query
		// is equal to the actually query
		tmp[i] = -b[i] + p[i];
	}
	
	for (i = 1; i <= m; ++i) {
		evt.push_back(event{inc[i], pref[i], 0, i, 1});
	}
	
	sort(tmp + 1, tmp + 1 + n);
	sort(evt.begin(), evt.end());
	
	disc.push_back(-2000001000);
	for (i = 1; i <= n; ++i) {
		if (i == 1 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
	}
	
	t.n = (int) disc.size();
	
	for (auto e : evt) {
		if (e.tp == 0) {
			int idx = upper_bound(disc.begin(), disc.end(), -e.y + e.x) - disc.begin() - 1;
			t.add(idx, make_pair(e.x + e.y, e.id));
		} else if (e.tp == 1) {
			int idx = upper_bound(disc.begin(), disc.end(), -e.y + e.x) - disc.begin() - 1;
			ans[e.id] = t.query(idx, e.x + e.y);
		} else {
			int idx = upper_bound(disc.begin(), disc.end(), -e.y + e.bk) - disc.begin() - 1;
			t.del(idx, make_pair(e.bk + e.y, e.id));
		}
	}
	
	for (i = 1; i <= m; ++i) printf("%d ", ans[i]);
	printf("\n");
	return 0;
}