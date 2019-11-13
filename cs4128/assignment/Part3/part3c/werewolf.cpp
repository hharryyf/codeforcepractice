#include <bits/stdc++.h>
#define MAX_SIZE 524292
using namespace std;

struct qrs {
	int l, r, dn, up, id;
};

struct pts {
	int x, y;
};

static bool cmp_1(const qrs &a, const qrs &b) {
	return a.up < b.up;
}

static bool cmp_2(const pts &a, const pts &b) {
	return a.y < b.y;
}

// n points, q queries
int n, q;

int tree[MAX_SIZE];

// all the points
vector<pts> pt;
// all the queries
vector<qrs> qr;
// add a point
void addpoint(int x, int y) {
	pt.push_back(pts{x, y});
}
// add a query
void addquery(int l, int r, int dn, int up, int id) {
	qr.push_back(qrs{l, r, dn, up, id});
}

// set pos to val
void update(int pos, int l, int r, int index, int val) {
	if (l > r) return;
	if (l == r && r == pos) {
		tree[index] = max(tree[index], val);
		return;
	}
	
	int mid = l + (r - l) / 2;
	if (pos <= mid) {
		update(pos, l, mid, index * 2, val);
	} else {
		update(pos, mid + 1, r, index * 2 + 1, val);
	}
	tree[index] = max(tree[index * 2], tree[index * 2 + 1]);
}

// range max query
int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return 0;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	return max(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

int ans[MAX_SIZE >> 1];

// solve all the points and queries, invariant, this function is only called when
// the points and queries are added and pt.size = n, qr.size = q
void solve(vector<int> &ret) {
	sort(qr.begin(), qr.end(), cmp_1);
	sort(pt.begin(), pt.end(), cmp_2);
	int i = 0, j = 0;
	for (i = 0, j = 0; i < q; i++) {
		while (j < n && qr[i].up >= pt[j].y) {
			update(pt[j].x, 1, n, 1, pt[j].y);
			j++;
		}
		
		ans[qr[i].id] = (query(qr[i].l, qr[i].r, 1, n, 1) >= qr[i].dn);
	}	
	
	for (i = 1; i <= q; i++) {
		ret.push_back(ans[i]);
	}
}

vector<int> g[MAX_SIZE >> 1];

struct Construction {
	int tp;
	int k = 1;
	int f[MAX_SIZE];
	int parent[MAX_SIZE][19];
	vector<int> rt[MAX_SIZE >> 1];
	int dfsord[MAX_SIZE >> 1];
	int subsz[MAX_SIZE >> 1];
	Construction(int a) {
		this->tp = a;
	}
	
	
	int find(int x) {
		if (f[x] == x) return x;
		return f[x] = find(f[x]);
	}
	
	void dfs(int v) {
		int i;
		dfsord[v] = k++;
		subsz[v] = 1;
		
		for (i = 1 ; i < 19; i++) {
			parent[v][i] = parent[parent[v][i-1]][i-1];
		}
		
		for (auto nv : rt[v]) {
			dfs(nv);
			subsz[v] = subsz[v] + subsz[nv];
		}
	}
	
	void build() {
		int i;
		for (int i = 1; i <= n; i++) {
			f[i] = i;
		}
		// the first tree
		if (tp == 0) {
			
			for (i = n; i >= 1; i--) {
				for (auto v : g[i]) {
					// only join from low to high
					if (i < v) {
						v = find(v);
						if (v == i) continue;
						f[v] = i;
						parent[v][0] = i;
						rt[i].push_back(v);
					}
				}
			}
			
			dfs(1);
		} else {
		// the second tree
			for (i = 1; i <= n; i++) {
				for (auto v : g[i]) {
					// only join from low to high
					if (i > v) {
						v = find(v);
						if (v == i) continue;
						f[v] = i;
						parent[v][0] = i;
						rt[i].push_back(v);
					}
				}
			}
			dfs(n);
		}
	}
	
	// give a point to start/end and an upper bound/lower bound
	// return to the uppermost point it can reach in its connected component 
	int getrange(int x, int l) {
		int i;
		for (i = 18; i >= 0; i--) {
			if (parent[x][i] && ((tp == 0 && parent[x][i] >= l) || (parent[x][i] <= l && tp == 1))) {
				x = parent[x][i];
			}
		}
		
		return x;
	}
};

Construction t1 = Construction(0);
Construction t2 = Construction(1);

void check_validity() {
	vector<int> ret;
	int m;
	scanf("%d%d%d", &n, &m, &q);
	
	int i;
	for (i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x++;
		y++;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	
	t1.build();
	t2.build();
	
	for (i = 1; i <= n; i++) {
		addpoint(t1.dfsord[i], t2.dfsord[i]);
	}
	
	for (i = 1; i <= q; i++) {
		int s, e, l, r;
		scanf("%d%d%d%d", &s, &e, &l, &r);
		s++, e++, l++, r++;
		s = t1.getrange(s, l);
		e = t2.getrange(e, r);
		addquery(t1.dfsord[s], t1.dfsord[s] + t1.subsz[s] - 1, 
				 t2.dfsord[e], t2.dfsord[e] + t2.subsz[e] - 1, i);
	}
	
	
	solve(ret);
	
	for (auto rr : ret) {
		cout << rr << endl;
	}
}

int main() {
	check_validity();
	return 0;
}
