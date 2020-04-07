#include <bits/stdc++.h>
#define MAX_SIZE 100111
#define MID ((l+r)>>1)
#define RIGHT (index << 1 | 1)
#define LEFT (index << 1)
typedef long long ll;
using namespace std;

vector<int> g[MAX_SIZE];
int f[MAX_SIZE][18];
int sz[MAX_SIZE], son[MAX_SIZE], depth[MAX_SIZE];
int id[MAX_SIZE], rid[MAX_SIZE], top[MAX_SIZE];
int upmost[MAX_SIZE], L;
ll sm[MAX_SIZE][18];
ll wt[MAX_SIZE];
ll S;
int n, cnt = 0;

int tree[MAX_SIZE << 2];

void dfs1(int v, int pre) {
	 f[v][0] = pre;
	 sm[v][0] = wt[pre];
	 depth[v] = depth[pre] + 1;
	 sz[v] = 1;
	 int max_subsz = 0, i;
	 for (i = 1; i <= 17; ++i) {
		 f[v][i] = f[f[v][i-1]][i-1];
		 sm[v][i] = sm[f[v][i-1]][i-1] + sm[v][i-1];
	 }
	 for (auto nv : g[v]) {
	 	 if (nv != pre) {
         	dfs1(nv, v);
         	sz[v] += sz[nv];
         	if (max_subsz < sz[nv]) {
			   son[v] = nv, max_subsz = sz[nv]; 
	        }
		 }
	 }
}

void dfs2(int v, int tp) {
	 top[v] = tp, id[v] = ++cnt, rid[id[v]] = v;
	 if (son[v]) {
	 	dfs2(son[v], tp);
	 }
	 
	 for (auto nv : g[v]) {
	 	 if (nv != f[v][0] && nv != son[v]) {
		 	dfs2(nv, nv); 
         }
	 }
}
// find the upmost parent of v such that the length of the path
// is no more than L - 1 and the sum of the nodes on that path
// is no more than S - wt[v]
int find(int v) {
	ll curr = wt[v];
	int tol = 1, i;
	for (i = 17; i >= 0; --i) {
		if (tol + (1 << i) <= L && curr + sm[v][i] <= S && f[v][i] != 0) {
			tol = tol + (1 << i);
			curr = curr + sm[v][i];
			v = f[v][i];
		}
	}
	
	return v;
}

void pushdown(int l, int r, int index) {
	if (l >= r) return;
	if (tree[index] == 1) {
		tree[LEFT] = tree[index];
		tree[RIGHT] = tree[index];
		tree[index] = 0;
	}
}

void update(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return;
	pushdown(l, r, index);
	if (start <= l && r <= end) {
		tree[index] = 1;
		return;
	}
	
	if (end <= MID) {
		update(start, end, l, MID, LEFT);
	} else if (start >= MID + 1) {
		update(start, end, MID + 1, r, RIGHT);
	} else {
		update(start, end, l, MID, LEFT);
		update(start, end, MID + 1, r, RIGHT);
	}
}

int query(int pt, int l, int r, int index) {
	if (l > r || pt < l || pt > r) return 0;
	pushdown(l, r, index);
	if (pt == l && l == r) {
		return tree[index];
	}
	
	if (pt <= MID) return query(pt, l, MID, LEFT);
	return query(pt, MID + 1, r, RIGHT);
}
// set all vertices on the path from x to y as visited
void hld(int x, int y) {
	int fx = top[x], fy = top[y];
	while (fx != fy) {
		if (depth[fx] >= depth[fy]) {
		    update(id[fx], id[x], 1, n, 1);
			x = f[fx][0], fx = top[x];
		} else {
            update(id[fy], id[y], 1, n, 1);
			y = f[fy][0], fy = top[y];
		}  
	}
	
	if (id[x] <= id[y]) {
	   update(id[x], id[y], 1, n, 1);
	} else {
	   update(id[y], id[x], 1, n, 1);
	}
}

int main() {
	scanf("%d%d%I64d", &n, &L, &S);
	int i;
	for (i = 1; i <= n; ++i) {
		scanf("%I64d", &wt[i]);
		if (wt[i] > S) {
			printf("-1\n");
			return 0;
		}
	}
	
	for (i = 2; i <= n; ++i) {
		int v;
		scanf("%d", &v);
		g[v].push_back(i);
	}
	
	dfs1(1, 0);
	dfs2(1, 1);
	
	for (i = 1; i <= n; ++i) {
		upmost[i] = find(i);
		// cout << i << " " << upmost[i] << endl;
	}
	
	int ans = 0;
	for (i = n; i >= 1; --i) {
		if (!query(id[i], 1, n, 1)) {
			ans++;
			hld(i, upmost[i]);
		}
	}
	
	printf("%d\n", ans);
	return 0;
}