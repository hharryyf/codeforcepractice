#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 300111
using namespace std;

vector<pair<int, int>> g[MAX_SIZE];
int low[MAX_SIZE], visited[MAX_SIZE], instack[MAX_SIZE];
int cmpid[MAX_SIZE];
stack<int> s;
int k = 1;
int n, m;
// run tarjan's algorithm to find the biconnected components
void dfs(int v, int pre) {
    visited[v] = low[v] = k++;
    s.push(v);
    instack[v] = 1;
    for (auto np : g[v]) {
        int nv = np.first;
        if (nv != pre) {
            if (!visited[nv]) {
                dfs(nv, v);
                low[v] = min(low[v], low[nv]);
            } else if (instack[nv]) {
                low[v] = min(low[v], visited[nv]);
            }
        }
    }
    
    if (visited[v] == low[v]) {
        while (s.top() != v) {
            cmpid[s.top()] = v;
            s.pop();
        }
        
        cmpid[s.top()] = v;
        s.pop();
    }
}

// the color of the points
int color[MAX_SIZE];
unordered_map<int, int> g2[MAX_SIZE];
// we need to build the tree g2 after compression all the
// biconnected components
void build() {
    int i;
    for (i = 1; i <= n; i++) {
        for (auto np : g[i]) {
            int nv = np.first, w = np.second;
            if (cmpid[nv] == cmpid[i]) {
                color[cmpid[i]] = max(w, color[cmpid[i]]);
            } else {
                g2[cmpid[nv]][cmpid[i]] = g2[cmpid[i]][cmpid[nv]] 
                                    = max(g2[cmpid[i]][cmpid[nv]], w);
            }
        }
    }
}

int pre[MAX_SIZE];
int height[MAX_SIZE];
void dfs2(int v, int p) {
    pre[v] = p;
    height[v] = height[p] + 1;
    auto iter = g2[v].begin();
    while (iter != g2[v].end()) {
        if (iter->first != p) {
            dfs2(iter->first, v);
        }
        iter++;
    }
}

bool findpath(int u, int v) {
    if (height[u] < height[v]) swap(u, v);
    int ret = 0;
    ret = ret | color[u];
    ret = ret | color[v];
    while (height[u] > height[v]) {
        ret = ret | color[u];
        ret = ret | g2[u][pre[u]];
        u = pre[u];
    }
    
    while (u != v) {
        ret = ret | color[u];
        ret = ret | color[v];
        ret = ret | g2[u][pre[u]];
        ret = ret | g2[v][pre[v]];
        u = pre[u];
        v = pre[v];
    }
    ret = ret | color[u];
    return ret;
}

int main() {
    scanf("%d%d", &n, &m);
    int i;
    for (i = 0 ; i < m; i++) {
        int v1, v2, w;
        scanf("%d%d%d", &v1, &v2, &w);
        g[v1].emplace_back(v2, w);
        g[v2].emplace_back(v1, w);
    }
    
    dfs(1, 0);
    
    build();
    
    dfs2(cmpid[1], 0);
    
    int s, t;
    scanf("%d%d", &s, &t);
    if (findpath(cmpid[s], cmpid[t])) {
        printf("YES\n"); 
    } else {
        printf("NO\n");
    }
    return 0;
}
