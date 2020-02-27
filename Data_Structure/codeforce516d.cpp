#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_SIZE 262192
#define REP(i,s,t) for(i=s;i<=t;++i)
#define RREP(i,s,t) for(i=s;i>=t;--i)

typedef long long ll;
using namespace std;

struct segt {
	   int rsum, left, right;
};

segt tree[MAX_SIZE * 30];

int visited[MAX_SIZE >> 1];
int subsz[MAX_SIZE >> 1];
ll dp[MAX_SIZE >> 1][2];
vector<pair<int, int> > g[MAX_SIZE >> 1];
ll cost[MAX_SIZE >> 1];
ll disc[MAX_SIZE >> 1];
vector<int> g2[MAX_SIZE >> 1];
int f[MAX_SIZE >> 1];
int root[MAX_SIZE >> 1];
int id[MAX_SIZE >> 1];
ll tmp[MAX_SIZE >> 1];
int n, m;
int k = 1;
int cnt = 0;
int ans = 0;
ll L;

static bool cmp(const int &a, const int &b) {
	   return cost[a] < cost[b];
}

int build(int l, int r) {
	if (l > r) return 0;
	int curr = ++cnt;
	if (l == r) return curr;
	int mid = (l + r) >> 1;
	tree[curr].left = build(l, mid);
	tree[curr].right = build(mid + 1, r);
	return curr;
}

int update(int rt, int pos, int l, int r, int val) {
	if (pos < l || pos > r || l > r) return rt;
	int curr = ++cnt;
	tree[curr] = tree[rt];
	if (l == r && r == pos) {
	   tree[curr].rsum += val;
	   return curr;
	}
	
	int mid = (l + r) >> 1;
	if (pos <= mid) {
	   tree[curr].left = update(tree[rt].left, pos, l, mid, val);
	} else {
	   tree[curr].right = update(tree[rt].right, pos, mid + 1, r, val);
	}
	tree[curr].rsum = tree[tree[curr].left].rsum + tree[tree[curr].right].rsum;
	return curr;
}

int query(int rt1, int rt2, int start, int end, int l, int r) {
	if (rt1 == 0 || rt2 == 0|| start > end || l > r) return 0;
	if (start <= l && r <= end) return tree[rt2].rsum - tree[rt1].rsum;
	int mid = (l + r) >> 1;
	if (end <= mid) return query(tree[rt1].left, tree[rt2].left, start, end, l, mid);
	if (start >= mid + 1) return query(tree[rt1].right, tree[rt2].right, start, end, mid + 1, r);
	return query(tree[rt1].left, tree[rt2].left, start, end, l, mid) + query(tree[rt1].right, tree[rt2].right, start, end, mid + 1, r);
}

void dfs1(int v, int pre) {
	 for (auto np : g[v]) {
	 	 if (np.first != pre) {
		 	dfs1(np.first, v);
			dp[v][0] = max(dp[v][0], dp[np.first][0] + np.second); 
         }
	 }
}

void dfs2(int v, int pre) {
	 multiset<ll> st;
	 for (auto np : g[v]) {
	 	 if (np.first != pre) {
		  	st.insert(dp[np.first][0] + np.second);
         }
	 }
	 
	 for (auto np : g[v]) {
	 	  if (np.first != pre) {
		  	   st.erase(st.find(dp[np.first][0] + np.second));
		  	   if (st.empty()) {
				  dp[np.first][1] = dp[v][1] + np.second;
	           } else {
			   	  dp[np.first][1] = max(dp[v][1] + np.second, *st.rbegin() + np.second);
			   }
	           st.insert(dp[np.first][0] + np.second);
			   dfs2(np.first, v);	 
		  }
	 }
	 
}

void dfs3(int v) {
	 visited[v] = k++;
	 subsz[v] = 1;
	 int idx = lower_bound(disc, disc+m, cost[v]) - disc;
	 root[visited[v]] = update(root[visited[v] - 1], idx, 0, m - 1, 1);
	 for (auto nv : g2[v]) {
	 	  if (!visited[nv]) {
		  	 dfs3(nv);
		  	 subsz[v] += subsz[nv];
		  }
	 }
}

void dfs4(int v, int pre) {
	 int idx1 = lower_bound(disc, disc+m, cost[v]) - disc;
	 int idx2 = upper_bound(disc, disc+m, cost[v] + L) - disc - 1;
	 int l = visited[v], r = visited[v] + subsz[v] - 1;
	 int ret = query(root[l-1], root[r], idx1, idx2, 0, m - 1);
	 ans = max(ret, ans);
	 for (auto nv : g2[v]) {
	 	 if (nv != pre) {
	 	 	dfs4(nv, v);
         }
	 }
}

int find(int x) {
	if (x == f[x]) return x;
	return f[x] = find(f[x]);
}

int main() {
	int i;
	int u, v;
	int w;	
	scanf("%d", &n);
	REP(i, 1, n-1) {
		scanf("%d%d%d", &u, &v, &w);
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	
	dfs1(1, 0);
	dfs2(1, 0);
	
	REP(i,1,n) {
		cost[i] = max(dp[i][0], dp[i][1]);
		id[i] = i;
		tmp[i] = cost[i];
	}
	
	sort(tmp + 1, tmp + 1 + n);
	REP(i,1,n) {
		if (i == 1 || tmp[i] != tmp[i-1]) disc[m++] = tmp[i];
		f[i] = i;
	}
	
	sort(id + 1, id + 1 + n, cmp);
	
	RREP(i,n,1) {
		for (auto np : g[id[i]]) {
			int v = np.first;
			if (cost[id[i]] <= cost[v]) {
			   v = find(v);
			   if (v == id[i]) continue;
			   f[v] = id[i];
			   g2[id[i]].push_back(v);
			   // cout << "add " << id[i].second << " " << v << endl; 
			}
		}
	}
	
	int rt = id[1];
	root[0] = build(0, m - 1);
	
	dfs3(rt);
	
	int q;
	scanf("%d", &q);
	while (q > 0) {
		  scanf("%lld", &L);
		  ans = 0;
		  dfs4(rt, 0);
		  printf("%d\n", ans);
		  q--;
	}
	return 0;
}
