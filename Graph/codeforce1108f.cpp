#include <bits/stdc++.h>
#define MAX_SIZE 200111
using namespace std;
typedef long long ll;

int height[MAX_SIZE];
int f[MAX_SIZE];
int parent[MAX_SIZE][19];
ll pmax[MAX_SIZE][19];
struct edge {
    int from, to;
    ll w;
    bool selected;
    bool operator < (edge other) const {
        return w < other.w;
    }
};

vector<pair<int, ll>> g[MAX_SIZE];
vector<edge> edg;

void dfs(int v, int pre, int d) {
    int i;
    height[v] = d;
    parent[v][0] = pre;
    for (i = 1 ; i < 19; i++) {
        parent[v][i] = parent[parent[v][i-1]][i-1];
        pmax[v][i] = max(pmax[parent[v][i-1]][i-1], pmax[v][i-1]);
    }
    
    for (auto np : g[v]) {
        int nv = np.first;
        if (nv != pre) {
            pmax[nv][0] = np.second; 
            dfs(nv, v, d + 1);
        }
    }
}


int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
} 

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}


void Kruskal() {
    int i;
    for (i = 0 ; i < MAX_SIZE; i++) {
        f[i] = i;
    }
    
    sort(edg.begin(), edg.end());
    for (i = 0 ; i < edg.size(); i++) {
        if (find(edg[i].from) != find(edg[i].to)) {
            unionset(edg[i].from, edg[i].to);
            g[edg[i].from].emplace_back(edg[i].to, edg[i].w);
            g[edg[i].to].emplace_back(edg[i].from, edg[i].w);
            edg[i].selected = true;
        }
    }
}

// return the maximum edges of the path u->LCA(u, v)->v
ll LCA(int u, int v) {
    if (height[u] < height[v]) swap(u, v);
    ll ret = 0;
    int i;
    for (i = 18; i >= 0; i--) {
   	    if (height[u] >= (1 << i) + height[v]) {
	   	    ret = max(ret, pmax[u][i]);
		    u = parent[u][i];	  
	    }
    }
   
    if (u == v) return ret;
   
    for (i = 18; i >= 0; i--) {
   	    if (parent[u][i] != parent[v][i]) {
			 ret = max(ret, max(pmax[u][i], pmax[v][i]));
			 u = parent[u][i];
			 v = parent[v][i];	  
	    }
    }
   
   ret = max(ret, max(pmax[u][0], pmax[v][0]));
   return ret;
}

int main() {
    int n, m, i;
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; i++) {
        int v1, v2;
        ll w;
        scanf("%d%d%lld", &v1, &v2, &w);
        edg.push_back(edge{v1, v2, w, false});
    }
    
    Kruskal();
    dfs(1, 0, 0);
    int ans = 0;
    for (auto e : edg) {
        ll w = LCA(e.from, e.to);
        if (!e.selected && e.w == w) {
            ans++;
        }
    }
    
    printf("%d\n", ans);
    return 0;
}
