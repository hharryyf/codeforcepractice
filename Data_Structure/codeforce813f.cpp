#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define mid ((l+r)>>1)
#define LEFT (index << 1)
#define RIGHT (index << 1 | 1)
using namespace std;

// the range tree that contains all the queries
vector<pair<int, int>> tree[MAX_SIZE];
vector<int> sz[MAX_SIZE];
vector<int> f[MAX_SIZE];
vector<int> color[MAX_SIZE];
// the edges (subtree,parent)
stack<pair<int, int>> edg;
int ans[MAX_SIZE];

// find parent of x and the color of x
pair<int, int> find(int x) {
	if (f[x].back() == x) return make_pair(x, color[x].back());
	auto p = find(f[x].back());
	return make_pair(p.first, color[x].back() ^ p.second);
}

// delete the last edge
void del() {
	if (!edg.empty()) {
		auto p = edg.top();
		edg.pop();
		sz[p.second].pop_back();
		f[p.first].pop_back();
		color[p.first].pop_back();
	}
}
// add an edge between x and y
void add(int x, int y, int &valid) {
	auto p1 = find(x), p2 = find(y);
	if (p1.first == p2.first && p1.second == p2.second) valid = false;
	if (sz[p1.first].back() < sz[p2.first].back()) {
		// join from p1->p2
		sz[p2.first].push_back(sz[p2.first].back() + sz[p1.first].back());
		f[p1.first].push_back(p2.first);
		// TODO
		if (p1.second != p2.second) {
			// remain color p1.first as the same
			color[p1.first].push_back(color[p1.first].back() ^ color[p2.first].back());
		} else {
			// change color p1.first 
			color[p1.first].push_back(color[p1.first].back() ^ color[p2.first].back() ^ 1);
		}
		edg.push(make_pair(p1.first, p2.first));
	} else {
		if (p1.first != p2.first) {
			sz[p1.first].push_back(sz[p2.first].back() + sz[p1.first].back());
			if (p1.second != p2.second) {
			// remain color p1.first as the same
				color[p2.first].push_back(color[p1.first].back() ^ color[p2.first].back());
			} else {
				// change color p1.first 
				color[p2.first].push_back(color[p1.first].back() ^ color[p2.first].back() ^ 1);
			}
			f[p2.first].push_back(p1.first);
		} else {
			sz[p1.first].push_back(sz[p1.first].back());
			color[p1.first].push_back(color[p1.first].back());
			f[p2.first].push_back(f[p2.first].back());
		}
		edg.push(make_pair(p2.first, p1.first));
	}
}

// insert it to [start, end]
void update(int start, int end, int l, int r, int index, pair<int, int> it) {
	if (start > end || l > r || start > r || l > end) return;
	if (start <= l && r <= end) {
		tree[index].push_back(it);
		return;
	}
	
	if (end <= mid) {
		update(start, end, l, mid, LEFT, it);
	} else if (start >= mid + 1) {
		update(start, end, mid + 1, r, RIGHT, it);
	} else {
		update(start, end, l, mid, LEFT, it);
		update(start, end, mid + 1, r, RIGHT, it);
	}
}

void dfs(int l, int r, int index, int valid) {
	int cnt = 0;
	for (auto e : tree[index]) {
		add(e.first, e.second, valid);
		++cnt;
	}
	
	if (l == r) {
		ans[l] = valid;
		while (cnt > 0) {
			del();
			--cnt;
		}
		return;
	}
	
	dfs(l, mid, LEFT, valid);
	dfs(mid + 1, r, RIGHT, valid);
	while (cnt > 0) {
		del();
		--cnt;
	}
}

unordered_map<int, int> qrs[MAX_SIZE];
set<pair<int, int>> st;
int main() {
	int i, n, q;
	scanf("%d%d", &n, &q);
	for (i = 1; i <= n; ++i) {
		f[i].push_back(i);
		color[i].push_back(0);
		sz[i].push_back(1);
	} 
	
	for (i = 1; i <= q; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (qrs[x][y]) {
			update(qrs[x][y], i - 1, 1, q, 1, make_pair(x, y));
			qrs[x][y] = 0;
			st.erase(make_pair(x, y));
		} else {
			qrs[x][y] = i;
			st.insert(make_pair(x, y));
		}
	}
	
	for (auto p : st) {
		update(qrs[p.first][p.second], q, 1, q, 1, p);
	}
	
	dfs(1, q, 1, 1);
	
	for (i = 1; i <= q; ++i) {
		printf("%s\n", ans[i] ? "YES" : "NO");
	}
	return 0;
}