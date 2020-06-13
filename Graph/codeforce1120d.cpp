#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;


vector<int> g[MAX_SIZE];
vector<int> leaf;
int cost[MAX_SIZE];
int f[MAX_SIZE];
int id[MAX_SIZE];
int sz[MAX_SIZE];
int cnt = 0;

void dfs(int v, int pre) {
    id[v] = cnt++;
    sz[v] = 1;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
            sz[v] += sz[nv];
        }
    }

    if (v != 1 && sz[v] == 1) {
        leaf.push_back(id[v]);
    }
}

struct edge {
    int from, to, wt, id;
    int select;
    bool operator < (edge other) const {
        return wt < other.wt;
    }
};

vector<edge> edg;

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

vector<pair<int, int>> t[MAX_SIZE];
int height[MAX_SIZE];
int parent[MAX_SIZE][19];
int maxp[MAX_SIZE][19];

void dfs1(int v, int pre, int ht) {
	 parent[v][0] = pre;
	 height[v] = ht;
	 int i;
	 for (i = 1; i <= 18; i++) {
	 	 parent[v][i] = parent[parent[v][i-1]][i-1];
	 	 maxp[v][i] = max(maxp[v][i-1], maxp[parent[v][i-1]][i-1]);
	 }
	 
	 for (auto np : t[v]) {
	 	 if (np.first != pre) {
		  	maxp[np.first][0] = np.second;
		    dfs1(np.first, v, ht + 1);
         }
	 }
}

int LCA(int u, int v) {
   if (height[u] < height[v]) {
   	  swap(u, v);
   }
   int ret = 0;
   int i;
   for (i = 18; i >= 0; i--) {
   	   if (height[u] >= (1 << i) + height[v]) {
	   	  ret = max(ret, maxp[u][i]);
		  u = parent[u][i];	  
	   }
   }
   
   if (u == v) return ret;
   
   for (i = 18; i >= 0; i--) {
   	   if (parent[u][i] != parent[v][i]) {
			 ret = max(ret, max(maxp[u][i], maxp[v][i]));
			 u = parent[u][i];
			 v = parent[v][i];	  
	   }
   }
   
   ret = max(ret, max(maxp[u][0], maxp[v][0]));
   return ret;
}

int main() {
    int i, n;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) scanf("%d", &cost[i]);
    for (i = 0 ; i < MAX_SIZE; ++i) {
        f[i] = i;
    }

    for (i = 0 ; i < n - 1; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    dfs(1, 0);

    for (i = 1; i <= n; ++i) {
        int l = id[i], r = id[i] + sz[i] - 1;
        int L = lower_bound(leaf.begin(), leaf.end(), l) - leaf.begin();
        int R = upper_bound(leaf.begin(), leaf.end(), r) - leaf.begin() - 1;
        if (L <= R) {
            edg.push_back(edge{L, R+1, cost[i], i});
            // cout << "addedge " << L << " " << R << endl;
        }
    }

    sort(edg.begin(), edg.end());

    long long ans = 0;
    vector<int> ret;
    for (auto &e : edg) {
        if (find(e.from) != find(e.to)) {
            ans += e.wt;
            unionset(e.from, e.to);
            e.select = 1;
            t[e.from].emplace_back(e.to, e.wt);
            t[e.to].emplace_back(e.from, e.wt);
        }
    }

    dfs1(0, -1, 1);

    for (auto &e : edg) {
        if (e.select) {
            ret.push_back(e.id);
        } else if (e.wt == LCA(e.from, e.to)) {
            ret.push_back(e.id);
        }
    }

    sort(ret.begin(), ret.end());

    printf("%I64d %d\n", ans, (int) ret.size());
    for (auto v : ret) {
        printf("%d ", v);
    }
    printf("\n");
    return 0;
}