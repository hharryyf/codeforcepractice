#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;

int subsz[MAX_SIZE];
int visited[MAX_SIZE];
// binary lifting parent array
int parent[MAX_SIZE][18];
// rooted tree
vector<int> g[MAX_SIZE];
// invariant, each level is sorted in ascending order
// store the dfs order of nodes
vector<int> level[MAX_SIZE];
int dep[MAX_SIZE];
int k = 1;

void dfs(int v, int pre) {
    subsz[v] = 1;
    dep[v] = dep[pre] + 1;
    visited[v] = k++;
    parent[v][0] = pre;
    level[dep[v]].push_back(visited[v]);
    int i;
    for (i = 1; i < 18; i++) parent[v][i] = parent[parent[v][i-1]][i-1];
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
            subsz[v] += subsz[nv];
        }
    }
}

int getkth(int v, int k) {
    int i;
    for (i = 17; i >= 0; i--) {
        if (k >= (1 << i)) {
            k = k - (1 << i);
            v = parent[v][i];
        }
    }
    return v;
}

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        int v;
        scanf("%d", &v);
        if (v != 0) g[v].push_back(i);
    }
    
    for (i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, 0);
        }
    }
    
    int m;
    scanf("%d", &m);
    while (m > 0) {
        int v, p;
        scanf("%d%d", &v, &p);
        if (dep[v] <= p) {
            printf("0 ");
        } else {
            int nv = getkth(v, p);
            int l = visited[nv], r = visited[nv] + subsz[nv] - 1;
            int v1 = lower_bound(level[dep[v]].begin(), level[dep[v]].end(), l) - level[dep[v]].begin();
            int v2 = upper_bound(level[dep[v]].begin(), level[dep[v]].end(), r) - level[dep[v]].begin() - 1;
            printf("%d ", max(0, v2 - v1));
        }
        m--;
    }
    
    printf("\n");
    return 0;
}
